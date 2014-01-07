/*
 *	Boost Replacement functions
 */
#include "CommandLineInterface.h"

 namespace StochLib{ 
std::string CommandLineInterface::getGeneratedCodeDir() const {
	return generatedCodeDir;
}

std::string CommandLineInterface::getModelFileName() const {
	return modelFileName;
}

double CommandLineInterface::getSimulationTime() const {
	return simulationTime;
}

std::size_t CommandLineInterface::getRealizations() const {
	return realizations;
}

std::size_t CommandLineInterface::getIntervals() const {
	return intervals;
}

bool CommandLineInterface::getUseSeed() const {
	return useSeed;
}

int CommandLineInterface::getSeed() const {
	return seed;
}

bool CommandLineInterface::getKeepStats() const {
	return keepStats;
}

bool CommandLineInterface::getKeepTrajectories() const {
	return keepTrajectories;
}

bool CommandLineInterface::getKeepHistograms() const {
	return keepHistograms;
}

std::size_t CommandLineInterface::getHistogramBins() const {
	return histogramBins;
}

double CommandLineInterface::getEpsilon() const {
	return epsilon;
}

std::size_t CommandLineInterface::getThreshold() const {
	return threshold;
}

std::size_t CommandLineInterface::getSSASteps() const {
	return SSASteps;
}

/*
std::vector<std::string> CommandLineInterface::getSpecies() const {
return species;
}
*/

std::size_t CommandLineInterface::getProcesses() const {
	return processes;
}

std::vector<std::size_t> CommandLineInterface::getSpeciesSubset() const {
	return speciesSubset;
}

bool CommandLineInterface::getLabel() const {
	return label;
}

std::vector<std::string> CommandLineInterface::getSpeciesNames() const {
	return speciesNames;
}

std::string CommandLineInterface::getOutputDir() const {
	return outputDir;
}

bool CommandLineInterface::getUseExistingOutputDirs() const {
	return useExistingOutputDirs;
}

bool CommandLineInterface::getForce() const {
	return force;
}

std::string CommandLineInterface::getStatsDir() const {
	return statsDir;
}
std::string CommandLineInterface::getMeansFileName() const {
	return meansFileName;
}
std::string CommandLineInterface::getVariancesFileName() const {
	return variancesFileName;
}

std::string CommandLineInterface::getStatsInfoFileName() const {
	return statsInfoFileName;
}

std::string CommandLineInterface::getHistogramsInfoFileName() const {
	return histogramsInfoFileName;
}

std::string CommandLineInterface::getTrajectoriesDir() const {
	return trajectoriesDir;
}
std::size_t CommandLineInterface::getTrajectoriesOffset() const {
	return trajectoriesOffset;
}
std::string CommandLineInterface::getHistogramsDir() const {
	return histogramsDir;
}

bool CommandLineInterface::getRecompile() const {
	return recompile;
}

std::string CommandLineInterface::getCmdArgs() const {
	return cmdArgs;
}


char* CommandLineInterface::getCmdOption(char ** begin, char ** end, const std::string & option){
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end){
        return *itr;
    }
    return 0;
}

bool CommandLineInterface::cmdOptionExists(char** begin, char** end, const std::string& option){
	return std::find(begin, end, option) != end;
}

std::vector<std::string> CommandLineInterface::getCmdOptionList(char ** begin, char ** end, const std::string & option){
    char ** itr = std::find(begin, end, option);
    std::string tmp;
    std::vector<std::string> list;
    bool last=false;
    while(!last && itr != end){
            if (itr != end && ++itr != end){
                    tmp = *itr;

                    if (tmp[0] == '-') {
                            last=true;
                    } else {
                            list.push_back(tmp);
                    }
            	Rcpp::Rcout << "species:" << tmp <<std::endl;
            }
            
    }
    return list;
}

std::vector<std::string> CommandLineInterface::splitString( const std::string& str){
	std::string buf; 
    std::stringstream ss(str); 
    std::vector<std::string> tokens;
    while (ss >> buf)
        tokens.push_back(buf);
        return tokens;
}

