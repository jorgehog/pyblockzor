#include "pythonwrapper.h"

#include <pyblockzor.h>

#include <boost/python.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;

using namespace arma;
using namespace std;

bn::ndarray pyblockzor::block(const int N, const int min, const int max)
{
    vec data = linspace<vec>(1, 100, N);

    pyblockzor::Dataset set(data, min, max, 10);

    mat result = set.block();

    Py_intptr_t shape[2] = {result.n_rows, result.n_cols};
    bn::ndarray numpyResult = bn::zeros(2, shape, bn::dtype::get_builtin<double>());
    std::copy(result.begin(), result.end(), reinterpret_cast<double*>(numpyResult.get_data()));
    return numpyResult;
}

BOOST_PYTHON_MODULE(pyblockzor)
{
    bn::initialize();
    bp::def("block", pyblockzor::block);
}


