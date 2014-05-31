
#include "StochLib.h"
#include <cstdlib>
#include <fstream>
#include <string>


#include "boost_headers.h"
#include "StdOutputHandler.h"
#include "StandardDriverTypes.h"
#include "SerialIntervalSimulationDriver.h"
#include "SSA_Direct.h"
#include "ParallelIntervalSimulation.h"


using namespace StochLib;

#if defined(_OPENMP)
void StochLib::parallelSSADirectSerial(std::string str){
  typedef SSA_Direct<StandardDriverTypes::populationType,
    StandardDriverTypes::stoichiometryType, 
    StandardDriverTypes::propensitiesType,
    StandardDriverTypes::graphType> solverType;
  ParallelIntervalSimulation driver(str);
  driver.run();
  COUT << "Done.\n Merging output...\n";
  driver.mergeOutput();
  //driver.mergeSerialOutput();
}
#endif //_OPENMP_