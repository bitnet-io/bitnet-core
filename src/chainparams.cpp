// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <deploymentinfo.h>
#include <consensus/consensus.h>
#include <hash.h> // for signet block challenge hash
#include <script/interpreter.h>
#include <util/string.h>
#include <util/system.h>
#include <util/convert.h>

#include <assert.h>

///////////////////////////////////////////// // qtum
#include <libdevcore/SHA3.h>
#include <libdevcore/RLP.h>
#include "arith_uint256.h"
#include <cinttypes>

/////////////////////////////////////////////

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
//    genesis.hashStateRoot = uint256(h256Touint(dev::h256("9514771014c9ae803d8cea2731b2063e83de44802b40dce2d06acd02d0ff65e9"))); // qtum
    genesis.hashStateRoot = uint256(h256Touint(dev::h256("e965ffd002cd6ad0e2dc402b8044de833e06b23127ea8c3d80aec91410771495"))); // qtum

    genesis.hashUTXORoot = uint256(h256Touint(dev::sha3(dev::rlp("")))); // qtum
    return genesis;

}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{

 const char* pszTimestamp = "Segwit added to Bitnet restart 02-26-2023";
    const CScript genesisOutputScript = CScript() << ParseHex("04594c39e7eacaa78d2bb0073725c1b75187a1a5b12a8e78d5222c9efacd7e37bb1455a582c2f6b2ac6b60d2899376780367f2a9aad91d42f23cd9f60663575bad") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);

}

/**
 * Main network on which people trade goods and services.
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 6000000; // qtum halving every 4 years
        consensus.script_flag_exceptions.emplace( // BIP16 exception
            uint256S("0x00000caff19214512f927af2b7cead4b33a54c096e432a275628cb4cf8d4b73c"), SCRIPT_VERIFY_NONE);
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00000caff19214512f927af2b7cead4b33a54c096e432a275628cb4cf8d4b73c");
        consensus.BIP65Height = 0; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 0; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931
        consensus.CSVHeight = 10; // 000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5
        consensus.SegwitHeight = 10; // 0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893

        consensus.switchAlgoHeight = 125000;    // activate aurum @ 125,000 height
        consensus.MinBIP9WarningHeight = 2026; // segwit activation height + miner confirmation window

        consensus.QIP5Height = 207020;
        consensus.QIP6Height = 207020;
        consensus.QIP7Height = 207020;
        consensus.QIP9Height = 207020;
        consensus.nOfflineStakeHeight = 207020;
        consensus.nReduceBlocktimeHeight = 6000000;
        consensus.nMuirGlacierHeight = 207020;
        consensus.nLondonHeight = 207020;
        consensus.nShanghaiHeight = 207020;




        consensus.powLimit = uint256S      ("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
//        consensus.posLimit = uint256S      ("00000ffff0ffffffffffffffffffffffffffffffffffffffffffffffffffffff");
//        consensus.QIP9PosLimit = uint256S  ("00000ffff0ffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
//        consensus.RBTPosLimit = uint256S   ("00000ffff0ffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.posLimit = uint256S      ("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S  ("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S   ("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nPowTargetTimespan = 24 * 60 * 60; // 16 minutes
        consensus.nPowTargetTimespanV2 = 24 * 60 * 60;
        consensus.nRBTPowTargetTimespan = 24 * 60 * 60;
        consensus.nPowTargetSpacing = 3.5 * 60;
        consensus.nRBTPowTargetSpacing = 3.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 90% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
//        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
//        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 0;
//        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        // Min block number for activation, the number must be divisible by 2016
        // Replace 0xffffc0 with the activation block number
//        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 2080512;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000001c098a087afb5f07823"); // 94000~
       consensus.defaultAssumeValid = uint256S("0x000000000000002d05e938bb1360c7dea3f15628eacb260fd5657d839c4e58c6"); // 92345 current 10-24-2023


        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */

        pchMessageStart[0] = 0xd1;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xd1;
        pchMessageStart[3] = 0xe1;
        nDefaultPort = 13333;
        nPruneAfterHeight = 6000000;
        m_assumed_blockchain_size = 21;
        m_assumed_chain_state_size = 6;


         genesis = CreateGenesisBlock(1677414786, 1196422, 0x1e0ffff0, 1, 88 * COIN);






