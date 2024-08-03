#ifndef BIT_WALLET_RPC_ADDRESSES_H
#define BIT_WALLET_RPC_ADDRESSES_H

#include <script/standard.h>
#include <univalue.h>

namespace wallet {
class CWallet;

UniValue DescribeWalletAddress(const CWallet& wallet, const CTxDestination& dest);
} //  namespace wallet

#endif // BIT_WALLET_RPC_ADDRESSES_H
