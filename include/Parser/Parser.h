#ifndef __TAISEI_PARSER__
#define __TAISEI_PARSER__

#include "Lex/Lexer.h"
#include "AST/AST.h"
#include "Lex/Token.h"

#include <memory>
#include <unordered_map>

namespace tsic {


class Parser
{
public:
    Parser();
    void MainLoop(); 

    Token getNextToken() {
        return CurTok = lexer->getTok();
    }

private:
    int GetTokPrecedence();
    void InitializeBinOpPrecedence();

    std::unique_ptr<ExprAST> ParseNumberExpr();
    std::unique_ptr<ExprAST> ParseParenExpr();
    std::unique_ptr<ExprAST> ParseIdentifierExpr();
    std::unique_ptr<ExprAST> ParsePrimary();
    std::unique_ptr<ExprAST> ParseExpression();
    std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
    std::unique_ptr<PrototypeAST> ParsePrototype();
    std::unique_ptr<FunctionAST> ParseDefinition();

    void HandleDefinition();;

   
private:
    Lexer *lexer;

    Token CurTok;
    std::unordered_map<char, int> BinOpPrecedence;
    bool bBinOpPrecedenceInitialized;
};


} // End tsic namespace

#endif