/*
		GENESIS VERIFY/GENERATOR SCRIPT
	
        consensus.hashGenesisBlock = uint256S("0x00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        if (true && (genesis.GetHash() != consensus.hashGenesisBlock)) {
            std::cout << std::string("Begin calculating Mainnet Genesis Block:\n");
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 hash;
            genesis.nNonce = 0;
            while (UintToArith256(genesis.GetHash()) > hashTarget) {
                ++genesis.nNonce;
                if (genesis.nNonce == 0) {
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 1000 == 0) {
                    std::cout << strNetworkID << " nonce: " << genesis.nNonce << " time: " << genesis.nTime << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
                }
            }

            printf(" Mainnet ---\n");
            std::cout << std::string(" main_nonce: ") << ("%" PRIu32, genesis.nNonce) << std::endl;
            std::cout << std::string(" main_time: ") << ("%" PRIu32, genesis.nTime) << std::endl;
            std::cout << std::string(" main_hash: ") << ("%" PRIu32, genesis.GetHash().ToString().c_str()) << std::endl;
            std::cout << std::string(" main_merklehash: ") << ("%" PRIu32, genesis.hashMerkleRoot.ToString().c_str()) << std::endl;
            std::cout << std::string(" Main Genesis hashStateRoot: ") << ("%" PRIu32,  genesis.hashStateRoot.ToString().c_str()) << std::endl;
            std::cout << std::string(" Main Genesis hashUTXOroot: ") << ("%" PRIu32,  genesis.hashUTXORoot.ToString().c_str()) << std::endl;
            printf("min Main nBit:  %08x\n", consensus.powLimit);
            std::cout << std::string("Finished calculating Mainnet Genesis Block for SED replacement of current assertion and values:") << std::endl;



        }

*/


/*
 Mainnet ---
 main_nonce: 1196422
 main_time: 1677414786
 main_hash: 00000caff19214512f927af2b7cead4b33a54c096e432a275628cb4cf8d4b73c
 main_merklehash: b7421cb345a400ccd9e924c4c5afad4114be25f7a928956f52df5524bb1ca181
 Main Genesis hashStateRoot: 9514771014c9ae803d8cea2731b2063e83de44802b40dce2d06acd02d0ff65e9
 Main Genesis hashUTXOroot: 21b463e3b52f6201c0ad6c991be0485b6ef8c092e64583ffa655cc1b171fe856
*/



        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000caff19214512f927af2b7cead4b33a54c096e432a275628cb4cf8d4b73c"));
        assert(genesis.hashMerkleRoot == uint256S("0xb7421cb345a400ccd9e924c4c5afad4114be25f7a928956f52df5524bb1ca181"));



        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as an addrfetch if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
//        vSeeds.emplace_back("qtum3.dynu.net"); // Qtum mainnet
//        vSeeds.emplace_back("qtum5.dynu.net"); // Qtum mainnet
//        vSeeds.emplace_back("qtum6.dynu.net"); // Qtum mainnet
//        vSeeds.emplace_back("qtum7.dynu.net"); // Qtum mainnet


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,22);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,158);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "bit";

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_main), std::end(chainparams_seed_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                { 203471, uint256S("0x0f00c9744dbe5b0541913dd5f63e15866ebcce0b723a8d11dba2db7988ff5333")},

            }
        };

        m_assumeutxo_data = MapAssumeutxo{
         // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
	  // Data from rpc: getchaintxstats
            /* nTime    */ //1684633076,
            /* nTxCount */ //43308,
            /* dTxRate  */ //0.005

           .nTime    = 1722637360, // * UNIX timestamp of last known number of transactions
            .nTxCount = 322415, // * total number of transactions between genesis and that timestamp
            .dTxRate  = 0.005320414534712683, // * estimated number of transactions per second after that timestamp


        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 10;
        consensus.nRBTCoinbaseMaturity = 10;
        consensus.nSubsidyHalvingIntervalV2 = 6000000;
        consensus.nLastPOWBlock = 6000000;
        consensus.nLastBigReward = 6000000;
        consensus.nMPoSRewardRecipients = 10000;
        consensus.nFirstMPoSBlock = 207020;
        consensus.nLastMPoSBlock = 6000000;


        consensus.nFixUTXOCacheHFHeight = 6000000;
        consensus.nEnableHeaderSignatureHeight = 6000000;
        consensus.nCheckpointSpan = 6000000;
        consensus.nRBTCheckpointSpan = 6000000;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;
    }
};

