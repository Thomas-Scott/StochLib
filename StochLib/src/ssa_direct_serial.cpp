/*
 *  ssa_direct_serial.cpp
 *  
 */
#include "boost_headers.h"

#include <iostream>
#include <string>
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "SSA_Direct.h"

#include "StochLib.h"
using namespace StochLib;

void StochLib::ssa_direct_serial(std::string str)
{

  typedef SSA_Direct<StandardDriverTypes::populationType,
    StandardDriverTypes::stoichiometryType, 
    StandardDriverTypes::propensitiesType,
    StandardDriverTypes::graphType> solverType;

  SerialIntervalSimulationDriver<solverType> driver(str);

  solverType solver=driver.createMassActionSolver();
  
  //set solver-specific parameters
  //none for ssa_direct

  driver.callSimulate(solver);

  driver.writeOutput();

  return;
}
