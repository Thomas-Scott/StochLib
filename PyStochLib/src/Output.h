#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef __OUTPUT__
#define __OUTPUT__

class Output{
	int ** states;
	int numStates;
	int numSpecies;
  public:
	Output(int numStates,int numSpecies); 
	~Output(); 
  	void addState(int timestep, int * s);
  	void print(char* path);
};


#endif // __OUTPUT__