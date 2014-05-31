/*
 *  
 */
 
#include "StochLib.h"
#include "boost_headers.h"

#include <iostream>
#include <string>
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "SSA_NRM.h"

using namespace StochLib;

void StochLib::ssa_nrm_serial(std::string str)
{

  typedef SSA_NRM<StandardDriverTypes::populationType,
    StandardDriverTypes::stoichiometryType, 
    StandardDriverTypes::propensitiesType,
    StandardDriverTypes::graphType> solverType;

  SerialIntervalSimulationDriver<solverType> driver(str);

  solverType solver=driver.createMassActionSolver();
  
  //set solver-specific parameters
  //none for ssa_ldm

  driver.callSimulate(solver);

  driver.writeOutput();

  return ;
}
