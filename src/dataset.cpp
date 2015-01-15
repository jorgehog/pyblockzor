#include "dataset.h"

#include <iostream>

using namespace pyblockzor;
using namespace arma;
using namespace std;

Dataset::Dataset(const vec data,
                 uint minBlockSize,
                 uint maxBlockSize,
                 uint nBlocks) :
    m_minBlockSize(minBlockSize),
    m_maxBlockSize(maxBlockSize),
    m_nBlocks_raw(nBlocks),
    m_data(data)
{

}

Dataset::~Dataset()
{

}

mat Dataset::block()
{
    uvec blockSizes = getUniqueBlocks();

    uint nBlocks = blockSizes.size();

    vec result(nBlocks);

    for (uint i = 0; i < nBlocks; ++i)
    {
        uint blockSize = blockSizes(i);

        double blockVariance = getBlockVariance(blockSize);

        result[i] = sqrt(blockVariance / ((m_data.size()/blockSize) - 1.0));
    }

    return join_rows(conv_to<vec>::from(blockSizes), result);
}

uvec Dataset::getUniqueBlocks() const
{
    int blockStepLength = (m_maxBlockSize - m_minBlockSize) / (m_nBlocks_raw - 1);

    uvec blockSizes(m_nBlocks_raw);

    for (uint j = 0; j < m_nBlocks_raw; j++)
    {
        blockSizes(j) = m_minBlockSize + j * blockStepLength;
    }

    return arma::unique(blockSizes);
}

double Dataset::getBlockVariance(const uint blockSize) const
{
    double blockMean;


    double mean = 0;
    double squareMean = 0;

    uint nBlocks = m_data.size() / blockSize;
    for (uint i = 0; i < nBlocks; i++) {

        //mean inside block number i which goes from i*blocksize to (i+1)*blocksize - 1
        blockMean = arma::mean(m_data(span(i*blockSize, (i + 1) * blockSize - 1)));

        mean += blockMean;
        squareMean += blockMean*blockMean;
    }

    mean /= nBlocks;

    //Use sample variance here since we use potentially few samples
    return squareMean/(nBlocks-1) - nBlocks*mean*mean/(nBlocks-1);
}


