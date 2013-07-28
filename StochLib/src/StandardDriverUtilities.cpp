/*!

*/
#include "StandardDriverUtilities.h"
#ifdef WIN32
#include <windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#define unlink _unlink
#else 
#include <unistd.h>
#define GetCurrentDir getcwd
#include <sys/stat.h>
#include <cstdio>
#endif

namespace StochLib
{
	void StandardDriverUtilities::createOutputDirs(CommandLineInterface& commandLine, bool parallel, std::size_t threads)
	{  

		std::string outputDir=commandLine.getOutputDir();

		try {
			bool e;
			#ifdef WIN32
			e = CreateDirectory(outputDir.c_str(), NULL);
			#else
			struct stat sb;
			if (stat(outputDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
				e = true;
			}
			#endif 
			if (e) {
				if (!commandLine.getForce()) {
					std::cout << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): output directory \""<<outputDir<<"\" already exists.\n";
					std::cout << "Delete existing directory, use --out-dir to specify a unique directory name, or run with --force to overwrite.\n";
					std::cout << "Simulation terminated.\n";
					exit(1);
				}
				else {
					//delete existing directory
					if (e) {
						//could do some checks here to ensure they're not deleting a StochKit directory such as "src", "libs", "models", etc.
						//currently, that is the risk one takes in using --force

						#ifdef WIN32
							WCHAR szDir[MAX_PATH+1];  // +1 for the double null terminate
						    SHFILEOPSTRUCTW fos = {0};

						    StringCchCopy(szDir, MAX_PATH, outputDir.c_str());
						    int len = lstrlenW(szDir);
						    szDir[len+1] = 0; // double null terminate for SHFileOperation

						    // delete the folder and everything inside
						    fos.wFunc = FO_DELETE;
						    fos.pFrom = szDir;
						    fos.fFlags = FOF_NO_UI;
						    SHFileOperation( &fos );
						#else 
						    unlink(outputDir.c_str());
						#endif
					}
					//abort if it exists but is not a directory
					else {
						std::cerr << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): output directory \""<<outputDir<<"\" exists but is not a directory.\n";
						std::cerr << "Delete existing file or use --out-dir to specify a unique directory name.\n";
						std::cerr << "Simulation terminated.\n";
						exit(1);
					}
				}
			}
			
#ifdef WIN32
			CreateDirectory(outputDir,NULL);
			if (commandLine.getKeepStats()) {
				CreateDirectory(outputDir+"\\"+commandLine.getStatsDir(), NULL);
				//boost::filesystem::create_directory(outputDir+"\\"+commandLine.getStatsDir());
				if (parallel) {
					CreateDirectory(outputDir+"\\"+commandLine.getStatsDir()+"\\.parallel", NULL);
					//boost::filesystem::create_directory(outputDir+"\\"+commandLine.getStatsDir()+"\\.parallel");
				}
			}
			if (commandLine.getKeepTrajectories()) {
				CreateDirectory(outputDir+"\\"+commandLine.getTrajectoriesDir(),NULL);
			}
			if (commandLine.getKeepHistograms()) {
				CreateDirectory(outputDir+"\\"+commandLine.getHistogramsDir(),NULL);
				if (parallel) {
					CreateDirectory(outputDir+"\\"+commandLine.getHistogramsDir()+"\\.parallel",NULL);	
					for (std::size_t i=0; i!=threads; ++i) {
						std::string threadNumStr=StandardDriverUtilities::size_t2string(i);
						CreateDirectory(outputDir+"\\"+commandLine.getHistogramsDir()+"\\.parallel\\thread"+threadNumStr,NULL);	
					}
				}

			}
			//create a hidden directory for StochKit data (e.g. a file that lists the solver used, the parameters, maybe even a copy of the model file
			CreateDirectory(outputDir+"\\.StochKit",NULL);      
#else
			mkdir(outputDir.c_str(), 0777);
			if (commandLine.getKeepStats()) {
				mkdir((outputDir+"/"+commandLine.getStatsDir()).c_str(),0777);
				if (parallel) {
					mkdir((outputDir+"/"+commandLine.getStatsDir()+"/.parallel").c_str(),0777);
				}
			}
			if (commandLine.getKeepTrajectories()) {
				mkdir((outputDir+"/"+commandLine.getTrajectoriesDir()).c_str(),0777);
			}
			if (commandLine.getKeepHistograms()) {
				mkdir((outputDir+"/"+commandLine.getHistogramsDir()).c_str(),0777);
				if (parallel) {
					mkdir((outputDir+"/"+commandLine.getHistogramsDir()+"/.parallel").c_str(),0777);	
					for (std::size_t i=0; i!=threads; ++i) {
						std::string threadNumStr=StandardDriverUtilities::size_t2string(i);
						mkdir((outputDir+"/"+commandLine.getHistogramsDir()+"/.parallel/thread"+threadNumStr).c_str(),0777);	
					}
				}

			}
			//create a hidden directory for StochKit data (e.g. a file that lists the solver used, the parameters, maybe even a copy of the model file
			mkdir((outputDir+"/.StochKit").c_str(),0777);
#endif
		}
		catch (...) {
			std::cerr << "StochKit ERROR (StandardDriverUtilities::createOutputDirs): error creating output directory.\n";
			exit(1);
		}
	}