/**
 * Testnet (v3): public test network which is reset from time to time.
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 985500; // qtum halving every 4 years
        consensus.script_flag_exceptions.emplace( // BIP16 exception
            uint256S("0x0000e803ee215c0684ca0d2f9220594d3f828617972aad66feb2ba51f5e14222"), SCRIPT_VERIFY_NONE);
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0000e803ee215c0684ca0d2f9220594d3f828617972aad66feb2ba51f5e14222");
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 6048; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 6048; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 8064; // segwit activation height + miner confirmation window
        consensus.QIP5Height = 446320;
        consensus.QIP6Height = 446320;
        consensus.QIP7Height = 446320;
        consensus.QIP9Height = 446320;
        consensus.nOfflineStakeHeight = 625000;
        consensus.nReduceBlocktimeHeight = 806600;
        consensus.nMuirGlacierHeight = 806600;
        consensus.nLondonHeight = 1967616;
        consensus.nShanghaiHeight = 3298892;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        // Min block number for activation, the number must be divisible by 2016
        // Replace 0xffffc0 with the activation block number
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 1967616;

        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000213cff04c2108ab7d5a"); // 3180000
        consensus.defaultAssumeValid = uint256S("0xde6afcb300f7036b67b7446933b8aa7986850058d5927e07ce5df1e270069ef2"); // 3180000

        pchMessageStart[0] = 0x0d;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x06;
        nDefaultPort = 13888;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 10;
        m_assumed_chain_state_size = 1;

//        genesis = CreateGenesisBlock(1504695029, 7349697, 0x1f00ffff, 1, 50 * COIN);
//        consensus.hashGenesisBlock = genesis.GetHash();
//        assert(consensus.hashGenesisBlock == uint256S("0x0000e803ee215c0684ca0d2f9220594d3f828617972aad66feb2ba51f5e14222"));
//        assert(genesis.hashMerkleRoot == uint256S("0xed34050eb5909ee535fcb07af292ea55f3d2f291187617b44d3282231405b96d"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("qtum4.dynu.net"); // Qtum testnet

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,120);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tq";

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_test), std::end(chainparams_seed_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                {0, uint256S("0x0000e803ee215c0684ca0d2f9220594d3f828617972aad66feb2ba51f5e14222")},
                {5000, uint256S("0x000000302bc22f2f65995506e757fff5c824545db5413e871d57d27a0997e8a0")}, //last PoW block
                {77000, uint256S("0xf41e2e8d09bca38827c23cad46ed6d434902da08415d2314d0c8ce285b1970cb")},
                {230000, uint256S("0xcd17baf80fa817dd543b83897ccb1e07350019e5b812f4956f69efe855d62601")},
                {343000, uint256S("0xac66f1de1a5fa473b5097b313c203e97d45669485e4c235a32a0f80df64f6948")},
                {441632, uint256S("0x2cb93f74cb3e47ec05b745a445f90a023b7136a68f94e9bff7fb49819155ccd8")},
                {491300, uint256S("0x75a7db2865423d3af5f0dfd70cfef6053b91f3c018c4b28a4e28c09a8c011e78")},
                {690000, uint256S("0x89b010b5333fa9d22c7fcf157c7eeaee1ccfe80c435390243b3d782a1fc1eff7")},
                {944000, uint256S("0x6bb6312088d81ca5484460b3466c66c01ff7d1cd4ef91e1dc9555a15b51d025d")},
                {1405000, uint256S("0xaff1f9c768e83f90d10a55306993e9042b5740251abc1afdde1429d09e95fa66")},
                {1930000, uint256S("0xf4836510a70e25d5c70554abbbcb346abd66af540f616d806fb1c20335c1e874")},
                {2686000, uint256S("0xc12594feff0dfae05f5a056cd9248ff5e6fc42d37c4bedf37b212eb17dccb486")},
				{3180000, uint256S("0xde6afcb300f7036b67b7446933b8aa7986850058d5927e07ce5df1e270069ef2")},
            }
        };

        m_assumeutxo_data = MapAssumeutxo{
            // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            // Data as of block 0xde6afcb300f7036b67b7446933b8aa7986850058d5927e07ce5df1e270069ef2 (height 3180000)
            .nTime    = 1692923320,
            .nTxCount = 6552961,
            .dTxRate  = 0.06299127541669518,
        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // qtum halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 5000;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    consensus.nCoinbaseMaturity;
        consensus.nLastMPoSBlock = 624999;

        consensus.nFixUTXOCacheHFHeight = 84500;
        consensus.nEnableHeaderSignatureHeight = 391993;
        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;
    }
};

/**
 * Signet: test network with an additional consensus parameter (see BIP325).
 */
