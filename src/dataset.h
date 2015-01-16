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

    static bool consistencyCheck(uint minbs, uint maxbs, uint nbs, uint nDataPoints, bool silent = false);

    static bool consistencyCheckMinBlockSize(uint minbs);
    static bool consistencyCheckMaxBlockSize(uint maxbs, uint N);
    static bool consistencyCheckNBlocks(uint maxbs, uint minbs, uint nbs);

    static std::string _consistencyCheckMinBlockSizeMessage(uint minbs);
    static std::string _consistencyCheckMaxBlockSizeMessage(uint maxbs, uint N);
    static std::string _consistencyCheckNBlocksMessage(uint maxbs, uint minbs, uint nbs);

private:

    const uint m_minBlockSize;
    const uint m_maxBlockSize;
    const uint m_nBlocks_raw; //This is not necessariliy equal to the real number of blocks.

    const arma::vec m_data; //!armadillo vector initialized from constructor data

    arma::uvec getUniqueBlocks() const;

    double getBlockVariance(const uint blockSize) const;



};

}

