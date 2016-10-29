#ifndef __TSIC_TSIC__
#define __TSIC_TSIC__

namespace tsic {

class Tsic {
public:
	Tsic();
	~Tsic();

	int setOptions(const InputParser &input);
	int run();

protected:
	InputParser &input;

	// Pointer to the parser
	Parser *parser;

	// Pointer to the lexer
	Lexer *lexer;
}

} // End tsic namespace


#endif