class SigNetParams : public CChainParams {
public:
    explicit SigNetParams(const ArgsManager& args) {
        std::vector<uint8_t> bin;
        vSeeds.clear();

        if (!args.IsArgSet("-signetchallenge")) {
            bin = ParseHex("51210276aa67f74d27c3dcd4be86ca8375a4d70b1e00f7787451d8445c647a3c099ee7210276aa67f74d27c3dcd4be86ca8375a4d70b1e00f7787451d8445c647a3c099ee752ae");

            consensus.nMinimumChainWork = uint256{};
            consensus.defaultAssumeValid = uint256{};
            m_assumed_blockchain_size = 1;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                // Data from RPC: getchaintxstats 4096 000000d1a0e224fa4679d2fb2187ba55431c284fa1b74cbc8cfda866fd4d2c09
                .nTime    = 0,
                .nTxCount = 0,
                .dTxRate  = 0,
            };
        } else {
            const auto signet_challenge = args.GetArgs("-signetchallenge");
            if (signet_challenge.size() != 1) {
                throw std::runtime_error(strprintf("%s: -signetchallenge cannot be multiple values.", __func__));
            }
            bin = ParseHex(signet_challenge[0]);

            consensus.nMinimumChainWork = uint256{};
            consensus.defaultAssumeValid = uint256{};
            m_assumed_blockchain_size = 0;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                0,
                0,
                0,
            };
            LogPrintf("Signet with challenge %s\n", signet_challenge[0]);
        }

        if (args.IsArgSet("-signetseednode")) {
            vSeeds = args.GetArgs("-signetseednode");
        }

        strNetworkID = CBaseChainParams::SIGNET;
        consensus.signet_blocks = true;
        consensus.signet_challenge.assign(bin.begin(), bin.end());
        consensus.nSubsidyHalvingInterval = 985500;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256{};
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.QIP5Height = 0;
        consensus.QIP6Height = 0;
        consensus.QIP7Height = 0;
        consensus.QIP9Height = 0;
        consensus.nOfflineStakeHeight = 1;
        consensus.nReduceBlocktimeHeight = 0;
        consensus.nMuirGlacierHeight = 0;
        consensus.nLondonHeight = 0;
        consensus.nShanghaiHeight = 0;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1815; // 90% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.MinBIP9WarningHeight = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        // Activation of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        // message start is defined as the first 4 bytes of the sha256d of the block script
        HashWriter h{};
        h << consensus.signet_challenge;
        uint256 hash = h.GetHash();
        memcpy(pchMessageStart, hash.begin(), 4);

        nDefaultPort = 33888;
        nPruneAfterHeight = 1000;

