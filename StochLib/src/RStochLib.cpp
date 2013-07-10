#include <Rcpp.h>
#include "DriverDecs.h"

RCPP_MODULE(StochLib){
	Rcpp::function( "ssaDirectSerial", &_ssaDirectSerial );
	Rcpp::function( "parallelSSADirectSerial", &_parallel_ssaDirectSerial );
	Rcpp::function( "count", &_count );
}
