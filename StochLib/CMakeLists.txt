include_directories(../src)
message(STATUS "Setting up R build directory.")
file(MAKE_DIRECTORY build/StochLib)
file(	COPY cleanup
		DESTINATION ../build/StochLib/)

file(	COPY configure
		DESTINATION ../build/StochLib/)

file(	COPY configure.win
		DESTINATION ../build/StochLib/)

file(	COPY R
		DESTINATION ../build/StochLib/)

file(	COPY NAMESPACE
		DESTINATION ../build/StochLib/)

file(	COPY DESCRIPTION
		DESTINATION ../build/StochLib/)

file(	COPY ../src
		DESTINATION ../build/StochLib/)

file(	COPY src
		DESTINATION ../build/StochLib/)

file(	COPY man
		DESTINATION ../build/StochLib/)

message(STATUS "R build directory completed. Run R CMD INSTALL to build.")