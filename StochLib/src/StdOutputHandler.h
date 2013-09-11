#ifndef __STD_OUTPUT_HANDLER__
#define __STD_OUTPUT_HANDLER__

#ifdef RBUILD
#include <Rcpp.h>
	#ifndef COUT
	#define COUT Rcpp::Rcout
	#define CERR Rcpp::Rcerr
	#endif
#else
#include <iostream>
	#ifndef COUT
	#define COUT std::cout
	#define CERR std::cerr
	#endif
#endif 

#endif //__STD_OUTPUT_HANDLER__