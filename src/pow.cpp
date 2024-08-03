// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>

namespace {
    // returns a * exp(p/q) where |p/q| is small
    arith_uint256 mul_exp(arith_uint256 a, int64_t p, int64_t q)
    {
        bool isNegative = p < 0;
        uint64_t abs_p = p >= 0 ? p : -p;
        arith_uint256 result = a;
        uint64_t n = 0;
        while (a > 0) {
            ++n;
            a = a * abs_p / q / n;
            if (isNegative && (n % 2 == 1)) {
                result -= a;
            } else {
                result += a;
            }
        }
        return result;
    }
}

// ppcoin: find last block index up to pindex
const CBlockIndex* GetLastBlockIndex(const CBlockIndex* pindex, bool fProofOfStake)
{
    //CBlockIndex will be updated with information about the proof type later
    while (pindex && pindex->pprev && (pindex->IsProofOfStake() != fProofOfStake))
        pindex = pindex->pprev;
    return pindex;
}

inline arith_uint256 GetLimit(int nHeight, const Consensus::Params& params, bool fProofOfStake)
{
    if(fProofOfStake) {
        if(nHeight < params.QIP9Height) {
            return UintToArith256(params.posLimit);
        } else if(nHeight < params.nReduceBlocktimeHeight) {
            return UintToArith256(params.QIP9PosLimit);
        } else {
            return UintToArith256(params.RBTPosLimit);
        }
    } else {
        return UintToArith256(params.powLimit);
    }
}



unsigned int static KimotoGravityWell(const CBlockIndex* pindexLast, const Consensus::Params& params) {
    const CBlockIndex *BlockLastSolved = pindexLast;
    const CBlockIndex *BlockReading = pindexLast;
    uint64_t PastBlocksMass = 0;
    int64_t PastRateActualSeconds = 0;
    int64_t PastRateTargetSeconds = 0;
    double PastRateAdjustmentRatio = double(1);
    arith_uint256 PastDifficultyAverage;
    arith_uint256 PastDifficultyAveragePrev;
    double EventHorizonDeviation;
    double EventHorizonDeviationFast;
    double EventHorizonDeviationSlow;

    uint64_t pastSecondsMin = params.nPowTargetTimespan * 0.025;
    uint64_t pastSecondsMax = params.nPowTargetTimespan * 7;
    uint64_t PastBlocksMin = pastSecondsMin / params.nPowTargetSpacing;
    uint64_t PastBlocksMax = pastSecondsMax / params.nPowTargetSpacing;

    if (BlockLastSolved == nullptr || BlockLastSolved->nHeight == 0 || (uint64_t)BlockLastSolved->nHeight < PastBlocksMin) { return UintToArith256(params.powLimit).GetCompact(); }

    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
        PastBlocksMass++;

        PastDifficultyAverage.SetCompact(BlockReading->nBits);
        if (i > 1) {
            // handle negative arith_uint256
            if(PastDifficultyAverage >= PastDifficultyAveragePrev)
                PastDifficultyAverage = ((PastDifficultyAverage - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev;
            else
                PastDifficultyAverage = PastDifficultyAveragePrev - ((PastDifficultyAveragePrev - PastDifficultyAverage) / i);
        }
        PastDifficultyAveragePrev = PastDifficultyAverage;

        PastRateActualSeconds = BlockLastSolved->GetBlockTime() - BlockReading->GetBlockTime();
        PastRateTargetSeconds = params.nPowTargetSpacing * PastBlocksMass;
        PastRateAdjustmentRatio = double(1);
        if (PastRateActualSeconds < 0) { PastRateActualSeconds = 0; }
        if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
            PastRateAdjustmentRatio = double(PastRateTargetSeconds) / double(PastRateActualSeconds);
        }
        EventHorizonDeviation = 1 + (0.7084 * pow((double(PastBlocksMass)/double(28.2)), -1.228));
        EventHorizonDeviationFast = EventHorizonDeviation;
        EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

        if (PastBlocksMass >= PastBlocksMin) {
                if ((PastRateAdjustmentRatio <= EventHorizonDeviationSlow) || (PastRateAdjustmentRatio >= EventHorizonDeviationFast))
                { assert(BlockReading); break; }
        }
        if (BlockReading->pprev == nullptr) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }

    arith_uint256 bnNew(PastDifficultyAverage);
    if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
        bnNew *= PastRateActualSeconds;
        bnNew /= PastRateTargetSeconds;
    }

    if (bnNew > UintToArith256(params.powLimit)) {
        bnNew = UintToArith256(params.powLimit);
    }

    return bnNew.GetCompact();
}

