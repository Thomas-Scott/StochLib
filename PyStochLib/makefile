.PHONY: PyLibrary clean

CXX = g++
CXXFLAGS = -O3 -Wall -fopenmp

INCLUDE_PATH = -I/usr/lib/boost_1_53_0 -I$(PYTHON_HOME)/include/python2.7 -I/usr/lib/boost_1_53_0/stage/lib 
LINK_PATH =  -L/usr/lib/boost_1_53_0 -L$(PYTHON_HOME)/lib -L/usr/lib/boost_1_53_0/stage/lib
LINK_LIBS = -lboost_python -lpython2.7

STOCHLIB_OBJS = Output.o Model.o SSADirectSerial.o

COMPILEOPTIONS = -c $(CXXFLAGS) $(INCLUDE_PATH) 
ALLOPTIONS = $(CXXFLAGS) $(INCLUDE_PATH) $(LINK_PATH) $(LINK_LIBS)

all: PyLibrary

PyLibrary: DriverDecs.h PyStochLib.cpp $(STOCHLIB_OBJS)
	$(CXX) PyStochLib.cpp -o PyStochLib.os -fPIC $(COMPILEOPTIONS)
	$(CXX) -o PyStochLib.so -shared PyStochLib.os $(STOCHLIB_OBJS) $(ALLOPTIONS)

SSADirectSerial.o: SSADirectSerial.cpp 
	$(CXX) SSADirectSerial.cpp -o SSADirectSerial.o $(COMPILEOPTIONS)


Model.o: Model.h Model.cpp Reaction.h
	$(CXX) Model.cpp -o Model.o $(COMPILEOPTIONS)


Output.o:	Output.h Output.cpp
	$(CXX) Output.cpp -o Output.o $(COMPILEOPTIONS)

clean:
	rm -f *.o *.so *.os 