#ifdef WIN32
	void StandardDriverUtilities::compileMixed(std::string executableName, const CommandLineInterface& commandLine, bool events) {
		std::string generatedCodeDir=current_path.parent_path().string()+"\\generatedCode";
		if (commandLine.getRecompile()) {
			try {
				if (CreateDirectory(generatedCodeDir.c_str(), NULL)) {
					//delete existing directory
					if (CreateDirectory(generatedCodeDir.c_str(), NULL)) {
						unlink(generatedCodeDir);
					}
					//abort if it exists but is not a directory
					else {
						std::cerr << "StochKit ERROR (StandardDriverUtilities::compileMixed): generated code directory \""<<generatedCodeDir<<"\" already exists and is not a directory.\n";
						std::cerr << "Simulation terminated.\n";
						exit(1);
					}
				}
				CreateDirectory(generatedCodeDir,NULL);
			}
			catch (...) {
				std::cerr << "StochKit ERROR (StandardDriverUtilities::compileMixed): error creating output directory.\n";
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

			std::cout << "StochKit MESSAGE: compiling generated code...this will take a few moments...\n";
			int returnValue=system(makeCommand.c_str());

			if (returnValue!=0) {
				std::cout << "StochKit ERROR: compile of generated code failed.  Simulation terminated.\n";
				//copy hidden compile-log to visible log (this seens useless for windows)
			//std::string command="copy /B "+commandLine.getGeneratedCodeDir()+"\\.compile-log.txt "+commandLine.getGeneratedCodeDir()+"\\compile-log.txt";

			//	system(command.c_str());

				std::cout << "Check log file \"" << generatedCodeDir<<"\\compile-log.txt\" for error messages.\n";
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
				struct stat sb;
				if (stat(commandLine.getGeneratedCodeDir().c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
					//delete existing directory
					if (stat(commandLine.getGeneratedCodeDir().c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
						unlink(commandLine.getGeneratedCodeDir().c_str());
					}
					//abort if it exists but is not a directory
					else {
						std::cerr << "StochKit ERROR (StandardDriverUtilities::compileMixed): generated code directory \""<<commandLine.getGeneratedCodeDir()<<"\" already exists and is not a directory.\n";
						std::cerr << "Simulation terminated.\n";
						exit(1);
					}
				}
				mkdir(commandLine.getGeneratedCodeDir().c_str(),0777);
				mkdir((commandLine.getGeneratedCodeDir()+"/bin").c_str(),0777);
			}
			catch (...) {
				std::cerr << "StochKit ERROR (StandardDriverUtilities::compileMixed): error creating output directory.\n";
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
			std::string makeCommand=(std::string)"cd $STOCHKIT_HOME/src; make "+executableName+" GENERATED_CODE_PATH="+commandLine.getGeneratedCodeDir()+" --silent";

			//redirect any errors from make to a log file
			//updated so generated code path is a full path sanft 2011/03/21
			makeCommand+=" > "+commandLine.getGeneratedCodeDir()+"/.compile-log.txt 2>&1";

			std::cout << "StochKit MESSAGE: compiling generated code...this will take a few moments...\n";
			int returnValue=system(makeCommand.c_str());

			if (returnValue!=0) {
				std::cout << "StochKit ERROR: compile of generated code failed.  Simulation terminated.\n";
				//copy hidden compile-log to visible log
				//updated so generated code path is a full path sanft 2011/03/21
				std::string command="cp "+commandLine.getGeneratedCodeDir()+"/.compile-log.txt "+commandLine.getGeneratedCodeDir()+"/compile-log.txt";

				system(command.c_str());

				std::cout << "Check log file \"" << commandLine.getGeneratedCodeDir()<<"/compile-log.txt\" for error messages.\n";
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