//        genesis = CreateGenesisBlock(1623662135, 7377285, 0x1f00ffff, 1, 50 * COIN);
//        consensus.hashGenesisBlock = genesis.GetHash();
//        assert(consensus.hashGenesisBlock == uint256S("0x0000e0d4bc95abd1c0fcef0abb2795b6e8525f406262d59dc60cd3c490641347"));
//        assert(genesis.hashMerkleRoot == uint256S("0xed34050eb5909ee535fcb07af292ea55f3d2f291187617b44d3282231405b96d"));

        vFixedSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,120);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tq";

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // qtum halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 0x7fffffff;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = 5000;
        consensus.nLastMPoSBlock = 0;

        consensus.nFixUTXOCacheHFHeight = 0;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;
    }
};

/**
 * Regression test: intended for private networks only. Has minimal difficulty to ensure that
 * blocks can be found instantly.
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 985500;
        consensus.BIP34Height = 1; // Always active unless overridden
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1;  // Always active unless overridden
        consensus.BIP66Height = 1;  // Always active unless overridden
        consensus.CSVHeight = 1;    // Always active unless overridden
        consensus.SegwitHeight = 0; // Always active unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.QIP5Height = 0;
        consensus.QIP6Height = 0;
        consensus.QIP7Height = 0;
        consensus.QIP9Height = 0;
        consensus.nOfflineStakeHeight = 1;
        consensus.nReduceBlocktimeHeight = 0;
        consensus.nMuirGlacierHeight = 0;
        consensus.nLondonHeight = 0;
        consensus.nShanghaiHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes (960 = 832 + 128; multiplier is 832)
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0; // No activation delay

        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay

        consensus.nMinimumChainWork = uint256{};
        consensus.defaultAssumeValid = uint256{};

        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xdd;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xe1;
        nDefaultPort = 23888;
        nPruneAfterHeight = args.GetBoolArg("-fastprune", false) ? 100 : 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

//        genesis = CreateGenesisBlock(1504695029, 17, 0x207fffff, 1, 50 * COIN);
//        consensus.hashGenesisBlock = genesis.GetHash();
//        assert(consensus.hashGenesisBlock == uint256S("0x665ed5b402ac0b44efc37d8926332994363e8a7278b7ee9a58fb972efadae943"));
//        assert(genesis.hashMerkleRoot == uint256S("0xed34050eb5909ee535fcb07af292ea55f3d2f291187617b44d3282231405b96d"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();
        vSeeds.emplace_back("dummySeed.invalid.");

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                {0, uint256S("665ed5b402ac0b44efc37d8926332994363e8a7278b7ee9a58fb972efadae943")},
            }
        };

        m_assumeutxo_data = MapAssumeutxo{
         // TODO to be specified in a future patch.
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // qtum halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 0x7fffffff;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = 5000;
        consensus.nLastMPoSBlock = 0;

        consensus.nFixUTXOCacheHFHeight=0;
        consensus.nEnableHeaderSignatureHeight = 0;

        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,120);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "qcrt";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout, int min_activation_height)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
        consensus.vDeployments[d].min_activation_height = min_activation_height;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

static void MaybeUpdateHeights(const ArgsManager& args, Consensus::Params& consensus)
{
    for (const std::string& arg : args.GetArgs("-testactivationheight")) {
        const auto found{arg.find('@')};
        if (found == std::string::npos) {
            throw std::runtime_error(strprintf("Invalid format (%s) for -testactivationheight=name@height.", arg));
        }
        const auto name{arg.substr(0, found)};
        const auto value{arg.substr(found + 1)};
        int32_t height;
        if (!ParseInt32(value, &height) || height < 0 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Invalid height value (%s) for -testactivationheight=name@height.", arg));
        }
        if (name == "segwit") {
            consensus.SegwitHeight = int{height};
        } else if (name == "bip34") {
            consensus.BIP34Height = int{height};
        } else if (name == "dersig") {
            consensus.BIP66Height = int{height};
        } else if (name == "cltv") {
            consensus.BIP65Height = int{height};
        } else if (name == "csv") {
            consensus.CSVHeight = int{height};
        } else {
            throw std::runtime_error(strprintf("Invalid name (%s) for -testactivationheight=name@height.", arg));
        }
    }
}

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    MaybeUpdateHeights(args, consensus);

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams = SplitString(strDeployment, ':');
        if (vDeploymentParams.size() < 3 || 4 < vDeploymentParams.size()) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end[:min_activation_height]");
        }
        int64_t nStartTime, nTimeout;
        int min_activation_height = 0;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        if (vDeploymentParams.size() >= 4 && !ParseInt32(vDeploymentParams[3], &min_activation_height)) {
            throw std::runtime_error(strprintf("Invalid min_activation_height (%s)", vDeploymentParams[3]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout, min_activation_height);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld, min_activation_height=%d\n", vDeploymentParams[0], nStartTime, nTimeout, min_activation_height);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

/**
 * Regression network parameters overwrites for unit testing
 */
