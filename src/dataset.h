#pragma once

#include <armadillo>

namespace pyblockzor
{

class Dataset
{
public:

    Dataset(const arma::vec data,
            uint minBlockSize,
            uint maxBlockSize,
            uint nBlocks);

    ~Dataset();

    arma::mat block();

private:

    const uint m_minBlockSize;
    const uint m_maxBlockSize;
    const uint m_nBlocks_raw; //This is not necessariliy equal to the real number of blocks.

    const arma::vec m_data; //!armadillo vector initialized from constructor data

    arma::uvec getUniqueBlocks() const;

    double getBlockVariance(const uint blockSize) const;

};

}

