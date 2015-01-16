#include "pythonwrapper.h"

#include <pyblockzor.h>

#include <boost/python.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;

using namespace arma;
using namespace std;

bn::ndarray pyblockzor::block(const bn::ndarray &input, const int min, const int max)
{
    vec data(reinterpret_cast<double*>(input.get_data()), input.shape(0), false);

    pyblockzor::Dataset set(data, min, max, 10);

    mat result = set.block();

    cout << result << endl;

    Py_intptr_t shape[2] = {result.n_cols, result.n_rows};
    bn::ndarray numpyResult = bn::zeros(2, shape, bn::dtype::get_builtin<double>());
    std::copy(result.begin(), result.end(), reinterpret_cast<double*>(numpyResult.get_data()));
    return numpyResult;
}

BOOST_PYTHON_MODULE(pyblockzor)
{
    bn::initialize();
    bp::def("block", pyblockzor::block);
}


