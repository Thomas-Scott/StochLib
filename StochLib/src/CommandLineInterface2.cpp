/*
 *	Boost Replacement functions
 */
	char* getCmdOption(char ** begin, char ** end, const std::string & option){
	    char ** itr = std::find(begin, end, option);
	    if (itr != end && ++itr != end){
	        return *itr;
	    }
	    return 0;
	}

	bool cmdOptionExists(char** begin, char** end, const std::string& option){
    	return std::find(begin, end, option) != end;
	}

	std::vector<std::string> splitString( const std::string& str,char delim){
		std::vector<std::string> tokens;
        std::stringstream mySstream( str );
        std::string temp;

        while( getline( mySstream, temp, delim ) ) {
            tokens.push_back( temp );
        }
        return tokens;
	}

	char** tokenize( const std::string& str,int &ac, char delim )  {
        std::vector<std::string> tok
        char** cmdArray=new char*[tokens.size()];
        for (std::vector<int>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
        	char* s = new char[tokens[it].size()+1];
        	std::copy(tokens[it].begin(),tokens[it].end(),s);
        	s[tokens[it].size()]='\0';
        	cmdArray=s;
        }	
        ac=tokens.size();
        return cmdArray;
    } 

    void CommandLineInterface::parse_command_line(int ac, char* av[]){
    	if(cmdOptionExists(av, av+ac, "-m")){
    		char * modelName = getCmdOption(av,av+ac,"-m");
    		std::string name(modelName);
    		modelFileName=name;
	    	//vm.insert(std::pair<std::string,std::string>("model",name))
	    } else if (cmdOptionExists(av,av+ac,"--model")){
	    	char * modelName = getCmdOption(av,av+ac,"--model");
	    	std::string name(modelName);
	    	modelFileName=name;
	    	//vm.insert(std::pair<std::string,std::string>("model",name))
	    }

	    if(cmdOptionExists(av, av+ac, "-t")){
    		char * time = getCmdOption(av,av+ac,"-t");
    		double t = atof(time);
	    	//vm.insert(std::pair<std::string,double>("time",t))
	    } else if (cmdOptionExists(av,av+ac,"--time")){
	    	char * time = getCmdOption(av,av+ac,"--time");
	    	double t = atof(time);
	    	//vm.insert(std::pair<std::string,double>("time",time))
	    }

	    if(cmdOptionExists(av, av+ac, "-r")){
    		char * r = getCmdOption(av,av+ac,"-r");
    		std::istringstream iss(r);
    		iss >realizations;
	    	//vm.insert(std::pair<std::string,std::size_t>("realizations",name))
	    } else if (cmdOptionExists(av,av+ac,"--realizations")){
	    	char * r = getCmdOption(av,av+ac,"--realizations");
	    	std::istringstream iss(r);
    		iss >realizations;
	    	//vm.insert(std::pair<std::string,std::size_t>("realizations",name))
	    }

	    if(cmdOptionExists(av, av+ac, "-i")){
    		char * tmp = getCmdOption(av,av+ac,"-i");
    		std::istringstream iss(tmp);
    		iss >intervals;
	    } else if (cmdOptionExists(av,av+ac,"--intervals")){
	    	char * tmp = getCmdOption(av,av+ac,"--intervals");
	    	std::istringstream iss(tmp);
    		iss >intervals;
	    }

	    if(cmdOptionExists(av, av+ac, "-f") || cmdOptionExists(av,av+ac,"--force")){
	    	force = true;
	    } else {
	    	force = false;
	    }

	 	if(cmdOptionExists(av, av+ac, "-p")){
    		char * tmp = getCmdOption(av,av+ac,"-p");
    		std::istringstream iss(tmp);
    		iss >processes;
	    } else if (cmdOptionExists(av,av+ac,"--processes")){
	    	char * tmp = getCmdOption(av,av+ac,"--processes");
	    	std::istringstream iss(tmp);
    		iss >processes;
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
			std::cout << "StochKit ERROR (CommandLineInterface::parse): invalid value for epsilon.  Run with --help for more info.\n";
			exit(1);  
		}

		if(cmdOptionExists(av, av+ac, "--species")){
			std::string speciesList (getCmdOption(av,av+ac,"--species"));
    		species splitString(speciesList);
	    }


	    //TODO: fix out-dir function
	    /*
	    if (vm.count("out-dir")) {
		//create full path to output directory
		outputDir=boost::filesystem::system_complete(boost::filesystem::path(vm["out-dir"].as<std::string>())).string();
		}
		else {
		//create full path to output directory, default location, <full_path_to/model_filename (without extension)>_output
		std::string tmp_full_model_path=boost::filesystem::system_complete(modelFileName).string();
		outputDir=tmp_full_model_path.substr(0,tmp_full_model_path.find_last_of("."))+"_output";
		}

	    */
	    if(cmdOptionExists(av,av+ac,"--out-dir")){
	    	char * output = getCmdOption(av,av+ac,"-m");
    		std::string out(output);
    		outputDir = out;
	    }

	    if(cmdOptionExists(av, av+ac, "--no-recompile")){
    		recompile = false;
	    } else {
	    	recompile = true;
	    }

	    /* TODO: port this

	std::string full_model_path=boost::filesystem::system_complete(modelFileName).string();
	generatedCodeDir=full_model_path.substr(0,full_model_path.find_last_of("."))+"_generated_code";
	
		*/


		if(cmdOptionExists(av, av+ac, "--use-existing-output-dirs")){
    		useExistingOutputDirs = false;
	    } else {
	    	useExistingOutputDirs = true;
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
						std::cout << "StochKit ERROR (CommandLineInterface::parse): species index \""<<index<<"\" larger than number of species (Note: indices start at 0, so largest index is "<<modelSpeciesList.size()-1<<")\n";
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
    }

	CommandLineInterface::CommandLineInterface(std::string str){
		int ac;
		char** av=tokenize(str,ac,' ');
		std::string temp_dir;
		

	}


  