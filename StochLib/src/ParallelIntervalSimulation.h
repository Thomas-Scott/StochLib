/******************************************************************************
 */

#ifndef _PARALLEL_INTERVAL_SIMULATION_H_
#define _PARALLEL_INTERVAL_SIMULATION_H_

#include "Input_mass_action.h"
#include "CommandLineInterface.h"
#include "StandardDriverTypes.h"
#include "StandardDriverUtilities.h"
//#include "Input_mixed_before_compile.h"
//#include "Input_events_before_compile.h"
#include "IntervalOutput.h"
#include "StatsOutput.h"
#include "HistogramSingle.h"
#include "boost/bind.hpp"
#include "boost/random.hpp"
#include "boost/random/uniform_int.hpp"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <sys/time.h>
#include <vector>
#include "StdOutputHandler.h"
#include <string>
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "SSA_Direct.h"

#include <omp.h>
#ifdef WIN32
#include <windows.h>
#include <fstream>
#endif



namespace StochLib
{

class ParallelIntervalSimulation
{
	
public:
  ParallelIntervalSimulation(std::string);

  void run(std::string executableName);

  std::size_t assignment(std::size_t totalRealizationss, std::size_t threadid);

  void mergeOutput();

  void warnIfLargeOutput();//helper function that prints a warning if simulation will generate a lot of data

  static std::string modifyCmdArgsRealizations(std::string commandLineArguments, std::string subRealizations);
  static std::string modifyCmdArgsSeed(std::string commandLineArguments, std::string newSeed);
private:
  void _parallel_ssaDirectSerial_subdriver(std::string str);

protected:
  CommandLineInterface commandLine;
  std::size_t threadct;

  //records how many realizations were assigned to each processor
  std::vector<std::size_t> processorRealizationAssignments;
  std::size_t masterProc;

  int seedOfSeed;
  boost::mt19937 engine ;
  std::size_t numberOfWorkers;
};

}

#endif
