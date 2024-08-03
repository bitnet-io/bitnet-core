#ifndef BIT_WALLET_RPC_CONTRACT_H
#define BIT_WALLET_RPC_CONTRACT_H

#include <span.h>

class CRPCCommand;

namespace wallet {
Span<const CRPCCommand> GetContractRPCCommands();
} // namespace wallet

#endif // BIT_WALLET_RPC_CONTRACT_H
