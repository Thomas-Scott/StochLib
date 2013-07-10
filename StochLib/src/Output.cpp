#include "Output.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


Output::Output(int n,int s){
	numSpecies = n;
	numStates = s;
	states=new int*[numStates];
	for (int i=0; i<numStates;i++){
		states[i] = new int[numSpecies];
	}
	return;
}

Output::~Output(){
	for (int i=0; i<numStates;i++){
		delete [] states[i];
	}
	delete [] states;
	return;
}

void Output::addState(int timestep, int* s){
	for (int i=0; i<numSpecies;i++){
		states[timestep][i]=s[i];
	}
	return;
}

void Output::print(char * outPath){
	ofstream outFile;
	outFile.open(outPath);
	for (int i=0; i<numStates;i++){
		outFile << i << ",";
		for (int j=0; j<numSpecies;j++){
			outFile << j << ",";
		}
		outFile << endl;
	}
	outFile.close();
	return;
}