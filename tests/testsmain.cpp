#include <pyblockzor.h>

#include <sys/time.h>
#include <iostream>

#include <armadillo>

using namespace arma;

int main()
{
    vec data = linspace(1, 100, 10000);
    pyblockzor::Dataset dataset(data, 100, 1000, 10);

    mat result = dataset.block();

    cout << result << endl;

    return 0;
}
