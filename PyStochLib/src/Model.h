#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Reaction.h"

#ifndef __MODEL__
#define __MODEL__

class Model{
	int iterations,trials;
	int numSpecies;
	int * populations;
	int numReactions;
	Reaction * reactions;
  public:
  	void read(char* path);
  	int getNumSpecies();
  	int getIterations();
  	int getTrials();
  	Reaction getReaction(int id);
  	void ssaDirectSerial();
  	void parallelSSADirectSerial();
};


#endif //__MODEL__