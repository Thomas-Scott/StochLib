/*
 *  ssa_direct_serial.cpp
 *  
 */
#include "boost_headers.h"
#include <Rcpp.h>
#include <iostream>
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
  Rcpp::Rcout << "Defined driver."<<std::endl;
  SerialIntervalSimulationDriver<solverType> driver(str);
  Rcpp::Rcout << "Made driver."<<std::endl;
  solverType solver=driver.createMassActionSolver();
  Rcpp::Rcout << "Created Mass Action Solver."<<std::endl;
  Rcpp::Rcout << "Ready to simulate." <<std::endl;
  driver.callSimulate(solver);
  Rcpp::Rcout << "Simulated."<<std::endl;
  driver.writeOutput();
  Rcpp::Rcout << "Done."<<std::endl;

  return;
}
