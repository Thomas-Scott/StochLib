include_directories(../src)
file(	COPY PyStochLib
		DESTINATION ../build/)
add_library(PyStochLib PyStochLib.cpp ${STOCH_SRC} ${LIBXML2_HEADERS})
target_link_libraries(PyStochLib ${LIBS})