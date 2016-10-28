#ifndef __TAISEI_LEXER__
#define __TAISEI_LEXER__

#include <string>
#include <unordered_map>

enum Token {
    tok_eof = -1,

    // commands
    tok_struct = -2,
    tok_def = -3,
    tok_extern = -4,

    // primary
    tok_identifier = -5,
    tok_number = -6,
};

class Lexer
{
public:
    static Token getTok();
    static double getNumVal();
    static std::string getIdentifierStr();

private:
    static void InitializeTokenMap();

private:
    static std::string IdentifierStr;
    static double NumVal;

    static std::unordered_map<std::string, Token> TokenMap;
    static bool bTokenMapInitialized;

    static int LastChar;
};

#endif