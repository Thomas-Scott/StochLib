#include "StandardDriverUtilities.h"

namespace StochLib
{
	bool StandardDriverUtilities::dirIsDir(const std::string& outputDir) {
		#ifdef WIN32
		DWORD fileAtt = GetFileAttributesA(filePath);
		if(fileAtt == INVALID_FILE_ATTRIBUTES) 
			throw GetLastError();
		return ((fileAtt & FILE_ATTRIBUTE_DIRECTORY) == 0);
		#else
		struct stat sb;
  		if (stat(outputDir.c_str(), &sb) == 0){
			return S_ISDIR(sb.st_mode);
		}
		#endif
	}

	bool StandardDriverUtilities::dirExists(const std::string& outputDir) {
		#ifdef WIN32
		DWORD ftyp = GetFileAttributesA(outputDir.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES) return false; 
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
  		return false;
  		#else
  		struct stat sb;

  		if (stat(outputDir.c_str(), &sb) == 1 && S_ISDIR(sb.st_mode)){
			return true;
		} else {
			return false;
		}
  		#endif
	}

	int StandardDriverUtilities::__posixDeleteFunction(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
		int e = remove(fpath);
		if (e){
			perror(fpath);
		} 
		return e;

	}

	bool StandardDriverUtilities::deleteDir(const std::string& dir){
		#ifdef WIN32
	    HANDLE          hFile;                       // Handle to directory
	    std::string     strFilePath;                 // Filepath
	    std::string     strPattern;                  // Pattern
	    WIN32_FIND_DATA FileInformation;             // File information


	    strPattern = dir + "\\*.*";
	    hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	    if(hFile != INVALID_HANDLE_VALUE) {
	        do {
	            if(FileInformation.cFileName[0] != '.') {
	                strFilePath.erase();
	                strFilePath = dir + "\\" + FileInformation.cFileName;
	                if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
	                    // Delete subdirectory
	                    bool iRC = deleteDir(strFilePath);
	                    if(iRC) {
	                        return iRC;
	                    }
	                } else {
	                // Set file attributes
	                    if(::SetFileAttributes(strFilePath.c_str(),FILE_ATTRIBUTE_NORMAL) == FALSE) {
	                    return ::GetLastError();
	                }
	                // Delete file
	                if(::DeleteFile(strFilePath.c_str()) == FALSE) {
	                    return ::GetLastError();
	                }
	            }
	        }
	        } while(::FindNextFile(hFile, &FileInformation) == TRUE);
	        // Close file handle
	        ::FindClose(hFile);
	        DWORD dwError = ::GetLastError();
	        if(dwError != ERROR_NO_MORE_FILES) {
	            return dwError;
	        } else {
	            if(::SetFileAttributes(dir.c_str(),FILE_ATTRIBUTE_NORMAL) == FALSE) {
	            return false;
	        }
	            if(::RemoveDirectory(dir.c_str()) == FALSE) {
	                return false;
	            }
	        }
	    }
		return true;
		#else
		int success=nftw(dir.c_str(), __posixDeleteFunction, 64, FTW_DEPTH | FTW_PHYS);
		if (success==0){
			return true;
		} else {
			return false;
		}
		#endif
	}

	bool StandardDriverUtilities::createDir(const std::string& dir) {
		//Rcpp::Rcout << "Creating: "<<dir<<std::endl;
		#ifdef WIN32
		CreateDirectory(dir,NULL);
  		#else
		mkdir(dir.c_str(),0755);
  		#endif
  		return true;
	}

	std::size_t StandardDriverUtilities::assignment(std::size_t totalRealizations, std::size_t threadct) {
		return totalRealizations/(threadct);
	}

	void StandardDriverUtilities::createOutputDirs(CommandLineInterface& commandLine, bool parallel, std::size_t threads) {  

		std::string outputDir=commandLine.getOutputDir();
		try {
			if (dirExists(outputDir)) {
				if (!commandLine.getForce()) {
					COUT << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): output directory \""<<outputDir<<"\" already exists.\n";
					COUT << "Delete existing directory, use --out-dir to specify a unique directory name, or run with --force to overwrite.\n";
					COUT << "Simulation terminated.\n";
					exit(1);
				} else {
					//delete existing directory
					if (dirIsDir(outputDir)) {
						//could do some checks here to ensure they're not deleting a StochKit directory such as "src", "libs", "models", etc.
						//currently, that is the risk one takes in using --force
						deleteDir(outputDir);
					} else {
						CERR << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): output directory \""<<outputDir<<"\" exists but is not a directory.\n";
						CERR << "Delete existing file or use --out-dir to specify a unique directory name.\n";
						CERR << "Simulation terminated.\n";
						exit(1);
					}
				}
			}
			createDir(outputDir);
