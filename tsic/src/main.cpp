#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Parser.h"


int main() {
    fprintf(stderr, "ready> ");
    Parser::getNextToken();

    //// Run the main "interpreter loop" now.
    Parser::MainLoop();

    //// Print out all of the generated code.
    //TheModule->dump();

    return 0;
}