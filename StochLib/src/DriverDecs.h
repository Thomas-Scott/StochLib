#include "StochLib.h"

#ifndef __DRIVER_DECS__
#define __DRIVER_DECS__
using namespace StochLib;

#if defined(_OPENMP)
//[[Rcpp::Export]]
void _parallel_ssaDirectSerial(std::string str){
	parallelSSADirectSerial(str);
}
#endif //_OPENMP 

//[[Rcpp::Export]]
void _ssaDirectSerial(std::string str){
	ssa_direct_serial(str);
	return;
}

//[[Rcpp::Export]]
void _count(){
	count();
	return;
}

#endif //__DRIVER_DECS__