class CUnitTestParams : public CRegTestParams
{
public:
    explicit CUnitTestParams(const ArgsManager& args)
    : CRegTestParams(args)
    {
        // Activate the the BIPs for regtest as in Bitcoin
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = consensus.nBlocktimeDownscaleFactor*500 + 851; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = consensus.nBlocktimeDownscaleFactor*500 + 751; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.QIP6Height = consensus.nBlocktimeDownscaleFactor*500 + 500;
        consensus.QIP7Height = 0; // QIP7 activated on regtest

        // BIT have 500 blocks of maturity, increased values for regtest in unit tests in order to correspond with it
        consensus.nSubsidyHalvingInterval = 750;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*750;
        consensus.nRuleChangeActivationThreshold = consensus.nBlocktimeDownscaleFactor*558; // 75% for testchains
        consensus.nMinerConfirmationWindow = consensus.nBlocktimeDownscaleFactor*744; // Faster than normal for regtest (744 instead of 2016)

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;

        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity*2; // Increase the check point span for the reorganization tests from 500 to 1000
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity*2; // Increase the check point span for the reorganization tests from 500 to 1000

        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0;

        m_assumeutxo_data = MapAssumeutxo{
            {
                2010,
                {AssumeutxoHash{uint256S("0xf3ad83776715ee9b09a7a43421b6fe17701fb2247370a4ea9fcf0b073639cac9")}, 2010},
            },
            {
                2100,
                {AssumeutxoHash{uint256S("0x677f8902ca481677862d19fbe8c6214f596c8b475aabfe4273361485fc4e6fb4")}, 2100},
            },
        };
    }
};

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN) {
        return std::unique_ptr<CChainParams>(new CMainParams());
    } else if (chain == CBaseChainParams::TESTNET) {
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    } else if (chain == CBaseChainParams::SIGNET) {
        return std::unique_ptr<CChainParams>(new SigNetParams(args));
    } else if (chain == CBaseChainParams::REGTEST) {
        return std::unique_ptr<CChainParams>(new CRegTestParams(args));
    } else if (chain == CBaseChainParams::UNITTEST) {
        return std::unique_ptr<CChainParams>(new CUnitTestParams(args));
    }
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(gArgs, network);
}

std::string CChainParams::EVMGenesisInfo() const
{
    dev::eth::EVMConsensus evmConsensus;
    evmConsensus.QIP6Height = consensus.QIP6Height;
    evmConsensus.QIP7Height = consensus.QIP7Height;
    evmConsensus.nMuirGlacierHeight = consensus.nMuirGlacierHeight;
    evmConsensus.nLondonHeight = consensus.nLondonHeight;
    evmConsensus.nShanghaiHeight = consensus.nShanghaiHeight;
    return dev::eth::genesisInfoQtum(GetEVMNetwork(), evmConsensus);
}

std::string CChainParams::EVMGenesisInfo(int nHeight) const
{
    dev::eth::EVMConsensus evmConsensus(nHeight);
    return dev::eth::genesisInfoQtum(GetEVMNetwork(), evmConsensus);
}

std::string CChainParams::EVMGenesisInfo(const dev::eth::EVMConsensus& evmConsensus) const
{
    return dev::eth::genesisInfoQtum(GetEVMNetwork(), evmConsensus);
}

dev::eth::Network CChainParams::GetEVMNetwork() const
{
    return dev::eth::Network::qtumNetwork;
}

