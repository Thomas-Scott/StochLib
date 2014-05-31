
/*
*  tau_leaping.cpp
*  
*/
#include "StochLib.h"
#include "boost_headers.h"

#include "ParallelIntervalSimulation.h"

using namespace StochLib;

void StochLib::tau_leaping_exp_adapt(std::string str)
{
	ParallelIntervalSimulation parallelDriver(str);
	parallelDriver.run();

	parallelDriver.mergeOutput();

	return ;
}
