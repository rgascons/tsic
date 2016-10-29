#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "tsic/tsic.h"
#include "tsic/tsici.h"
#include "Utils/InputParser.h"

int main(int argc, char** argv) {
	InputParser input(argc, argv);

	tsic::tsic *compiler;
	int compiler_output;

	if(input.cmdOptionExists("-i") || input.cmdOptionExists("interactive")) {
		compiler = new TsicInteractive();
	} else {
		compiler = new Tsic();
	}

	compiler_output = compiler->setOptions(input);

	if(compiler_output != 0)
		delete compiler;
		return compiler_output;

	compiler_output = compiler->run();

	if(compiler_output != 0)
		delete compiler;
		return compiler_output;

	delete compiler;
    return 0;
}