void CChainParams::UpdateOpSenderBlockHeight(int nHeight)
{
    consensus.QIP5Height = nHeight;
}

void UpdateOpSenderBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateOpSenderBlockHeight(nHeight);
}

void CChainParams::UpdateBtcEcrecoverBlockHeight(int nHeight)
{
    consensus.QIP6Height = nHeight;
}

void UpdateBtcEcrecoverBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateBtcEcrecoverBlockHeight(nHeight);
}

void CChainParams::UpdateConstantinopleBlockHeight(int nHeight)
{
    consensus.QIP7Height = nHeight;
}

void UpdateConstantinopleBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateConstantinopleBlockHeight(nHeight);
}

void CChainParams::UpdateDifficultyChangeBlockHeight(int nHeight)
{
    consensus.nSubsidyHalvingInterval = 985500; // qtum halving every 4 years
    consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // qtum halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)
    consensus.posLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.QIP9Height = nHeight;
    consensus.fPowAllowMinDifficultyBlocks = false;
    consensus.fPowNoRetargeting = true;
    consensus.fPoSNoRetargeting = false;
    consensus.nLastPOWBlock = 5000;
    consensus.nMPoSRewardRecipients = 10;
    consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                consensus.nMPoSRewardRecipients + 
                                consensus.nCoinbaseMaturity;
    consensus.nLastMPoSBlock = 0;
}

void UpdateDifficultyChangeBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateDifficultyChangeBlockHeight(nHeight);
}

void CChainParams::UpdateOfflineStakingBlockHeight(int nHeight)
{
    consensus.nOfflineStakeHeight = nHeight;
}

void UpdateOfflineStakingBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateOfflineStakingBlockHeight(nHeight);
}

void CChainParams::UpdateDelegationsAddress(const uint160& address)
{
    consensus.delegationsAddress = address;
}

void UpdateDelegationsAddress(const uint160& address)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateDelegationsAddress(address);
}

void CChainParams::UpdateLastMPoSBlockHeight(int nHeight)
{
    consensus.nLastMPoSBlock = nHeight;
}

void UpdateLastMPoSBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateLastMPoSBlockHeight(nHeight);
}

void CChainParams::UpdateReduceBlocktimeHeight(int nHeight)
{
    consensus.nReduceBlocktimeHeight = nHeight;
}

void UpdateReduceBlocktimeHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateReduceBlocktimeHeight(nHeight);
}

void CChainParams::UpdatePowAllowMinDifficultyBlocks(bool fValue)
{
    consensus.fPowAllowMinDifficultyBlocks = fValue;
}

void UpdatePowAllowMinDifficultyBlocks(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePowAllowMinDifficultyBlocks(fValuet);
}

void CChainParams::UpdatePowNoRetargeting(bool fValue)
{
    consensus.fPowNoRetargeting = fValue;
}

void UpdatePowNoRetargeting(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePowNoRetargeting(fValuet);
}

void CChainParams::UpdatePoSNoRetargeting(bool fValue)
{
    consensus.fPoSNoRetargeting = fValue;
}

void UpdatePoSNoRetargeting(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePoSNoRetargeting(fValuet);
}

void CChainParams::UpdateMuirGlacierHeight(int nHeight)
{
    consensus.nMuirGlacierHeight = nHeight;
}

void UpdateMuirGlacierHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateMuirGlacierHeight(nHeight);
}

void CChainParams::UpdateLondonHeight(int nHeight)
{
    consensus.nLondonHeight = nHeight;
}

void UpdateLondonHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateLondonHeight(nHeight);
}

void CChainParams::UpdateTaprootHeight(int nHeight)
{
    if(nHeight == 0)
    {
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = 0; // No activation delay
    }
    else
    {
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 0;
        // Min block number for activation, the number must be divisible with 144
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].min_activation_height = nHeight;
    }
}

void UpdateTaprootHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateTaprootHeight(nHeight);
}

void CChainParams::UpdateShanghaiHeight(int nHeight)
{
    consensus.nShanghaiHeight = nHeight;
}

void UpdateShanghaiHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateShanghaiHeight(nHeight);
}
