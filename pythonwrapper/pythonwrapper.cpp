#include "pythonwrapper.h"

#include <pyblockzor.h>

#include <boost/python.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;

using namespace arma;
using namespace std;

boost::numpy::ndarray pyblockzor::block(const boost::numpy::ndarray &inputData,
                                        const uint minBlockSize,
                                        const uint maxBlockSize,
                                        const uint nBlocks)
{
    //convert numpy data to armadillo
    vec data(reinterpret_cast<double*>(inputData.get_data()), inputData.shape(0), false);

    pyblockzor::Dataset set(data, minBlockSize, maxBlockSize, nBlocks);

    mat result = set.block();

    //Convert result to numpy array
    Py_intptr_t shape[2] = {result.n_cols, result.n_rows};
    bn::ndarray numpyResult = bn::zeros(2, shape, bn::dtype::get_builtin<double>());
    std::copy(result.begin(), result.end(), reinterpret_cast<double*>(numpyResult.get_data()));

    return numpyResult;
}


BOOST_PYTHON_MODULE(pyblockzor)
{
    bn::initialize();
    bp::def("block", pyblockzor::block);
    bp::def("consistencyCheck", pyblockzor::Dataset::consistencyCheck);

    bp::def("consistencyCheckMinBlockSize", pyblockzor::Dataset::consistencyCheckMinBlockSize);
    bp::def("consistencyCheckMaxBlockSize", pyblockzor::Dataset::consistencyCheckMaxBlockSize);
    bp::def("consistencyCheckNBlocks", pyblockzor::Dataset::consistencyCheckNBlocks);

    bp::def("_consistencyCheckMinBlockSizeMessage", pyblockzor::Dataset::_consistencyCheckMinBlockSizeMessage);
    bp::def("_consistencyCheckMaxBlockSizeMessage", pyblockzor::Dataset::_consistencyCheckMaxBlockSizeMessage);
    bp::def("_consistencyCheckNBlocksMessage", pyblockzor::Dataset::_consistencyCheckNBlocksMessage);
}

