#ifndef BIT_WALLET_RPC_MINING_H
#define BIT_WALLET_RPC_MINING_H

#include <span.h>

class CRPCCommand;

namespace wallet {
Span<const CRPCCommand> GetMiningRPCCommands();
} // namespace wallet

#endif // BIT_WALLET_RPC_MINING_H
