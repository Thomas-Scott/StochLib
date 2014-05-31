/*
 *  tau_leaping_serial.cpp
 *  
 */
#include "boost_headers.h"

#include <iostream>
#include <string>
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "TauLeapingExplicitAdaptive.h"
#include "CommandLineInterface.h"

using namespace StochLib;

void StochLib::tau_leaping_exp_adapt_serial(std::string str)
{

  typedef TauLeapingExplicitAdaptive<StandardDriverTypes::populationType,
    StandardDriverTypes::stoichiometryType, 
    StandardDriverTypes::propensitiesType,
    StandardDriverTypes::graphType> solverType;

  SerialIntervalSimulationDriver<solverType> driver(str);

// Not working yet, can't get implementation of TauLeapingExplicitAdaptive to find the uBLAS functions
  // solverType solver=driver.createMassActionSolver();
  
  // //set solver-specific parameters
  // solver.setEpsilon(driver.getCommandLine().getEpsilon());
  // solver.setThreshold(driver.getCommandLine().getThreshold());
  // solver.setSSASteps(driver.getCommandLine().getSSASteps());

  // driver.callSimulate(solver);

  // driver.writeOutput();

  return ;
}
