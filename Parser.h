#ifndef __TAISEI_PARSER__
#define __TAISEI_PARSER__

#include "Lexer.h"
#include "AST.h"

#include <memory>
#include <unordered_map>

class Parser
{
public:
    static void MainLoop(); 

    static Token getNextToken() {
        return CurTok = Lexer::getTok();
    }

private:
    static int GetTokPrecedence();
    static void InitializeBinOpPrecedence();

    static std::unique_ptr<ExprAST> ParseNumberExpr();
    static std::unique_ptr<ExprAST> ParseParenExpr();
    static std::unique_ptr<ExprAST> ParseIdentifierExpr();
    static std::unique_ptr<ExprAST> ParsePrimary();
    static std::unique_ptr<ExprAST> ParseExpression();
    static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
    static std::unique_ptr<PrototypeAST> ParsePrototype();
    static std::unique_ptr<FunctionAST> ParseDefinition();

    static void Parser::HandleDefinition();;

   
private:
    static Token CurTok;
    static std::unordered_map<char, int> BinOpPrecedence;
    static bool bBinOpPrecedenceInitialized;
};

#endif