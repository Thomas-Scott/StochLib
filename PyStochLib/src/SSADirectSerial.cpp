#include "StochLib.h"
#include <cstdlib>
#include <fstream>

using namespace StochLib;


void StochLib::ssaDirectSerial(){
	std::ofstream out;
	out.open("~/counting.txt");
	#pragma omp parallel num_threads(8)
	{
		#pragma omp for
		for(int i =0;i<1000;i++){
			out<<i<<std::endl;
		}
	}
	out.close();
	return;
}


void StochLib::parallelSSADirectSerial(){
	ssaDirectSerial();
	return;
}

void StochLib::count(){
	std::ofstream out;
	out.open("counting.txt");
	#pragma omp parallel num_threads(8)
	{
		#pragma omp for
		for(int i =0;i<1000;i++){
			out<<i<<std::endl;
		}
	}
	out.close();
	return;
}