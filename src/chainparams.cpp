// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Merge developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/*
 * Main network
 */

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,  uint256("0x00000e44bca505863831d65cf302884eaf6eed296dc59088e89324bccf5d9dca"))
    (5,  uint256("0x000000c286816d11a56d750f7a060860cc915d7153bd86766fa77a3d7a2b01dc"))
    (10, uint256("0x000007e0ba8c10fca3dd32a453f1c92c834f91e9e424e9ef4f70568c108e56fe"))
    (15, uint256("0x00000430b1e322298082e63175fafa7bccd907e3c2c0a860011184e92181e8f1"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1545670000, 1, 1};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000009adaa70b13db675071f0c3cebb79775a6229f2774e2f5cfed05066613ff"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1545670001, 1, 1};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x0000000000000000000000000000000000000000000000000000000000000000"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0, 0, 0 };

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        pchMessageStart[0] = 0xef;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0xee;
        pchMessageStart[3] = 0x3a;
        vAlertPubKey = ParseHex("041904d259d4f4a0d985cb6f91a4357fec00db8b5957244aa4c3449f87520a3f356a0455b1637e352c6bfba5f1c8a50fd08441a5bfd8f18c546e0dc48822c34bef");
        nDefaultPort = 52000;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60;
        nTargetSpacing = 1 * 60;
        nStakeMinAge = 60 * 60;
        nMaturity = 25;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;
        nLastPOWBlock = 57601;
        nModifierUpdateBlock = 50;

        const char* pszTimestamp = "ABC News 24/DEC/2018 Trump's Treasury Secretary to convene 'Plunge Protection Team' to deal with Wall Street rout";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1545670000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1997235;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e44bca505863831d65cf302884eaf6eed296dc59088e89324bccf5d9dca"));
        assert(genesis.hashMerkleRoot == uint256("0x2b77d68f79c8c45b77335607c928533950da763a4a16c34555bdf8446aa6cc1c"));

        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("projectmerge.org", "seed.projectmerge.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 50); // M
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 53); // N
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 178);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0421783d5f8b38c2f71f10a7e8a4c5df39bfe1d3ca10dd17e5fc76ff5b523ab21e89ae0276aae967d0d7f26c3f34136acdc0a2f41bab19cc262658703f38a3da55";
        strObfuscationPoolDummyAddress = "MERGEXXXXXXXXXXXXXXXXXXXXXXXYmkoB4";
        nStartMasternodePayments = genesis.nTime + 5400;
        nBudget_Fee_Confirmations = 6;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/*
 * Testnet (v3) - Debut
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0x3f;
        vAlertPubKey = ParseHex("045f8e3e3efeb5de4621aa0c539497eee9b2b07a1f4419ef39e0cc49bf83da11089fc20096bd94366a992a7afb184ae84a6f517ba93eee583bedf7db3f10c17e4c");
        nDefaultPort = 62000;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60;
        nTargetSpacing = 1 * 60;
        nStakeMinAge = 60 * 60;
        nMaturity = 25;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 50;

        genesis.nVersion = 1;
        genesis.nTime = 1545670001;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1940182;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009adaa70b13db675071f0c3cebb79775a6229f2774e2f5cfed05066613ff"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("myexplorer.org", "mergetestnet.myexplorer.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 80); // Z
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83); // a
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 208);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04310cda8b6a460200b5c69ecaf74d20cb92a84815cbc82ebe8dd153afeff3de5a3ee487d83bcdf71600be49304ce2f808a73fb0d489bef124e364d69c4b87fc74";
        strObfuscationPoolDummyAddress = "ZERGEXXXXXXXXXXXXXXXXXXXXXXXcMy12n";
        nStartMasternodePayments = genesis.nTime + 5400;
        nBudget_Fee_Confirmations = 6;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CTestNetParams testNetParams;

/*
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 1 * 60;
        nStakeMinAge = 20 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;

        vFixedSeeds.clear();
        vSeeds.clear();

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/*
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear();
        vSeeds.clear();

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;

static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

