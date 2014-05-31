cmake_minimum_required(VERSION 2.8)
project(StochLib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS program_options thread filesystem system python)
find_package(PythonLibs)
find_package(OpenMP)
find_package(XML2 REQUIRED)

## BOOST

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})                                   
endif()

if(Boost_FOUND AND PythonLibs_FOUND)
	add_subdirectory(PyStochLib)
endif()

## CXX FLAGS

set(CMAKE_CXX_FLAGS "-O3 -Wall")

if (CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

## LIBRARIES

set(LIBS ${LIBS} ${XML2_LIBRARIES} ${Boost_LIBRARIES})

## BUILD DIR

file(MAKE_DIRECTORY build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

## INCLUDE

include_directories(${XML2_INCLUDE_DIR})
set(LIBXML2_HEADERS ${XML2_INCLUDE_DIR}/)

## StochLib SRC

file(GLOB_RECURSE STOCH_SRC CommandLineInterface.cpp Parameter.cpp Random.cpp StandardDriverUtilities.cpp TimeBasedTrigger.cpp ParallelIntervalSimulation.cpp SSADirectSerial.cpp StringCalculator.cpp ssa_direct_serial.cpp Input.ipp Input_tag.ipp SSA_Direct.ipp ssa_constant_serial.cpp ssa_lda_serial.cpp ssa_nrm_serial.cpp tau_leaping_exp_adapt.cpp tau_leaping_exp_adapt_serial.cpp ssa_odm_small.cpp ssa_odm.cpp)

add_subdirectory(PyStochLib)
add_subdirectory(StochLib)