#ifdef WIN32
			if (commandLine.getKeepStats()) {
				createDir(outputDir+"\\"+commandLine.getStatsDir());
				if (parallel) {
					createDir(outputDir+"\\"+commandLine.getStatsDir()+"\\.parallel");
				}
			}
			if (commandLine.getKeepTrajectories()) {
				createDir(outputDir+"\\"+commandLine.getTrajectoriesDir());
			}
			if (commandLine.getKeepHistograms()) {
				createDir(outputDir+"\\"+commandLine.getHistogramsDir());
				if (parallel) {
					createDir(outputDir+"\\"+commandLine.getHistogramsDir()+"\\.parallel");	
					for (std::size_t i=0; i!=threads; ++i) {
						std::string threadNumStr=StandardDriverUtilities::size_t2string(i);
						createDir(outputDir+"\\"+commandLine.getHistogramsDir()+"\\.parallel\\thread"+threadNumStr);	
					}
				}

			}
			//create a hidden directory for StochKit data (e.g. a file that lists the solver used, the parameters, maybe even a copy of the model file
			createDir(outputDir+"\\.StochKit");      
#else
			if (commandLine.getKeepStats()) {
				createDir(outputDir+"/"+commandLine.getStatsDir());
				if (parallel) {
					createDir(outputDir+"/"+commandLine.getStatsDir()+"/.parallel");
				}
			}
			if (commandLine.getKeepTrajectories()) {
				createDir(outputDir+"/"+commandLine.getTrajectoriesDir());
			}
			if (commandLine.getKeepHistograms()) {
				createDir(outputDir+"/"+commandLine.getHistogramsDir());
				if (parallel) {
					createDir(outputDir+"/"+commandLine.getHistogramsDir()+"/.parallel");	
					for (std::size_t i=0; i!=threads; ++i) {
						std::string threadNumStr=StandardDriverUtilities::size_t2string(i);
						createDir(outputDir+"/"+commandLine.getHistogramsDir()+"/.parallel/thread"+threadNumStr);	
					}
				}

			}
			//create a hidden directory for StochKit data (e.g. a file that lists the solver used, the parameters, maybe even a copy of the model file
			createDir(outputDir+"/.StochKit");
#endif
		}
		catch (...) {
			CERR << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): error creating output directory.\n";
			exit(1);
		}
	}

