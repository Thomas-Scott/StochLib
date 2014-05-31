#ifndef __STOCHLIB__
#define __STOCHLIB__
#include <string>

namespace StochLib{
	void ssa_direct_serial(std::string str);
	void parallelSSADirectSerial(std::string str);
	void count();
	void ssa_odm_small(std::string str);
	void ssa_odm(std::string str);
	void tau_leaping_exp_adapt(std::string str);
	void tau_leaping_exp_adapt_serial(std::string str);
	void ssa_constant_serial(std::string str);
	void ssa_nrm_serial(std::string str);
	void ssa_ldm_serial(std::string str);
}

#endif //__STOCHLIB__