char ** CommandLineInterface::parseString(std::string str,int &ac){
    	std::vector<std::string> vec =splitString(str);
    	ac = vec.size();
    	char ** arr = new char*[ac];
		for(size_t i = 0; i < ac; i++){
	    	arr[i] = new char[vec[i].size() + 1];
	    	strcpy(arr[i], vec[i].c_str());
		}
	return arr;
}


    void CommandLineInterface::parse_command_line(int ac, char* av[]){


    	if(cmdOptionExists(av, av+ac, "-m")){
    		char * modelName = getCmdOption(av,av+ac,"-m");
    		std::string name(modelName);
    		modelFileName=name;
	    } else if (cmdOptionExists(av,av+ac,"--model")){
	    	char * modelName = getCmdOption(av,av+ac,"--model");
	    	std::string name(modelName);
	    	modelFileName=name;
	    }
	   	//COUT << "Model: " << modelFileName <<std::endl;

	    if(cmdOptionExists(av, av+ac, "-t")){
    		char * time = getCmdOption(av,av+ac,"-t");
    		double t = atof(time);
    		simulationTime=t;
	    } else if (cmdOptionExists(av,av+ac,"--time")){
	    	char * time = getCmdOption(av,av+ac,"--time");
	    	double t = atof(time);
	    	simulationTime=t;
	    }

	    if(cmdOptionExists(av, av+ac, "-r")){
    		char * r = getCmdOption(av,av+ac,"-r");
    		std::istringstream iss(r);
    		iss >>realizations;
    		iss.str(std::string());
	    } else if (cmdOptionExists(av,av+ac,"--realizations")){
	    	char * r = getCmdOption(av,av+ac,"--realizations");
	    	std::istringstream iss(r);
    		iss >>realizations;
    		iss.str(std::string());
	    }

	    //COUT << "Realizations:" << realizations <<"\n";
	    //COUT.flush();


	    if(cmdOptionExists(av, av+ac, "-i")){
    		char * tmp = getCmdOption(av,av+ac,"-i");
    		std::istringstream iss(tmp);
    		iss >>intervals;
    		iss.str(std::string());
	    } else if (cmdOptionExists(av,av+ac,"--intervals")){
	    	char * tmp = getCmdOption(av,av+ac,"--intervals");
	    	std::istringstream iss(tmp);
    		iss >>intervals;
	    	iss.str(std::string());
	    } else {
	    	intervals = 0;
	    }

	    if(cmdOptionExists(av, av+ac, "-f") || cmdOptionExists(av,av+ac,"--force")){
	    	force = true;
	    } else {
	    	force = false;
	    }

	 	if(cmdOptionExists(av, av+ac, "-p")){
    		char * tmp = getCmdOption(av,av+ac,"-p");
    		std::istringstream iss(tmp);
    		iss >>processes;
	    } else if (cmdOptionExists(av,av+ac,"--processes")){
	    	char * tmp = getCmdOption(av,av+ac,"--processes");
	    	std::istringstream iss(tmp);
    		iss >>processes;
	    } else {
	    	processes = 0;
	    }

	    if(cmdOptionExists(av, av+ac, "--epsilon")){
    		char * ep = getCmdOption(av,av+ac,"--epsilon");
	    	double e = atof(ep);
	    	epsilon = e;
	    } else {
	    	epsilon = 0.03;
	    }

	    if(cmdOptionExists(av, av+ac, "--bins")){
    		char * b = getCmdOption(av,av+ac,"--bins");
	    	double bins = atof(b);
	    	histogramBins = bins;
	    } else {
	    	histogramBins = 32;
	    }

	    if(cmdOptionExists(av, av+ac, "--ssa-steps")){
    		char * s = getCmdOption(av,av+ac,"--ssa-steps");
	    	double steps = atof(s);
	    	SSASteps = steps;
	    } else {
	    	SSASteps = 100;
	    }

	    if(cmdOptionExists(av, av+ac, "--trajectories-offset")){
    		char * t = getCmdOption(av,av+ac,"--trajectories-offset");
	    	double offset = atof(t);
	    	trajectoriesOffset = offset;
	    } else {
	    	trajectoriesOffset = 0;
	    }

	    if(cmdOptionExists(av, av+ac, "--threshold")){
    		char * thresh = getCmdOption(av,av+ac,"--threshold");
	    	double t = atof(thresh);
	    	threshold = t;
	    } else {
	    	threshold = 10;
	    }

	    if(cmdOptionExists(av, av+ac, "--seed")){
    		useSeed = true;
	    } else {
	    	useSeed = false;
	    }

	    if(cmdOptionExists(av, av+ac, "--keep-trajectories")){
    		keepTrajectories = true;
	    } else {
	    	keepTrajectories = false;
	    }

	    if(cmdOptionExists(av, av+ac, "--keep-histograms")){
    		keepHistograms = true;
	    } else {
	    	keepHistograms = false;
	    }

	    if(cmdOptionExists(av, av+ac, "--label")){
    		label = true;
	    } else {
	    	label = false;
	    }

	    if(cmdOptionExists(av, av+ac, "--no-stats")){
    		keepStats = false;
	    } else {
	    	keepStats = true;
	    }

	    if (epsilon<=0.0 || epsilon>=1.0) {
			COUT << "StochKit ERROR (CommandLineInterface::parse): invalid value for epsilon.  Run with --help for more info.\n";
			exit(1);
		}

		if(cmdOptionExists(av, av+ac, "--species")){
			species = getCmdOptionList(av,av+ac,"--species");
	    }

	    if(cmdOptionExists(av,av+ac,"--out-dir")){
	    	char * output = getCmdOption(av,av+ac,"--out-dir");
    		std::string out(output);
    		outputDir = "/Users/scotthom15/"+out;
	    } else {
	    	outputDir = "/Users/scotthom15/output";
	    }
	    
	    if(cmdOptionExists(av,av+ac,"--stats-dir")){
	    	char * s = getCmdOption(av,av+ac,"--stats-dir");
    		std::string stats(s);
    		statsDir = stats;
	    } else {
	    	statsDir = "stats";
	    }

	    if(cmdOptionExists(av,av+ac,"--means-file")){
	    	char * m = getCmdOption(av,av+ac,"--means-file");
    		std::string means(m);
    		meansFileName = means;
	    } else {
	    	meansFileName = "means.txt";
	    }

	    if(cmdOptionExists(av,av+ac,"--variances-file")){
	    	char * v = getCmdOption(av,av+ac,"--variances-file");
    		std::string vars(v);
    		variancesFileName = vars;
	    } else {
	    	variancesFileName = "variances.txt";
	    }

	    if(cmdOptionExists(av,av+ac,"--stats-info-file")){
	    	char * s = getCmdOption(av,av+ac,"--stats-info-file");
    		std::string str(s);
    		statsInfoFileName = str;
	    } else {
	    	statsInfoFileName = ".stats-info.txt";
	    }

	    if(cmdOptionExists(av,av+ac,"--trajectories-dir")){
	    	char * s = getCmdOption(av,av+ac,"--trajectories-dir");
    		std::string str(s);
    		trajectoriesDir = str;
	    } else {
	    	trajectoriesDir = "trajectories";
	    }

	    if(cmdOptionExists(av,av+ac,"--trajectories-offset")){
	    	char * s = getCmdOption(av,av+ac,"--trajectories-offset");
    		double offset = atof(s);
    		trajectoriesOffset = offset;
	    } else {
	    	trajectoriesOffset = 0;
	    }

	    if(cmdOptionExists(av,av+ac,"--histograms-dir")){
	    	char * s = getCmdOption(av,av+ac,"--histograms-dir");
    		std::string str(s);
    		histogramsDir = str;
	    } else {
	    	histogramsDir = "histograms";
	    }

	    if(cmdOptionExists(av,av+ac,"--histograms-info-file")){
	    	char * s = getCmdOption(av,av+ac,"--histograms-info-file");
    		std::string str(s);
    		histogramsInfoFileName = str;
	    } else {
	    	histogramsInfoFileName = "";
	    }



	    if(cmdOptionExists(av, av+ac, "--no-recompile")){
    		recompile = false;
	    } else {
	    	recompile = true;
	    }

	    /* TODO: port this for future mixed, events, and other support

	std::string full_model_path=boost::filesystem::system_complete(modelFileName).string();
	generatedCodeDir=full_model_path.substr(0,full_model_path.find_last_of("."))+"_generated_code";
	
		*/


		if(cmdOptionExists(av, av+ac, "--use-existing-output-dirs")){
    		useExistingOutputDirs = true;
	    } else {
	    	useExistingOutputDirs = false;
	    }	    
	    char* modelFile;
		modelFile=const_cast<char*>(modelFileName.c_str());
		Input_tag<ModelTag> input_model_tag(modelFile);
		ModelTag model_tag = input_model_tag.writeModelTag();
		std::vector<std::string> modelSpeciesList=model_tag.SpeciesList;

		if (species.size()!=0) {//we need to create a species subset vector and set it in output object

			//loop over command line species list
			//if it's an index (a number), store it in the list of species indexes
			//if it's a species id (species name), look up it's index in the modelSpeciesList
			for (std::size_t i=0; i!=species.size(); ++i) {
				std::istringstream iss(species[i]);
				std::size_t index;
				iss >> index;
				if (iss.fail()) {
					for (std::size_t j=0; j!=modelSpeciesList.size(); ++j) {
						if (species[i].compare(modelSpeciesList[j])==0) {
							speciesSubset.push_back(j);
							break;
						}
					}
				}
				else {
					if (index<modelSpeciesList.size()) {
						speciesSubset.push_back(index);
					}
					else {
						COUT << "StochKit ERROR (CommandLineInterface::parse): species index \""<<index<<"\" larger than number of species (Note: indices start at 0, so largest index is "<<modelSpeciesList.size()-1<<")"<<std::endl;
						exit(1);
					}
				}
			}

		}
		
		//create vector of species names

		if (speciesSubset.size()==0) {//if keeping all species, use species label vector from model_tag
			speciesNames=modelSpeciesList;
		}
		else {//we're using a species subset, so we need to create the appropriate species label subset
			DenseVectorSubset<std::vector<std::string> > labelSubset(speciesSubset);
			speciesNames=labelSubset.getSubset(modelSpeciesList);
		}
		/*
		#ifdef WIN32
			//find the model file path and add quote for window version
			//for "-m"
			std::string serchingString="-m "+modelFileName;
			std::string replaceString="-m "+(std::string)"\""+modelFileName+(std::string)"\"";
			int index=cmdArgs.find(serchingString, 0);
			if(index!=std::string::npos)
				cmdArgs.replace(index, serchingString.size(), replaceString); 
			//for "--model"
			serchingString="--model "+modelFileName;
			replaceString="-m "+(std::string)"\""+modelFileName+(std::string)"\"";
			index=cmdArgs.find(serchingString, 0);
			if(index!=std::string::npos)
				cmdArgs.replace(index, serchingString.size(), replaceString);
			//for "--out-dir"
			serchingString="--out-dir "+temp_dir;
			replaceString="--out-dir "+(std::string)"\""+temp_dir+(std::string)"\"";
			index=cmdArgs.find(serchingString, 0);
			if(index!=std::string::npos)
				cmdArgs.replace(index, serchingString.size(), replaceString); 
		#endif
		*/
    }
    
	CommandLineInterface::CommandLineInterface(std::string str){
		int ac;
		cmdArgs = str;
		char ** command = parseString(str,ac);
		parse_command_line(ac,command);
	}
}

  