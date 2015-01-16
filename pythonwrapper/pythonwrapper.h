#pragma once

#include <boost/numpy.hpp>

namespace pyblockzor
{

boost::numpy::ndarray block(const boost::numpy::ndarray &inputData,
                            const uint minBlockSize,
                            const uint maxBlockSize,
                            const uint nBlocks);

}
