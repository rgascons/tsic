#ifndef __TSIC_TSIC__
#define __TSIC_TSIC__

#include "tsic/tsic.h"

class TsicInteractive : public Tsic {
public:
	TsicInteractive();
	~TsicInteractive();

	int run();
}

#endif