#ifndef __TAISEI_UTILS_FILEREADER__
#define __TAISEI_UTILS_FILEREADER__

#include <fstream>

#include "Utils/Path.h"

namespace tsic {


class InputReader {
public:
	InputReader();

protected:
	char _currChar;

public:
	virtual char getNextChar() = 0;
};


class FileReader : public InputReader {
public:
	FileReader(std::string strpath);
	FileReader(Path path);

	~FileReader();

private:
	std::streampos filePos;
	std::ifstream inputFile;

	bool _initialized;

	long long int length; // Length of file

public:
	virtual char getNextChar() override;
};


} // End tsic namespace


#endif
