/*
*  ssa_odm.cpp
*  
*/

#include "StochLib.h"
#include "boost_headers.h"

#include "ParallelIntervalSimulation.h"

using namespace StochLib;

void StochLib::ssa_odm(std::string str)
{
	ParallelIntervalSimulation driver(str);
	driver.run();
	COUT << "Done.\n Merging output...\n";
	driver.mergeOutput();

	return ;
}