unsigned int static DarkGravityWave(const CBlockIndex* pindexLast, const Consensus::Params& params) {
    /* current difficulty formula, dash - DarkGravity v3, written by Evan Duffield - evan@dash.org */
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);

 int64_t nPastBlocks = 24; // was 24 blocks for pastblocks average here adjusted
    if (pindexLast->nHeight + 1 >= 95000)
        nPastBlocks = 60; // about 3 hours timewindow with 60x3.5min



    // make sure we have at least (nPastBlocks + 1) blocks, otherwise just return powLimit
    if (!pindexLast || pindexLast->nHeight < nPastBlocks) {
        return bnPowLimit.GetCompact();
    }

    const CBlockIndex *pindex = pindexLast;
    arith_uint256 bnPastTargetAvg;

    for (unsigned int nCountBlocks = 1; nCountBlocks <= nPastBlocks; nCountBlocks++) {
        arith_uint256 bnTarget = arith_uint256().SetCompact(pindex->nBits);
        if (nCountBlocks == 1) {
            bnPastTargetAvg = bnTarget;
        } else {
            // NOTE: that's not an average really...
            bnPastTargetAvg = (bnPastTargetAvg * nCountBlocks + bnTarget) / (nCountBlocks + 1);
        }

        if(nCountBlocks != nPastBlocks) {
            assert(pindex->pprev); // should never fail
            pindex = pindex->pprev;
        }
    }

    arith_uint256 bnNew(bnPastTargetAvg);

    int64_t nActualTimespan = pindexLast->GetBlockTime() - pindex->GetBlockTime();
    // NOTE: is this accurate? nActualTimespan counts it for (nPastBlocks - 1) blocks only...
    int64_t nTargetTimespan = nPastBlocks * params.nPowTargetSpacing;

    if (nActualTimespan < nTargetTimespan/3)
        nActualTimespan = nTargetTimespan/3;
    if (nActualTimespan > nTargetTimespan*3)
        nActualTimespan = nTargetTimespan*3;

    // Retarget
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

    if (bnNew > bnPowLimit) {
        bnNew = bnPowLimit;
    }

    return bnNew.GetCompact();
}


unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, bool fProofOfStake)
{

    unsigned int  nTargetLimit = GetLimit(pindexLast ? pindexLast->nHeight+1 : 0, params, fProofOfStake).GetCompact();

    // genesis block
    if (pindexLast == NULL)
        return nTargetLimit;

    // first block
    const CBlockIndex* pindexPrev = GetLastBlockIndex(pindexLast, fProofOfStake);
    if (pindexPrev->pprev == NULL)
        return nTargetLimit;

    // second block
    const CBlockIndex* pindexPrevPrev = GetLastBlockIndex(pindexPrev->pprev, fProofOfStake);
    if (pindexPrevPrev->pprev == NULL)
        return nTargetLimit;

    // min difficulty
    if (params.fPowAllowMinDifficultyBlocks)
    {
        // Special difficulty rule for testnet:
        // If the new block's timestamp is more than 2* 10 minutes
        // then allow mining of a min-difficulty block.
        int nHeight = pindexLast->nHeight + 1;
        if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.TargetSpacing(nHeight)*2)
            return nTargetLimit;
        else
        {
            // Return the last non-special-min-difficulty-rules-block
            const CBlockIndex* pindex = pindexLast;
            while (pindex->pprev && pindex->nHeight % params.DifficultyAdjustmentInterval(pindex->nHeight) != 0 && pindex->nBits == nTargetLimit)
                pindex = pindex->pprev;
            return pindex->nBits;
        }
        return pindexLast->nBits;
    }

    return CalculateNextWorkRequired(pindexPrev, pindexPrevPrev->GetBlockTime(), params, fProofOfStake);
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params, bool fProofOfStake)
{
    if(fProofOfStake){
        if (params.fPoSNoRetargeting)
            return pindexLast->nBits;
    }else{
        if (params.fPowNoRetargeting)
            return pindexLast->nBits;
    }
    // Limit adjustment step
    int nHeight = pindexLast->nHeight + 1;
    int64_t nTargetSpacing = params.TargetSpacing(nHeight);
    int64_t nActualSpacing = pindexLast->GetBlockTime() - nFirstBlockTime;
    // Retarget
    const arith_uint256 bnTargetLimit = GetLimit(nHeight, params, fProofOfStake);
    // ppcoin: target change every block
    // ppcoin: retarget with exponential moving toward target spacing
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    int64_t nInterval = params.DifficultyAdjustmentInterval(nHeight); 

    if (nHeight < params.QIP9Height) {
        if (nActualSpacing < 0)
            nActualSpacing = nTargetSpacing;
        if (nActualSpacing > nTargetSpacing * 10)
            nActualSpacing = nTargetSpacing * 10;
        bnNew *= ((nInterval - 1) * nTargetSpacing + nActualSpacing + nActualSpacing);
        bnNew /= ((nInterval + 1) * nTargetSpacing);
    } else {
        if (nActualSpacing < 0)
            nActualSpacing = nTargetSpacing;
        if (nActualSpacing > nTargetSpacing * 20)
            nActualSpacing = nTargetSpacing * 20;
        uint32_t stakeTimestampMask=params.StakeTimestampMask(nHeight);
        bnNew = mul_exp(bnNew, 2 * (nActualSpacing - nTargetSpacing) / (stakeTimestampMask + 1), (nInterval + 1) * nTargetSpacing / (stakeTimestampMask + 1));
    }

    if (bnNew <= 0 || bnNew > bnTargetLimit)
        bnNew = bnTargetLimit;
    return bnNew.GetCompact();
}

// Check that on difficulty adjustments, the new difficulty does not increase
// or decrease beyond the permitted limits.
#ifdef BIT_BUILD
bool PermittedDifficultyTransition(const Consensus::Params&, int64_t, uint32_t, uint32_t)
{
    // Qtum has different difficulty adjustment algorithm than Bitcoin, so checking the borders for the new difficulty value might not be the same.
    // The method is used for unit testing and to reject headers (headerssync.cpp) during synching for Bitcoin depending on the difficulty transition.
    return true;
}
#else
bool PermittedDifficultyTransition(const Consensus::Params& params, int64_t height, uint32_t old_nbits, uint32_t new_nbits)
{
    if (params.fPowAllowMinDifficultyBlocks) return true;

    if (height % params.DifficultyAdjustmentInterval(height) == 0) {
        int64_t smallest_timespan = params.nPowTargetTimespan/4;
        int64_t largest_timespan = params.nPowTargetTimespan*4;

        const arith_uint256 pow_limit = UintToArith256(params.powLimit);
        arith_uint256 observed_new_target;
        observed_new_target.SetCompact(new_nbits);

        // Calculate the largest difficulty value possible:
        arith_uint256 largest_difficulty_target;
        largest_difficulty_target.SetCompact(old_nbits);
        largest_difficulty_target *= largest_timespan;
        largest_difficulty_target /= params.nPowTargetTimespan;

        if (largest_difficulty_target > pow_limit) {
            largest_difficulty_target = pow_limit;
        }

        // Round and then compare this new calculated value to what is
        // observed.
        arith_uint256 maximum_new_target;
        maximum_new_target.SetCompact(largest_difficulty_target.GetCompact());
        if (maximum_new_target < observed_new_target) return false;

        // Calculate the smallest difficulty value possible:
        arith_uint256 smallest_difficulty_target;
        smallest_difficulty_target.SetCompact(old_nbits);
        smallest_difficulty_target *= smallest_timespan;
        smallest_difficulty_target /= params.nPowTargetTimespan;

        if (smallest_difficulty_target > pow_limit) {
            smallest_difficulty_target = pow_limit;
        }

        // Round and then compare this new calculated value to what is
        // observed.
        arith_uint256 minimum_new_target;
        minimum_new_target.SetCompact(smallest_difficulty_target.GetCompact());
        if (minimum_new_target > observed_new_target) return false;
    } else if (old_nbits != new_nbits) {
        return false;
    }
    return true;
}
#endif

