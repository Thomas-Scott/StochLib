#include "DriverDecs.h"
#include <boost/python.hpp>
#include "boost/python/def.hpp"
#include "boost/python/module.hpp"


BOOST_PYTHON_MODULE(StochLib) {
    using namespace boost::python;
    def("ssaDirectSerial", _ssaDirectSerial);
    def("parallelSSADirectSerial", _parallel_ssaDirectSerial);
    def("count", _count);
} 
