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
    if (!consistencyCheck(m_minBlockSize,
                          m_maxBlockSize,
                          m_nBlocks_raw,
                          m_data.size()))
    {
        cerr << "Inconsistent parameters, aborting" << endl;
        exit(1);
    }
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

bool Dataset::consistencyCheck(uint minbs, uint maxbs, uint nbs, uint nDataPoints, bool silent)
{

    if (!consistencyCheckMaxBlockSize(maxbs, nDataPoints))
    {
        if (!silent)
        {
            cerr << _consistencyCheckMaxBlockSizeMessage(maxbs, nDataPoints) << endl;
        }

        return false;
    }

    if (!consistencyCheckMinBlockSize(minbs))
    {
        if (!silent)
        {
            cerr << _consistencyCheckMinBlockSizeMessage(minbs) << endl;
        }

        return false;
    }

    if (!consistencyCheckNBlocks(maxbs, minbs, nbs))
    {
        if (!silent)
        {
            cerr << _consistencyCheckNBlocksMessage(maxbs, minbs, nbs) << endl;
        }

        return false;
    }

    return true;
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

#pragma omp parallel for private(blockMean) reduction(+:mean, squareMean)
    for (uint i = 0; i < nBlocks; i++)
    {

        //mean inside block number i which goes from i*blocksize to (i+1)*blocksize - 1
        blockMean = arma::mean(m_data(span(i*blockSize, (i + 1) * blockSize - 1)));

        mean += blockMean;
        squareMean += blockMean*blockMean;
    }

    mean /= nBlocks;

    //Use sample variance here since we use potentially few samples
    return squareMean/(nBlocks-1) - nBlocks*mean*mean/(nBlocks-1);
}

bool Dataset::consistencyCheckMinBlockSize(uint minbs)
{
    return minbs >= 1;
}

bool Dataset::consistencyCheckMaxBlockSize(uint maxbs, uint N)
{
    return maxbs <= N/2;
}

bool Dataset::consistencyCheckNBlocks(uint maxbs, uint minbs, uint nbs)
{
    return nbs <= maxbs - minbs;
}

string Dataset::_consistencyCheckMinBlockSizeMessage(uint minbs)
{
    stringstream s;
    s << "Invalid local min block size " << minbs
      << ": Min block size must not be lower than 1";

    return s.str();
}

string Dataset::_consistencyCheckMaxBlockSizeMessage(uint maxbs, uint N)
{
    stringstream s;
    s << "Invalid max block size " << maxbs
      << ": Max block size must not be greater than " <<  N/2;

    return s.str();
}

string Dataset::_consistencyCheckNBlocksMessage(uint maxbs, uint minbs, uint nbs)
{
    stringstream s;
    s << "Invalid amount of block samples " << nbs
      << ": Block samples must be lower or equal " << maxbs - minbs;

    return s.str();
}


