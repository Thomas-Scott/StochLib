// [[Rcpp::depends(BH)]]
#include <Rcpp.h>
#include "DriverDecs.h"


RCPP_MODULE(StochLib){
	Rcpp::function( "ssaDirectSerial", &_ssaDirectSerial );
	Rcpp::function( "ssaNrmSerial", &_ssaNrmSerial );
	Rcpp::function( "ssaLdmSerial", &_ssaLdmSerial );
	Rcpp::function( "ssaConstantSerial", &_ssaConstantSerial );
	//Don't include parallel functions if no OpenMP support
	#if defined(_OPENMP)
	Rcpp::function( "parallelSSADirectSerial", &_parallel_ssaDirectSerial );
	Rcpp::function( "ssaOdm", &_ssaOdm );
	Rcpp::function( "ssaOdmSmall", &_ssaOdmSmall );
	Rcpp::function( "tauLeapingExpAdapt", &_tauLeapingExpAdapt );
	Rcpp::function( "tauLeapingExpAdaptSerial", &_tauLeapingExpAdaptSerial );
	#endif
}