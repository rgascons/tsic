#include "Lex/Lexer.h"

namespace tsic {

Lexer::Lexer(InputReader *fr) {
   inputReader = fr;
   LastChar = ' ';
}


Token Lexer::getTok() {
    if (!bTokenMapInitialized) {
        InitializeTokenMap();
        bTokenMapInitialized = true;
    }

    while (isspace(LastChar))
        LastChar = inputReader->getNextChar();

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = inputReader->getNextChar())))
            IdentifierStr += LastChar;

        std::unordered_map<std::string, Token>::const_iterator t_it;
        t_it = TokenMap.find(IdentifierStr);

        if (t_it == TokenMap.end())
            return tok::Identifier;
        else
            return t_it->second;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;

        do {
            NumStr += LastChar;
            LastChar = inputReader->getNextChar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok::Number;
    }

    if (LastChar == '#') {
        do
            LastChar = inputReader->getNextChar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return getTok();
    }

    if (LastChar == EOF)
        return tok::Eof;

    char ThisChar = LastChar;
    LastChar = inputReader->getNextChar();
    return ThisChar;
}


double Lexer::getNumVal() {
    return NumVal;
}


std::string Lexer::getIdentifierStr() {
    return IdentifierStr;
}


void Lexer::InitializeTokenMap() {
    TokenMap.emplace("struct",  tok::Struct);
    TokenMap.emplace("def",     tok::Def);
    TokenMap.emplace("extern",  tok::Extern);
}


} // End tsic namespace
