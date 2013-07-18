#ifndef __STOCHLIB__
#define __STOCHLIB__

#include "Model.h"
#include "Reaction.h"
#include "Output.h"

namespace StochLib{
	void parallelSSADirectSerial();
	void ssa_direct_serial(int ac, char* av[]);
	void ssaDirectSerial();
	void count();
}

#endif //__STOCHLIB__