#ifdef WIN32
	void StandardDriverUtilities::compileMixed(std::string executableName, const CommandLineInterface& commandLine, bool events) {
		std::string generatedCodeDir=current_path.parent_path().string()+"\\generatedCode";
		if (commandLine.getRecompile()) {
			try {
				if (dirExists(generatedCodeDir) {
					//delete existing directory
					if (dirIsDir(generatedCodeDir {
						deleteDir(generatedCodeDir);
					}
					//abort if it exists but is not a directory
					else {
						CERR << "StochKit ERROR (StandardDriverUtilities::compileMixed): generated code directory \""<<generatedCodeDir<<"\" already exists and is not a directory.\n";
						CERR << "Simulation terminated.\n";
						exit(1);
					}
				}
				createDir(generatedCodeDir);
			}
			catch (...) {
				CERR << "StochKit ERROR (StandardDriverUtilities::compileMixed): error creating output directory.\n";
				exit(1);
			}

			char* modelFileName;

			std::string tempname;
			tempname=commandLine.getModelFileName();
			modelFileName=const_cast<char*>(tempname.c_str());

#ifdef EVENTS
			Input_events_before_compile<StandardDriverTypes::populationType, 
				StandardDriverTypes::stoichiometryType,
				//StandardDriverTypes::propensitiesType,
				StandardDriverTypes::graphType> model(modelFileName);
			model.writeCustomPropensityFunctionsFile(const_cast<char*>((generatedCodeDir+"\\CustomPropensityFunctions.h").c_str()));
			model.writeCustomStateBasedTriggerFunctionsFile(const_cast<char*>((generatedCodeDir+"\\CustomStateBasedTriggerFunctions.h").c_str()));
			model.writeCustomChangeSingleSpeciesFunctionsFile(const_cast<char*>((generatedCodeDir+"\\CustomChangeSingleSpeciesFunctions.h").c_str()));
#else
			Input_mixed_before_compile<StandardDriverTypes::populationType, 
				StandardDriverTypes::stoichiometryType,
				StandardDriverTypes::propensitiesType,
				StandardDriverTypes::graphType> model(modelFileName);
			model.writeCustomPropensityFunctionsFile(const_cast<char*>((generatedCodeDir+"\\CustomPropensityFunctions.h").c_str()));
#endif

			//record current path so we can cd back to it after compiling
			char cCurrentPath[FILENAME_MAX];
			if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
     			throw;
     		}

			std::string currentPath= cCurrentPath;
			//TODO find a way to get parent path of cCurrentPath.
			std::string pathName=cCurrentPath.string()+"\\Mixed_Compiled_Solution\\Mixed_Compiled_Solution.sln";
			//redirect any errors from make to a log file
#ifdef NDEBUG
			std::string makeCommand=(std::string)"msbuild \""+pathName+"\" /t:"+executableName+":rebuild /clp:NoSummary /p:configuration=release;DebugType=none /v:q /nologo /flp:LogFile=\""+generatedCodeDir+"\\compile-log.txt\";Verbosity=diagnostic";
#else
			std::string makeCommand=(std::string)"msbuild \""+pathName+"\" /t:"+executableName+":rebuild /clp:NoSummary /p:configuration=debug /v:q /nologo /flp:LogFile=\""+generatedCodeDir+"\\compile-log.txt\";Verbosity=diagnostic";
#endif

			COUT << "StochKit MESSAGE: compiling generated code...this will take a few moments...\n";
			int returnValue=system(makeCommand.c_str());

			if (returnValue!=0) {
				COUT << "StochKit ERROR: compile of generated code failed.  Simulation terminated.\n";
				//copy hidden compile-log to visible log (this seens useless for windows)
			//std::string command="copy /B "+commandLine.getGeneratedCodeDir()+"\\.compile-log.txt "+commandLine.getGeneratedCodeDir()+"\\compile-log.txt";

			//	system(command.c_str());

				COUT << "Check log file \"" << generatedCodeDir<<"\\compile-log.txt\" for error messages.\n";
				exit(1);
			}

			//go back to original path
			std::string cd="cd "+currentPath;
			system(cd.c_str());
		}
	}
#else
	void StandardDriverUtilities::compileMixed(std::string executableName, const CommandLineInterface& commandLine, bool events) {
		if (commandLine.getRecompile()) {
			try {
				if (dirExists(commandLine.getGeneratedCodeDir())) {
					//delete existing directory
					if (dirIsDir(commandLine.getGeneratedCodeDir())) {
						deleteDir(commandLine.getGeneratedCodeDir());
					}
					//abort if it exists but is not a directory
					else {
						CERR << "StochKit ERROR (StandardDriverUtilities::compileMixed): generated code directory \""<<commandLine.getGeneratedCodeDir()<<"\" already exists and is not a directory.\n";
						CERR << "Simulation terminated.\n";
						exit(1);
					}
				}
				createDir(commandLine.getGeneratedCodeDir());
				createDir(commandLine.getGeneratedCodeDir()+"/bin");
			}
			catch (...) {
				CERR << "StochKit ERROR (StandardDriverUtilities::compileMixed): error creating output directory.\n";
				exit(1);
			}

			char* modelFileName;
			modelFileName=const_cast<char*>(commandLine.getModelFileName().c_str());

#ifdef EVENTS
			Input_events_before_compile<StandardDriverTypes::populationType, 
				StandardDriverTypes::stoichiometryType,
				/*StandardDriverTypes::propensitiesType,*/
				StandardDriverTypes::graphType> model(modelFileName);
			model.writeCustomPropensityFunctionsFile(const_cast<char*>((commandLine.getGeneratedCodeDir()+"/CustomPropensityFunctions.h").c_str()));
			model.writeCustomStateBasedTriggerFunctionsFile(const_cast<char*>((commandLine.getGeneratedCodeDir()+"/CustomStateBasedTriggerFunctions.h").c_str()));
			model.writeCustomChangeSingleSpeciesFunctionsFile(const_cast<char*>((commandLine.getGeneratedCodeDir()+"/CustomChangeSingleSpeciesFunctions.h").c_str()));
#else
			Input_mixed_before_compile<StandardDriverTypes::populationType, 
				StandardDriverTypes::stoichiometryType,
				StandardDriverTypes::propensitiesType,
				StandardDriverTypes::graphType> model(modelFileName);
			model.writeCustomPropensityFunctionsFile(const_cast<char*>((commandLine.getGeneratedCodeDir()+"/CustomPropensityFunctions.h").c_str()));
#endif

			//record current path so we can cd back to it after compiling
			char cCurrentPath[FILENAME_MAX];
			if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
     			throw;
     		}

			std::string currentPath= cCurrentPath;

			//updated so generated code path is a full path sanft 2011/03/21
			std::string makeCommand=(std::string)"cd $StochLib_HOME/src; make "+executableName+" GENERATED_CODE_PATH="+commandLine.getGeneratedCodeDir()+" --silent";

			//redirect any errors from make to a log file
			//updated so generated code path is a full path sanft 2011/03/21
			makeCommand+=" > "+commandLine.getGeneratedCodeDir()+"/.compile-log.txt 2>&1";

			COUT << "StochKit MESSAGE: compiling generated code...this will take a few moments...\n";
			int returnValue=system(makeCommand.c_str());

			if (returnValue!=0) {
				COUT << "StochKit ERROR: compile of generated code failed.  Simulation terminated.\n";
				//copy hidden compile-log to visible log
				//updated so generated code path is a full path sanft 2011/03/21
				std::string command="cp "+commandLine.getGeneratedCodeDir()+"/.compile-log.txt "+commandLine.getGeneratedCodeDir()+"/compile-log.txt";

				system(command.c_str());

				COUT << "Check log file \"" << commandLine.getGeneratedCodeDir()<<"/compile-log.txt\" for error messages.\n";
				exit(1);
			}

			//go back to original path
			std::string cd="cd "+currentPath;
			system(cd.c_str());
		}
	}
#endif

	std::string StandardDriverUtilities::size_t2string(std::size_t number) {
		std::string theString;
		std::stringstream ss;
		ss<<number;
		theString=ss.str();
		return theString;
	}

}
