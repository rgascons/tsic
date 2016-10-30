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

	Parser parser;
	Lexer lexer;
}

} // End tsic namespace


#endif