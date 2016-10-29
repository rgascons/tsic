#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "Parser/Parser.h"
#include "Utils/Error.h"


Token Parser::CurTok;
std::unordered_map<char, int> Parser::BinOpPrecedence;
bool Parser::bBinOpPrecedenceInitialized = false;

void Parser::MainLoop() {
    Context::TheModule = llvm::make_unique<Module>("my cool jit", Context::TheContext);
    while (1) {
        fprintf(stderr, "ready> ");
        switch (CurTok) {
        case tok::eof:
            return;
        case ';':
            getNextToken();
            break;
        default:
            HandleDefinition();
            break;
        }
    }
}

std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
    auto result = llvm::make_unique<NumberExprAST>(Lexer::getNumVal());
    getNextToken();
    return std::move(result);
}

std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
    getNextToken();
    auto V = ParseExpression();

    if (!V)
        return nullptr;

    if (CurTok != ')')
        return LogError("expected ')'");
    getNextToken();
    return V;
}

std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr() {
    std::string IdName = Lexer::getIdentifierStr();

    getNextToken();

    if (CurTok != '(')
        return llvm::make_unique<VariableExprAST>(IdName);

    getNextToken();
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurTok != ')') {
        while (1) {
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;

            if (CurTok == ')')
                break;

            if (CurTok != ',')
                return LogError("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }

    getNextToken();

    return llvm::make_unique<CallExprAST>(IdName, std::move(Args));
}

std::unique_ptr<ExprAST> Parser::ParsePrimary() {
    switch (CurTok) {
    default:
        return LogError("Unknown token when expecting an expression");
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    }
}

std::unique_ptr<ExprAST> Parser::ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while (1) {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        Token BinOp = CurTok;
        getNextToken();

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = llvm::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

std::unique_ptr<PrototypeAST> Parser::ParsePrototype() {
    if (CurTok != tok_identifier)
        return LogErrorP("Expected function name in prototype");

    std::string FnName = Lexer::getIdentifierStr();
    getNextToken();

    if (CurTok != '(')
        return LogErrorP("Expected '(' in prototype");

    std::vector<std::string> ArgNames;
    while (getNextToken() == tok_identifier)
        ArgNames.push_back(Lexer::getIdentifierStr());
    if (CurTok != ')')
        return LogErrorP("Expected ')' in prototype");

    getNextToken();

    return llvm::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

std::unique_ptr<FunctionAST> Parser::ParseDefinition() {
    getNextToken();
    auto Proto = ParsePrototype();
    if (!Proto) return nullptr;

    if (auto E = ParseExpression())
        return llvm::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    return nullptr;
}


void Parser::HandleDefinition() {
    if (auto FnAST = ParseDefinition()) {
        if (auto *FnIR = FnAST->codegen()) {
            fprintf(stderr, "Read function definition:");
            FnIR->dump();
        }
    }
    else {
        // Skip token for error recovery.
        getNextToken();
    }
}

int Parser::GetTokPrecedence() {
    if (!bBinOpPrecedenceInitialized)
        InitializeBinOpPrecedence();

    if (!isascii(CurTok))
        return -1;

    int TokPrec = BinOpPrecedence[CurTok];
    if (TokPrec <= 0) return -1;
    return TokPrec;
}

void Parser::InitializeBinOpPrecedence() {
    BinOpPrecedence['<'] = 10;
    BinOpPrecedence['+'] = 20;
    BinOpPrecedence['-'] = 30;
    BinOpPrecedence['*'] = 40;
}