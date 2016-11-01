#ifndef __TSIC_TSIC__
#define __TSIC_TSIC__

#include "tsic/tsic.h"


namespace tsic {

class TsicInteractive : public Tsic {
public:
	TsicInteractive();
	~TsicInteractive();

	int run();
}


}

#endif