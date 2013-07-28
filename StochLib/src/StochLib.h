#ifndef __STOCHLIB__
#define __STOCHLIB__
#include <string>

namespace StochLib{
	void parallelSSADirectSerial();
	void ssa_direct_serial(int ac, char* av[]);
	void ssaDirectSerial();
	void ssa_direct_serial(std::string str);
	void count();
}

#endif //__STOCHLIB__