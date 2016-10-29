#ifndef __TSIC_UTILS_SOURCELOCATION__
#define __TSIC_UTILS_SOURCELOCATION__

#include "Utils/Path.h"

namespace tsic {

class SourceLocation {
public:
	SourceLocation(Path path, int line, int column);

private:
	Path path;
	int line;
	int column;
}

} // End tsic namespace

#endif