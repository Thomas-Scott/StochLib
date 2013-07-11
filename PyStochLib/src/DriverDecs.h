#include "StochLib.h"
#include <string>

#ifndef __DRIVER_DECS__
#define __DRIVER_DECS__
using namespace StochLib;

#if defined(_OPENMP)
//[[Rcpp::Export]]
void _parallel_ssaDirectSerial(std::string str){
	char* modelName = new char[str.size()+1];
	std::copy(str.begin(), str.end(), modelName);
	modelName[str.size()] = '\0';
	Model model;
	model.read(modelName);
	parallelSSADirectSerial();
	delete [] modelName;
	return;
}
#endif

//[[Rcpp::Export]]
void _ssaDirectSerial(std::string str){
	char* modelName = new char[str.size()+1];
	std::copy(str.begin(), str.end(), modelName);
	modelName[str.size()] = '\0';
	Model model;
	model.read(modelName);
	ssaDirectSerial();
	delete [] modelName;
	return;
}

//[[Rcpp::Export]]
void _count(){
	count();
	return;
}

#endif //__DRIVER_DECS__