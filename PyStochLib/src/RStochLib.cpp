#include <Rcpp.h>
#include "DriverDecs.h"

RCPP_MODULE(StochLib){
	Rcpp::function( "ssaDirectSerial", &_ssaDirectSerial );
	Rcpp::function( "count", &_count );
	//Don't include parallel functions if no OpenMP
	#if defined(_OPENMP)
	Rcpp::function( "parallelSSADirectSerial", &_parallel_ssaDirectSerial );
	#endif
}
