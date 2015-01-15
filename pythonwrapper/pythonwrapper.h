#pragma once

#include <boost/numpy.hpp>

namespace pyblockzor
{

    boost::numpy::ndarray block(const int N, const int min, const int max);

}
