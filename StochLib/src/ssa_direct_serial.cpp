/*
 *  ssa_direct_serial.cpp
 *  
 */
#include "boost_headers.h"

#include "StdOutputHandler.h"

#include <string>
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "SSA_Direct.h"

#include "StochLib.h"
using namespace StochLib;

void StochLib::ssa_direct_serial(std::string str) {

  typedef SSA_Direct<StandardDriverTypes::populationType,
    StandardDriverTypes::stoichiometryType, 
    StandardDriverTypes::propensitiesType,
    StandardDriverTypes::graphType> solverType;
  SerialIntervalSimulationDriver<solverType> driver(str);
  solverType solver=driver.createMassActionSolver();
  driver.callSimulate(solver);
  driver.writeOutput();

  return;
}
