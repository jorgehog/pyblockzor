#pragma once

#include <boost/numpy.hpp>

namespace pyblockzor
{

    boost::numpy::ndarray block(const boost::numpy::ndarray &input, const int min, const int max);

}
