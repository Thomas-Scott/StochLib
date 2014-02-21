#include "DriverDecs.h"
#include <boost/python.hpp>
#include "boost/python/def.hpp"
#include "boost/python/module.hpp"


BOOST_PYTHON_MODULE(PyStochLib) {
    using namespace boost::python;
    def("ssaDirectSerial", _ssaDirectSerial);
    def("parallelSSADirectSerial", parallelSSADirectSerial);
} 
