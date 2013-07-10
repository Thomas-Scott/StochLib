#include "Model.h"
#include <cstdlib>
#include <iostream>
#include <fstream>


void Model::read(char* path){
	std::ifstream file;
	file.open(path);
	file >> iterations;
	file >> trials;
	file >> numSpecies;
	file >> numReactions;
	populations=new int[numSpecies];
	for (int i=0; i<numSpecies;i++){
		file>>populations[i];
	}
	reactions=new Reaction[numReactions];
	for (int i=0; i<numReactions;i++){
		file>>reactions[i].numReactants;
		reactions[i].reactants=new int[reactions[i].numReactants];
		reactions[i].rates=new int[reactions[i].numReactants];
		for (int j=0; j<reactions[i].numReactants;j++){
			file >> reactions[i].reactants[j];
			file >> reactions[j].rates[j];
		}
	}
	file.close();
	return;
}

int Model::getNumSpecies(){
	return numSpecies;
}

int Model::getIterations(){
	return iterations;
}

int Model::getTrials(){
	return trials;
}