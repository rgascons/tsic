#ifndef __TAISEI_LEXER__
#define __TAISEI_LEXER__

#include <string>
#include <unordered_map>

#include "Utils/InputReaders.h"
#include "Lex/Token.h"


namespace tsic {

class Lexer
{
public:
    Lexer();
	Lexer(InputReader *fr);

    Token getTok();

    double getNumVal();
    std::string getIdentifierStr();

private:
    void InitializeTokenMap();

private:
    std::string IdentifierStr;
    double NumVal;

    std::unordered_map<std::string, Token> TokenMap;
    bool bTokenMapInitialized;

    char LastChar;

    InputReader *inputReader;
};

} // End tsic namespace


#endif