unsigned int BetweenAlgorithmSmoother(const CBlockIndex* pindexLast, const Consensus::Params& params)
{
    const int smoothing_period = 12;
    const arith_uint256 powLimit = UintToArith256(params.powLimit);

    if (pindexLast->nHeight + 1 >= params.switchAlgoHeight &&
        pindexLast->nHeight + 1 < params.switchAlgoHeight + smoothing_period) {
//        LogPrint(BCLog::POW, "%s: returning powLimit at height %d\n", __func__, pindexLast->nHeight + 1);
        return powLimit.GetCompact();
    }

    return Lwma3CalculateNextWorkRequired(pindexLast, params);
}

unsigned int Lwma3CalculateNextWorkRequired(const CBlockIndex* pindexLast, const Consensus::Params& params)
{
    const int64_t T = params.nPowTargetSpacing;
    const int64_t N = 24;
    const int64_t k = N * (N + 1) * T / 2;
    const int64_t height = pindexLast->nHeight;
    const arith_uint256 powLimit = UintToArith256(params.powLimit);

    if (height < N) { return powLimit.GetCompact(); }

    arith_uint256 sumTarget, nextTarget;
    int64_t thisTimestamp, previousTimestamp;
    int64_t t = 0, j = 0;

    const CBlockIndex* blockPreviousTimestamp = pindexLast->GetAncestor(height - N);
    previousTimestamp = blockPreviousTimestamp->GetBlockTime();

    // Loop through N most recent blocks.
    for (int64_t i = height - N + 1; i <= height; i++) {
        const CBlockIndex* block = pindexLast->GetAncestor(i);
        thisTimestamp = (block->GetBlockTime() > previousTimestamp) ?
                         block->GetBlockTime() : previousTimestamp + 1;
        int64_t solvetime = std::min(6 * T, thisTimestamp - previousTimestamp);
        previousTimestamp = thisTimestamp;
        j++;
        t += solvetime * j; // Weighted solvetime sum.
        arith_uint256 target;
        target.SetCompact(block->nBits);
        sumTarget += target / (k * N);
    }
    nextTarget = t * sumTarget;
    if (nextTarget > powLimit) { nextTarget = powLimit; }

  //  LogPrint(BCLog::POW, "%s: returning %08x at height %d\n", __func__, nextTarget.GetCompact(), pindexLast->nHeight + 1);

    return nextTarget.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{

// local bypass for 2 blocks
    if (hash == uint256S("0x17aba88a5898c72efcefe8c49107d614ee2c3be119d3bf8dcf314a29df64ee08")) return true;
    if (hash == uint256S("0x0489a360021a5e3f12d0fe9205609a0fb81e34f64441f2f4ba7a0b7f61cd8225")) return true;
    if (hash == uint256S("0x000000000000000289df99201ccaa6e4ab5c43e4b6b04b80822f32e8c804b121")) return true;
    if (hash == uint256S("0x000000000000000575cbbe878e2a170ec6fdea27e44b3ecf733400bb0cae4e41")) return true;

    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}

bool CheckProofOfWorkForAlgorithm(uint256 hash, unsigned int nBits, Algorithm algoType)
{
    // local bypass for 2 blocks
    if (hash == uint256S("0x17aba88a5898c72efcefe8c49107d614ee2c3be119d3bf8dcf314a29df64ee08")) return true;
    if (hash == uint256S("0x0489a360021a5e3f12d0fe9205609a0fb81e34f64441f2f4ba7a0b7f61cd8225")) return true;
    if (hash == uint256S("0x000000000000000289df99201ccaa6e4ab5c43e4b6b04b80822f32e8c804b121")) return true;
    if (hash == uint256S("0x000000000000000575cbbe878e2a170ec6fdea27e44b3ecf733400bb0cae4e41")) return true;

    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    const Consensus::Params& consensusParams = Params().GetConsensus();
    uint256 powLimit = algoType == SHA256D ? consensusParams.powLimit : consensusParams.powLimit;
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}

