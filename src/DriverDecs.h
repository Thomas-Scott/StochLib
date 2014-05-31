#include "StochLib.h"

#ifndef __DRIVER_DECS__
#define __DRIVER_DECS__
using namespace StochLib;

//[[Rcpp::Export]]
void _ssaDirectSerial(std::string str){
	ssa_direct_serial(str);
	return;
}
//[[Rcpp::Export]]
void _ssaConstantSerial(std::string str){
	ssa_constant_serial(str);
	return;
}
//[[Rcpp::Export]]
void _ssaNrmSerial(std::string str){
	ssa_nrm_serial(str);
	return;
}

//[[Rcpp::Export]]
void _ssaLdmSerial(std::string str){
	ssa_ldm_serial(str);
	return;
}

#if defined(_OPENMP)
//[[Rcpp::Export]]
void _parallel_ssaDirectSerial(std::string str){
	parallelSSADirectSerial(str);
}
//[[Rcpp::Export]]
void _ssaOdm(std::string str){
	ssa_odm(str);
	return;
}
//[[Rcpp::Export]]
void _ssaOdmSmall(std::string str){
	ssa_odm_small(str);
	return;
}
//[[Rcpp::Export]]
void _tauLeapingExpAdaptSerial(std::string str){
	tau_leaping_exp_adapt_serial(str);
	return;
}
//[[Rcpp::Export]]
void _tauLeapingExpAdapt(std::string str){
	tau_leaping_exp_adapt(str);
	return;
}
#endif //_OPENMP 


#endif //__DRIVER_DECS__