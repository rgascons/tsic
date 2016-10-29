#ifndef __TAISEI_LEXER__
#define __TAISEI_LEXER__

#include <string>
#include <unordered_map>


namespace tsic {

class Lexer
{
public:
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

    int LastChar;
};

} // End tsic namespace


#endif