#ifndef __STOCHLIB__
#define __STOCHLIB__
#include <string>

namespace StochLib{
	void ssa_direct_serial(std::string str);
	void parallelSSADirectSerial(std::string str);
	void count();
}

#endif //__STOCHLIB__