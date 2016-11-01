#include "Utils/InputReaders.h"


namespace tsic {


FileReader::FileReader(std::string strpath) {
	Path path = Path(strpath);
	//FileReader(path);
}


FileReader::FileReader(Path path) : 
	_initialized(false),
	filePos(0)
{

}


FileReader::~FileReader() {
	inputFile.close();
}


char FileReader::getNextChar() {
	if(inputFile.is_open()) {
		inputFile.seekg(filePos);
		inputFile >> _currChar;
		filePos = (int)filePos + 1;
	}
}


} // End tsic namespace
