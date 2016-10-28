#include "Lexer.h"


bool Lexer::bTokenMapInitialized = false;
int  Lexer::LastChar = ' ';

std::unordered_map<std::string, Token> Lexer::TokenMap;
double Lexer::NumVal;
std::string Lexer::IdentifierStr;


Token Lexer::getTok() {
    if (!bTokenMapInitialized) {
        InitializeTokenMap();
        bTokenMapInitialized = true;
    }

    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        std::unordered_map<std::string, Token>::const_iterator t_it;
        t_it = TokenMap.find(IdentifierStr);

        if (t_it == TokenMap.end())
            return tok_identifier;
        else
            return t_it->second;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;

        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if (LastChar == '#') {
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return getTok();
    }

    if (LastChar == EOF)
        return tok_eof;

    int ThisChar = LastChar;
    LastChar = getchar();
    return (Token)ThisChar;
}

double Lexer::getNumVal() {
    return NumVal;
}

std::string Lexer::getIdentifierStr() {
    return IdentifierStr;
}

void Lexer::InitializeTokenMap() {
    TokenMap.emplace("struct",  tok_struct);
    TokenMap.emplace("def",     tok_def);
    TokenMap.emplace("extern",  tok_extern);
}