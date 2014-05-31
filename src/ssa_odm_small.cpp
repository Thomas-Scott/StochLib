/*
* ssa_odm_small.cpp 
*  
*/

#include "StochLib.h"
#include "boost_headers.h"

#include "ParallelIntervalSimulation.h"

using namespace StochLib;

void StochLib::ssa_odm_small(std::string str)
{
	ParallelIntervalSimulation parallelDriver(str);
	parallelDriver.run();
	COUT << "Done.\n Merging output...\n";
	parallelDriver.mergeOutput();

	return ;
}
