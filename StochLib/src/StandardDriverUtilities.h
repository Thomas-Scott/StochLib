/*!

*/

#ifndef _STANDARD_DRIVER_UTILITIES_H_
#define _STANDARD_DRIVER_UTILITIES_H_

#include <StdOutputHandler.h>

#include <stdio.h>
#include <vector>
#include <string.h>
#include <sstream>
#include "CommandLineInterface.h"
#ifdef EVENTS
#include "Input_events_before_compile.h"
#else
#include "Input_mixed_before_compile.h"
#endif
#include "StandardDriverTypes.h"


#ifdef WIN32
#include <windows.h>
#include <direct.h>
#include <conio.h>
#define GetCurrentDir _getcwd
#else 

#define GetCurrentDir getcwd
#include <cstdio>
#include <ftw.h>
#include <unistd.h>
#include <sys/stat.h>
#endif


namespace StochLib
{
	class StandardDriverUtilities
	{

	public:
		static void createOutputDirs(CommandLineInterface& commandLine, bool parallel, std::size_t threads=1);//if parallel=true, threads is number of processes

#ifdef WIN32
		static void compileMixed(std::string executableName, const CommandLineInterface& commandLine, bool events=false);
#else
		static void compileMixed(std::string executableName, const CommandLineInterface& commandLine, bool events=false);
#endif

		static std::string size_t2string(std::size_t number);

		static bool dirExists(const std::string& dir);

		static bool createDir(const std::string& dir);
		
		static bool dirIsDir(const std::string& dir);
		
		static bool deleteDir(const std::string& dir);

	private:
		static int __posixDeleteFunction(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
		

	};
}

#endif
