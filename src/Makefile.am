# Copyright (c) 2013-2016 The Bitnet Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Pattern rule to print variables, e.g. make print-top_srcdir
print-%: FORCE
	@echo '$*'='$($*)'

DIST_SUBDIRS = secp256k1

AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS) $(LTO_LDFLAGS) $(CORE_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS) $(LTO_CXXFLAGS) $(CORE_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS) $(CORE_CPPFLAGS) -DQTUM_BUILD
AM_LIBTOOLFLAGS = --preserve-dup-deps
PTHREAD_FLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_LIBS)
EXTRA_LIBRARIES =

lib_LTLIBRARIES =
noinst_LTLIBRARIES =

bin_PROGRAMS =
noinst_PROGRAMS =
check_PROGRAMS =
TESTS =
BENCHMARKS =

BITCOIN_INCLUDES=-I$(builddir) -I$(srcdir)/$(MINISKETCH_INCLUDE_DIR_INT) -I$(srcdir)/secp256k1/include -I$(srcdir)/$(UNIVALUE_INCLUDE_DIR_INT) $(LEVELDB_CPPFLAGS)
BITCOIN_INCLUDES += -I$(srcdir)/libff/libff
BITCOIN_INCLUDES += -I$(srcdir)/libff
BITCOIN_INCLUDES += -I$(srcdir)/evmone/evmc/include
BITCOIN_INCLUDES += -I$(srcdir)/evmone/include
BITCOIN_INCLUDES += -I$(srcdir)/eth_client
BITCOIN_INCLUDES += -I$(srcdir)/eth_client/utils
BITCOIN_INCLUDES += -I$(srcdir)/eth_client/utils/ethash/include
BITCOIN_INCLUDES += -I$(srcdir)/eth_client/utils/libscrypt

LIBBITCOIN_NODE=libbitnet_node.a
LIBBITCOIN_COMMON=libbitnet_common.a
LIBBITCOIN_CONSENSUS=libbitnet_consensus.a
LIBBITCOIN_CLI=libbitnet_cli.a
LIBBITCOIN_UTIL=libbitnet_util.a
LIBBITCOIN_CRYPTO_BASE=crypto/libbitnet_crypto_base.la
LIBBITCOINQT=qt/libbitnetqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBCRYPTOPP=cryptopp/libcryptopp.a
LIBFF=libff/libff.a

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libbitnet_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBBITCOINCONSENSUS=libbitnetconsensus.la
endif
if BUILD_BITCOIN_KERNEL_LIB
LIBBITCOINKERNEL=libbitnetkernel.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libbitnet_wallet.a
LIBBITCOIN_WALLET_TOOL=libbitnet_wallet_tool.a
endif

LIBBITCOIN_CRYPTO = $(LIBBITCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBBITCOIN_CRYPTO_SSE41 = crypto/libbitnet_crypto_sse41.la
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBBITCOIN_CRYPTO_AVX2 = crypto/libbitnet_crypto_avx2.la
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_AVX2)
endif
if ENABLE_X86_SHANI
LIBBITCOIN_CRYPTO_X86_SHANI = crypto/libbitnet_crypto_x86_shani.la
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_X86_SHANI)
endif
if ENABLE_ARM_SHANI
LIBBITCOIN_CRYPTO_ARM_SHANI = crypto/libbitnet_crypto_arm_shani.la
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_ARM_SHANI)
endif
noinst_LTLIBRARIES += $(LIBBITCOIN_CRYPTO)

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_NODE) \
  $(LIBBITCOIN_CLI) \
  $(LIBBITCOIN_IPC) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_WALLET_TOOL) \
  $(LIBBITCOIN_ZMQ)

if BUILD_BITCOIND
  bin_PROGRAMS += bitnetd
endif

if BUILD_BITCOIN_NODE
  bin_PROGRAMS += bitnet-node
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += bitnet-cli
endif

if BUILD_BITCOIN_TX
  bin_PROGRAMS += bitnet-tx
endif

if ENABLE_WALLET
if BUILD_BITCOIN_WALLET
  bin_PROGRAMS += bitnet-wallet
endif
endif

if BUILD_BITCOIN_UTIL
  bin_PROGRAMS += bitnet-util
endif

if BUILD_BITCOIN_CHAINSTATE
  bin_PROGRAMS += bitnet-chainstate
endif

.PHONY: FORCE check-symbols check-security
# bitnet core #
BITCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  addrman_impl.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  common/bloom.h \
  common/run_command.h \
  common/url.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/compat.h \
  compat/cpuid.h \
  compat/endian.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dbwrapper.h \
  deploymentinfo.h \
  deploymentstatus.h \
  external_signer.h \
  flatfile.h \
  fs.h \
  headerssync.h \
  httprpc.h \
  httpserver.h \
  i2p.h \
  index/base.h \
  index/blockfilterindex.h \
  index/coinstatsindex.h \
  index/disktxpos.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  init/common.h \
  interfaces/chain.h \
  interfaces/echo.h \
  interfaces/handler.h \
  interfaces/init.h \
  interfaces/ipc.h \
  interfaces/node.h \
  interfaces/wallet.h \
  kernel/chain.h \
  kernel/chainstatemanager_opts.h \
  kernel/checks.h \
  kernel/coinstats.h \
  kernel/context.h \
  kernel/cs_main.h \
  kernel/mempool_entry.h \
  kernel/mempool_limits.h \
  kernel/mempool_options.h \
  kernel/mempool_persist.h \
  kernel/validation_cache_sizes.h \
  key.h \
  key_io.h \
  logging.h \
  logging/timer.h \
  mapport.h \
  memusage.h \
  merkleblock.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  net_types.h \
  netaddress.h \
  netbase.h \
  netgroup.h \
  netmessagemaker.h \
  node/blockstorage.h \
  node/caches.h \
  node/chainstate.h \
  node/chainstatemanager_args.h \
  node/coin.h \
  node/coins_view_args.h \
  node/connection_types.h \
  node/context.h \
  node/database_args.h \
  node/eviction.h \
  node/interface_ui.h \
  node/mempool_args.h \
  node/mempool_persist_args.h \
  node/miner.h \
  node/minisketchwrapper.h \
  node/psbt.h \
  node/transaction.h \
  node/txreconciliation.h \
  node/utxo_snapshot.h \
  node/validation_cache_args.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/fees_args.h \
  policy/packages.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  randomenv.h \
  rest.h \
  reverse_iterator.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mempool.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/server_util.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/miniscript.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  signet.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  txorphanage.h \
  txrequest.h \
  undo.h \
  util/asmap.h \
  util/bip32.h \
  util/bitdeque.h \
  util/bytevectorhash.h \
  util/check.h \
  util/epochguard.h \
  util/error.h \
  util/fastrange.h \
  util/fees.h \
  util/getuniquepath.h \
  util/golombrice.h \
  util/hash_type.h \
  util/hasher.h \
  util/macros.h \
  util/message.h \
  util/moneystr.h \
  util/overflow.h \
  util/overloaded.h \
  util/rbf.h \
  util/readwritefile.h \
  util/result.h \
  util/serfloat.h \
  util/settings.h \
  util/sock.h \
  util/spanparsing.h \
  util/string.h \
  util/syscall_sandbox.h \
  util/syserror.h \
  util/system.h \
  util/thread.h \
  util/threadinterrupt.h \
  util/threadnames.h \
  util/time.h \
  util/tokenpipe.h \
  util/trace.h \
  util/translation.h \
  util/types.h \
  util/ui_change_type.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/bdb.h \
  wallet/coincontrol.h \
  wallet/coinselection.h \
  wallet/context.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/dump.h \
  wallet/external_signer_scriptpubkeyman.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/receive.h \
  wallet/rpc/util.h \
  wallet/rpc/wallet.h \
  wallet/salvage.h \
  wallet/scriptpubkeyman.h \
  wallet/spend.h \
  wallet/sqlite.h \
  wallet/transaction.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  walletinitinterface.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h \
  zmq/zmqutil.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libbitnet_util_a-clientversion.$(OBJEXT): obj/build.h

# node #
libbitnet_node_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(BOOST_CPPFLAGS) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libbitnet_node_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_node_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  dbwrapper.cpp \
  deploymentstatus.cpp \
  flatfile.cpp \
  headerssync.cpp \
  httprpc.cpp \
  httpserver.cpp \
  i2p.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/coinstatsindex.cpp \
  index/txindex.cpp \
  init.cpp \
  kernel/chain.cpp \
  kernel/checks.cpp \
  kernel/coinstats.cpp \
  kernel/context.cpp \
  kernel/cs_main.cpp \
  kernel/mempool_persist.cpp \
  mapport.cpp \
  net.cpp \
  net_processing.cpp \
  netgroup.cpp \
  node/blockstorage.cpp \
  node/caches.cpp \
  node/chainstate.cpp \
  node/chainstatemanager_args.cpp \
  node/coin.cpp \
  node/coins_view_args.cpp \
  node/connection_types.cpp \
  node/context.cpp \
  node/database_args.cpp \
  node/eviction.cpp \
  node/interface_ui.cpp \
  node/interfaces.cpp \
  node/mempool_args.cpp \
  node/mempool_persist_args.cpp \
  node/miner.cpp \
  node/minisketchwrapper.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  node/txreconciliation.cpp \
  node/utxo_snapshot.cpp \
  node/validation_cache_args.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/fees_args.cpp \
  policy/packages.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/fees.cpp \
  rpc/mempool.cpp \
  rpc/mining.cpp \
  rpc/net.cpp \
  rpc/node.cpp \
  rpc/output_script.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  rpc/server_util.cpp \
  rpc/signmessage.cpp \
  rpc/txoutproof.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  signet.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  txorphanage.cpp \
  txrequest.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BITCOIN_CORE_H)

if ENABLE_WALLET
libbitnet_node_a_SOURCES += wallet/init.cpp
libbitnet_node_a_CPPFLAGS += $(BDB_CPPFLAGS)
endif
if !ENABLE_WALLET
libbitnet_node_a_SOURCES += dummywallet.cpp
endif
#

# zmq #
if ENABLE_ZMQ
libbitnet_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbitnet_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp \
  zmq/zmqutil.cpp
endif
#

# wallet #
libbitnet_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(BOOST_CPPFLAGS) $(BDB_CPPFLAGS) $(SQLITE_CFLAGS)
libbitnet_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_wallet_a_SOURCES = \
  wallet/coincontrol.cpp \
  wallet/context.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/dump.cpp \
  wallet/external_signer_scriptpubkeyman.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/interfaces.cpp \
  wallet/load.cpp \
  wallet/receive.cpp \
  wallet/rpc/addresses.cpp \
  wallet/rpc/backup.cpp \
  wallet/rpc/coins.cpp \
  wallet/rpc/encrypt.cpp \
  wallet/rpc/spend.cpp \
  wallet/rpc/signmessage.cpp \
  wallet/rpc/transactions.cpp \
  wallet/rpc/util.cpp \
  wallet/rpc/wallet.cpp \
  wallet/scriptpubkeyman.cpp \
  wallet/spend.cpp \
  wallet/transaction.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(BITCOIN_CORE_H)

if USE_SQLITE
libbitnet_wallet_a_SOURCES += wallet/sqlite.cpp
endif
if USE_BDB
libbitnet_wallet_a_SOURCES += wallet/bdb.cpp wallet/salvage.cpp
endif
#

# wallet tool #
libbitnet_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(BOOST_CPPFLAGS)
libbitnet_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(BITCOIN_CORE_H)
#

# crypto #
crypto_libbitnet_crypto_base_la_CPPFLAGS = $(AM_CPPFLAGS)

# Specify -static in both CXXFLAGS and LDFLAGS so libtool will only build a
# static version of this library. We don't need a dynamic version, and a dynamic
# version can't be used on windows anyway because the library doesn't currently
# export DLL symbols.
crypto_libbitnet_crypto_base_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -static
crypto_libbitnet_crypto_base_la_LDFLAGS = $(AM_LDFLAGS) -static

crypto_libbitnet_crypto_base_la_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/aurum.c \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/muhash.h \
  crypto/muhash.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha3.cpp \
  crypto/sha3.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libbitnet_crypto_base_la_SOURCES += crypto/sha256_sse4.cpp
endif

# See explanation for -static in crypto_libbitnet_crypto_base_la's LDFLAGS and
# CXXFLAGS above
crypto_libbitnet_crypto_sse41_la_LDFLAGS = $(AM_LDFLAGS) -static
crypto_libbitnet_crypto_sse41_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -static
crypto_libbitnet_crypto_sse41_la_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitnet_crypto_sse41_la_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libbitnet_crypto_sse41_la_CPPFLAGS += -DENABLE_SSE41
crypto_libbitnet_crypto_sse41_la_SOURCES = crypto/sha256_sse41.cpp

# See explanation for -static in crypto_libbitnet_crypto_base_la's LDFLAGS and
# CXXFLAGS above
crypto_libbitnet_crypto_avx2_la_LDFLAGS = $(AM_LDFLAGS) -static
crypto_libbitnet_crypto_avx2_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -static
crypto_libbitnet_crypto_avx2_la_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitnet_crypto_avx2_la_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libbitnet_crypto_avx2_la_CPPFLAGS += -DENABLE_AVX2
crypto_libbitnet_crypto_avx2_la_SOURCES = crypto/sha256_avx2.cpp

# See explanation for -static in crypto_libbitnet_crypto_base_la's LDFLAGS and
# CXXFLAGS above
crypto_libbitnet_crypto_x86_shani_la_LDFLAGS = $(AM_LDFLAGS) -static
crypto_libbitnet_crypto_x86_shani_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -static
crypto_libbitnet_crypto_x86_shani_la_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitnet_crypto_x86_shani_la_CXXFLAGS += $(X86_SHANI_CXXFLAGS)
crypto_libbitnet_crypto_x86_shani_la_CPPFLAGS += -DENABLE_X86_SHANI
crypto_libbitnet_crypto_x86_shani_la_SOURCES = crypto/sha256_x86_shani.cpp

# See explanation for -static in crypto_libbitnet_crypto_base_la's LDFLAGS and
# CXXFLAGS above
crypto_libbitnet_crypto_arm_shani_la_LDFLAGS = $(AM_LDFLAGS) -static
crypto_libbitnet_crypto_arm_shani_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -static
crypto_libbitnet_crypto_arm_shani_la_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitnet_crypto_arm_shani_la_CXXFLAGS += $(ARM_SHANI_CXXFLAGS)
crypto_libbitnet_crypto_arm_shani_la_CPPFLAGS += -DENABLE_ARM_SHANI
crypto_libbitnet_crypto_arm_shani_la_SOURCES = crypto/sha256_arm_shani.cpp
#

# consensus #
libbitnet_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitnet_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_consensus_a_SOURCES = \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/amount.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/bitnetconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h
#

# common #
libbitnet_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(BOOST_CPPFLAGS) -DQTUM_BUILD
libbitnet_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  chainparams.cpp \
  coins.cpp \
  common/bloom.cpp \
  common/interfaces.cpp \
  common/run_command.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  deploymentinfo.cpp \
  external_signer.cpp \
  init/common.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  net_types.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/external_signer.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/request.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/miniscript.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  warnings.cpp \
  libff/libff/algebra/curves/public_params.hpp \
  libff/libff/algebra/curves/curve_utils.hpp \
  evmone/include/evmone/evmone.h \
  evmone/evmc/lib/instructions/instruction_metrics.c \
  evmone/evmc/lib/instructions/instruction_names.c \
  evmone/evmc/include/evmc/evmc.h \
  evmone/evmc/include/evmc/evmc.hpp \
  evmone/evmc/include/evmc/filter_iterator.hpp \
  evmone/evmc/include/evmc/helpers.h \
  evmone/evmc/include/evmc/hex.hpp \
  evmone/evmc/include/evmc/instructions.h \
  evmone/evmc/include/evmc/loader.h \
  evmone/evmc/include/evmc/mocked_host.hpp \
  evmone/evmc/include/evmc/tooling.hpp \
  evmone/evmc/include/evmc/utils.h \
  evmone/lib/evmone/advanced_analysis.cpp \
  evmone/lib/evmone/advanced_analysis.hpp \
  evmone/lib/evmone/advanced_execution.cpp \
  evmone/lib/evmone/advanced_execution.hpp \
  evmone/lib/evmone/advanced_instructions.cpp \
  evmone/lib/evmone/baseline.cpp \
  evmone/lib/evmone/baseline.hpp \
  evmone/lib/evmone/baseline_instruction_table.cpp \
  evmone/lib/evmone/baseline_instruction_table.hpp \
  evmone/lib/evmone/eof.cpp \
  evmone/lib/evmone/eof.hpp \
  evmone/lib/evmone/execution_state.hpp \
  evmone/lib/evmone/instructions_calls.cpp \
  evmone/lib/evmone/instructions.hpp \
  evmone/lib/evmone/instructions_opcodes.hpp \
  evmone/lib/evmone/instructions_storage.cpp \
  evmone/lib/evmone/instructions_traits.hpp \
  evmone/lib/evmone/instructions_xmacro.hpp \
  evmone/lib/evmone/opcodes_helpers.h \
  evmone/lib/evmone/tracing.cpp \
  evmone/lib/evmone/tracing.hpp \
  evmone/lib/evmone/vm.cpp \
  evmone/lib/evmone/vm.hpp \
 eth_client/libdevcore/Address.cpp \
  eth_client/libdevcore/Address.h \
  eth_client/libdevcore/Assertions.h \
  eth_client/libdevcore/Common.cpp \
  eth_client/libdevcore/Common.h \
  eth_client/libdevcore/CommonData.cpp \
  eth_client/libdevcore/CommonData.h \
  eth_client/libdevcore/CommonIO.cpp \
  eth_client/libdevcore/CommonIO.h \
  eth_client/libdevcore/DBFactory.cpp \
  eth_client/libdevcore/DBFactory.h \
  eth_client/libdevcore/Exceptions.h \
  eth_client/libdevcore/FileSystem.cpp \
  eth_client/libdevcore/FileSystem.h \
  eth_client/libdevcore/FixedHash.cpp \
  eth_client/libdevcore/FixedHash.h \
  eth_client/libdevcore/Guards.h \
  eth_client/libdevcore/JsonUtils.cpp \
  eth_client/libdevcore/JsonUtils.h \
  eth_client/libdevcore/LevelDB.cpp \
  eth_client/libdevcore/LevelDB.h \
  eth_client/libdevcore/Log.cpp \
  eth_client/libdevcore/Log.h \
  eth_client/libdevcore/OverlayDB.cpp \
  eth_client/libdevcore/OverlayDB.h \
  eth_client/libdevcore/RLP.cpp \
  eth_client/libdevcore/RLP.h \
  eth_client/libdevcore/SHA3.cpp \
  eth_client/libdevcore/SHA3.h \
  eth_client/libdevcore/StateCacheDB.cpp \
  eth_client/libdevcore/StateCacheDB.h \
  eth_client/libdevcore/TrieCommon.cpp \
  eth_client/libdevcore/TrieCommon.h \
  eth_client/libdevcore/TrieDB.h \
  eth_client/libdevcore/TrieHash.cpp \
  eth_client/libdevcore/TrieHash.h \
  eth_client/libdevcore/UndefMacros.h \
  eth_client/libdevcore/db.h \
  eth_client/libdevcore/dbfwd.h \
  eth_client/libdevcore/vector_ref.h \
  eth_client/libdevcrypto/Blake2.cpp \
  eth_client/libdevcrypto/Blake2.h \
  eth_client/libdevcrypto/Common.cpp \
  eth_client/libdevcrypto/Common.h \
  eth_client/libdevcrypto/CryptoPP.cpp \
  eth_client/libdevcrypto/CryptoPP.h \
  eth_client/libdevcrypto/Exceptions.h \
  eth_client/libdevcrypto/Hash.cpp \
  eth_client/libdevcrypto/Hash.h \
  eth_client/libdevcrypto/LibSnark.cpp \
  eth_client/libdevcrypto/LibSnark.h \
  eth_client/libethashseal/GenesisInfo.cpp \
  eth_client/libethashseal/GenesisInfo.h \
  eth_client/libethashseal/genesis/qtumNetwork.cpp \
  eth_client/libethcore/ABI.h \
  eth_client/libethcore/BlockHeader.cpp \
  eth_client/libethcore/BlockHeader.h \
  eth_client/libethcore/ChainOperationParams.cpp \
  eth_client/libethcore/ChainOperationParams.h \
  eth_client/libethcore/Common.cpp \
  eth_client/libethcore/Common.h \
  eth_client/libethcore/EVMSchedule.cpp \
  eth_client/libethcore/EVMSchedule.h \
  eth_client/libethcore/Exceptions.h \
  eth_client/libethcore/LogEntry.cpp \
  eth_client/libethcore/LogEntry.h \
  eth_client/libethcore/Precompiled.cpp \
  eth_client/libethcore/Precompiled.h \
  eth_client/libethcore/SealEngine.cpp \
  eth_client/libethcore/SealEngine.h \
  eth_client/libethcore/TransactionBase.cpp \
  eth_client/libethcore/TransactionBase.h \
  eth_client/libethereum/Account.cpp \
  eth_client/libethereum/Account.h \
  eth_client/libethereum/ChainParams.cpp \
  eth_client/libethereum/ChainParams.h \
  eth_client/libethereum/CodeSizeCache.h \
  eth_client/libethereum/DatabasePaths.cpp \
  eth_client/libethereum/DatabasePaths.h \
  eth_client/libethereum/Executive.cpp \
  eth_client/libethereum/Executive.h \
  eth_client/libethereum/ExtVM.cpp \
  eth_client/libethereum/ExtVM.h \
  eth_client/libethereum/LastBlockHashesFace.h \
  eth_client/libethereum/SecureTrieDB.h \
  eth_client/libethereum/State.cpp \
  eth_client/libethereum/State.h \
  eth_client/libethereum/Transaction.cpp \
  eth_client/libethereum/Transaction.h \
  eth_client/libethereum/TransactionReceipt.cpp \
  eth_client/libethereum/TransactionReceipt.h \
  eth_client/libethereum/ValidationSchemes.cpp \
  eth_client/libethereum/ValidationSchemes.h \
  eth_client/libevm/EVMC.cpp \
  eth_client/libevm/EVMC.h \
  eth_client/libevm/ExtVMFace.cpp \
  eth_client/libevm/ExtVMFace.h \
  eth_client/libevm/VMFace.h \
  eth_client/libevm/VMFactory.cpp \
  eth_client/libevm/VMFactory.h \
  eth_client/utils/ethash/include/ethash/ethash.h \
  eth_client/utils/ethash/include/ethash/ethash.hpp \
  eth_client/utils/ethash/include/ethash/hash_types.h \
  eth_client/utils/ethash/include/ethash/hash_types.hpp \
  eth_client/utils/ethash/include/ethash/keccak.h \
  eth_client/utils/ethash/include/ethash/keccak.hpp \
  eth_client/utils/ethash/include/ethash/progpow.hpp \
  eth_client/utils/ethash/lib/ethash/bit_manipulation.h \
  eth_client/utils/ethash/lib/ethash/builtins.h \
  eth_client/utils/ethash/lib/ethash/endianness.hpp \
  eth_client/utils/ethash/lib/ethash/ethash-internal.hpp \
  eth_client/utils/ethash/lib/ethash/ethash.cpp \
  eth_client/utils/ethash/lib/ethash/keccak.c \
  eth_client/utils/ethash/lib/ethash/keccakf1600.c \
  eth_client/utils/ethash/lib/ethash/keccakf800.c \
  eth_client/utils/ethash/lib/ethash/kiss99.hpp \
  eth_client/utils/ethash/lib/ethash/managed.cpp \
  eth_client/utils/ethash/lib/ethash/primes.c \
  eth_client/utils/ethash/lib/ethash/primes.h \
  eth_client/utils/ethash/lib/ethash/progpow.cpp \
  eth_client/utils/ethash/lib/ethash/support/attributes.h \
  eth_client/utils/intx/intx.hpp \
  eth_client/utils/json_spirit/JsonSpiritHeaders.h \
  eth_client/utils/json_spirit/json_spirit.h \
  eth_client/utils/json_spirit/json_spirit.vcproj \
  eth_client/utils/json_spirit/json_spirit_error_position.h \
  eth_client/utils/json_spirit/json_spirit_reader.cpp \
  eth_client/utils/json_spirit/json_spirit_reader.h \
  eth_client/utils/json_spirit/json_spirit_reader_template.h \
  eth_client/utils/json_spirit/json_spirit_stream_reader.h \
  eth_client/utils/json_spirit/json_spirit_utils.h \
  eth_client/utils/json_spirit/json_spirit_value.cpp \
  eth_client/utils/json_spirit/json_spirit_value.h \
  eth_client/utils/json_spirit/json_spirit_writer.cpp \
  eth_client/utils/json_spirit/json_spirit_writer.h \
  eth_client/utils/json_spirit/json_spirit_writer_template.h \
  eth_client/utils/libscrypt/b64.c \
  eth_client/utils/libscrypt/b64.h \
  eth_client/utils/libscrypt/crypto-mcf.c \
  eth_client/utils/libscrypt/crypto-scrypt-saltgen.c \
  eth_client/utils/libscrypt/crypto_scrypt-check.c \
  eth_client/utils/libscrypt/crypto_scrypt-hash.c \
  eth_client/utils/libscrypt/crypto_scrypt-hexconvert.c \
  eth_client/utils/libscrypt/crypto_scrypt-hexconvert.h \
  eth_client/utils/libscrypt/crypto_scrypt-nosse.c \
  eth_client/utils/libscrypt/libscrypt.h \
  eth_client/utils/libscrypt/sha256.c \
  eth_client/utils/libscrypt/sha256.h \
  eth_client/utils/libscrypt/slowequals.c \
  eth_client/utils/libscrypt/slowequals.h \
  eth_client/utils/libscrypt/sysendian.h \
  $(BITCOIN_CORE_H)

if USE_LIBEVENT
libbitnet_common_a_CPPFLAGS += $(EVENT_CFLAGS)
libbitnet_common_a_SOURCES += common/url.cpp
endif
#

# util #
libbitnet_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitnet_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  fs.cpp \
  logging.cpp \
  random.cpp \
  randomenv.cpp \
  support/cleanse.cpp \
  sync.cpp \
  util/asmap.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/check.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/sock.cpp \
  util/syserror.cpp \
  util/system.cpp \
  util/message.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/readwritefile.cpp \
  util/settings.cpp \
  util/thread.cpp \
  util/threadinterrupt.cpp \
  util/threadnames.cpp \
  util/serfloat.cpp \
  util/spanparsing.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/syscall_sandbox.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  $(BITCOIN_CORE_H)
#

# cli #
libbitnet_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitnet_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitnet_cli_a_SOURCES = \
  compat/stdin.h \
  compat/stdin.cpp \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libbitnet_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bitnetd & bitnet-node binaries #
bitnet_daemon_sources = bitnetd.cpp
bitnet_bin_cppflags = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitnet_bin_cxxflags = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitnet_bin_ldflags = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitnet_daemon_sources += bitnetd-res.rc
endif

bitnet_bin_ldadd = \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBCRYPTOPP) \
  $(LIBFF) \
  $(LIBSECP256K1)

bitnet_bin_ldadd += $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(SQLITE_LIBS)

bitnetd_SOURCES = $(bitnet_daemon_sources) init/bitnetd.cpp
bitnetd_CPPFLAGS = $(bitnet_bin_cppflags)
bitnetd_CXXFLAGS = $(bitnet_bin_cxxflags)
bitnetd_LDFLAGS = $(bitnet_bin_ldflags)
bitnetd_LDADD = $(LIBBITCOIN_NODE) $(bitnet_bin_ldadd)

bitnet_node_SOURCES = $(bitnet_daemon_sources) init/bitnet-node.cpp
bitnet_node_CPPFLAGS = $(bitnet_bin_cppflags)
bitnet_node_CXXFLAGS = $(bitnet_bin_cxxflags)
bitnet_node_LDFLAGS = $(bitnet_bin_ldflags)
bitnet_node_LDADD = $(LIBBITCOIN_NODE) $(bitnet_bin_ldadd) $(LIBBITCOIN_IPC) $(LIBMULTIPROCESS_LIBS)

# bitnet-cli binary #
bitnet_cli_SOURCES = bitnet-cli.cpp
bitnet_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
bitnet_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitnet_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitnet_cli_SOURCES += bitnet-cli-res.rc
endif

bitnet_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1) \
  $(LIBCRYPTOPP) 

bitnet_cli_LDADD += $(EVENT_LIBS)
#

# bitnet-tx binary #
bitnet_tx_SOURCES = bitnet-tx.cpp
bitnet_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitnet_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitnet_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitnet_tx_SOURCES += bitnet-tx-res.rc
endif

bitnet_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1) \
  $(LIBCRYPTOPP) 

#

# bitnet-wallet binary #
bitnet_wallet_SOURCES = bitnet-wallet.cpp
bitnet_wallet_SOURCES += init/bitnet-wallet.cpp
bitnet_wallet_CPPFLAGS = $(bitnet_bin_cppflags)
bitnet_wallet_CXXFLAGS = $(bitnet_bin_cxxflags)
bitnet_wallet_LDFLAGS = $(bitnet_bin_ldflags)
bitnet_wallet_LDADD = \
  $(LIBBITCOIN_WALLET_TOOL) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1) \
  $(BDB_LIBS) \
  $(SQLITE_LIBS)

if TARGET_WINDOWS
bitnet_wallet_SOURCES += bitnet-wallet-res.rc
endif
#

# bitnet-util binary #
bitnet_util_SOURCES = bitnet-util.cpp
bitnet_util_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitnet_util_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitnet_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bitnet_util_SOURCES += bitnet-util-res.rc
endif

bitnet_util_LDADD = \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1)
#

# bitnet-chainstate binary #
bitnet_chainstate_SOURCES = bitnet-chainstate.cpp
bitnet_chainstate_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(BOOST_CPPFLAGS)
bitnet_chainstate_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

bitnet_chainstate_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(PTHREAD_FLAGS) $(LIBTOOL_APP_LDFLAGS) -static
bitnet_chainstate_LDADD = $(LIBBITCOINKERNEL)

# libtool is unable to calculate this indirect dependency, presumably because it's a subproject.
# libsecp256k1 only needs to be linked in when libbitnetkernel is static.
bitnet_chainstate_LDADD += $(LIBSECP256K1)
#

# bitnetkernel library #
if BUILD_BITCOIN_KERNEL_LIB
lib_LTLIBRARIES += $(LIBBITCOINKERNEL)

libbitnetkernel_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS) $(PTHREAD_FLAGS)
libbitnetkernel_la_LIBADD = $(LIBBITCOIN_CRYPTO) $(LIBUNIVALUE) $(LIBLEVELDB) $(LIBMEMENV) $(LIBSECP256K1)
libbitnetkernel_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) -I$(srcdir)/$(UNIVALUE_INCLUDE_DIR_INT)

# libbitnetkernel requires default symbol visibility, explicitly specify that
# here so that things still work even when user configures with
#   --enable-reduce-exports
#
# Note this is a quick hack that will be removed as we incrementally define what
# to export from the library.
libbitnetkernel_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -fvisibility=default

# TODO: libbitnetkernel is a work in progress consensus engine library, as more
#       and more modules are decoupled from the consensus engine, this list will
#       shrink to only those which are absolutely necessary.
libbitnetkernel_la_SOURCES = \
  kernel/bitnetkernel.cpp \
  arith_uint256.cpp \
  chain.cpp \
  chainparamsbase.cpp \
  chainparams.cpp \
  clientversion.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  consensus/tx_check.cpp \
  consensus/tx_verify.cpp \
  core_read.cpp \
  dbwrapper.cpp \
  deploymentinfo.cpp \
  deploymentstatus.cpp \
  flatfile.cpp \
  fs.cpp \
  hash.cpp \
  kernel/chain.cpp \
  kernel/checks.cpp \
  kernel/coinstats.cpp \
  kernel/context.cpp \
  kernel/cs_main.cpp \
  kernel/mempool_persist.cpp \
  key.cpp \
  logging.cpp \
  node/blockstorage.cpp \
  node/chainstate.cpp \
  node/interface_ui.cpp \
  node/utxo_snapshot.cpp \
  policy/feerate.cpp \
  policy/fees.cpp \
  policy/packages.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  random.cpp \
  randomenv.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sigcache.cpp \
  script/standard.cpp \
  shutdown.cpp \
  signet.cpp \
  support/cleanse.cpp \
  support/lockedpool.cpp \
  sync.cpp \
  txdb.cpp \
  txmempool.cpp \
  uint256.cpp \
  util/check.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/serfloat.cpp \
  util/settings.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/syscall_sandbox.cpp \
  util/syserror.cpp \
  util/system.cpp \
  util/thread.cpp \
  util/threadnames.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  warnings.cpp

# Required for obj/build.h to be generated first.
# More details: https://www.gnu.org/software/automake/manual/html_node/Built-Sources-Example.html
libbitnetkernel_la-clientversion.l$(OBJEXT): obj/build.h
endif # BUILD_BITCOIN_KERNEL_LIB
#

# bitnetconsensus library #
if BUILD_BITCOIN_LIBS
lib_LTLIBRARIES += $(LIBBITCOINCONSENSUS)

include_HEADERS = script/bitnetconsensus.h
libbitnetconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libbitnet_crypto_base_la_SOURCES) $(libbitnet_consensus_a_SOURCES)

libbitnetconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libbitnetconsensus_la_LIBADD = $(LIBSECP256K1)
libbitnetconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libbitnetconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += index/*.gcda index/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += node/*.gcda node/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/bitnet-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/bitnet-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/bitnet-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/bitnet-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
	@echo "Running symbol and dynamic library checks..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

libbitnet_ipc_mpgen_input = \
  ipc/capnp/echo.capnp \
  ipc/capnp/init.capnp
EXTRA_DIST += $(libbitnet_ipc_mpgen_input)
%.capnp:

# Explicitly list dependencies on generated headers as described in
# https://www.gnu.org/software/automake/manual/html_node/Built-Sources-Example.html#Recording-Dependencies-manually
ipc/capnp/libbitnet_ipc_a-protocol.$(OBJEXT): $(libbitnet_ipc_mpgen_input:=.h)

if BUILD_MULTIPROCESS
LIBBITCOIN_IPC=libbitnet_ipc.a
libbitnet_ipc_a_SOURCES = \
  ipc/capnp/context.h \
  ipc/capnp/init-types.h \
  ipc/capnp/protocol.cpp \
  ipc/capnp/protocol.h \
  ipc/context.h \
  ipc/exception.h \
  ipc/interfaces.cpp \
  ipc/process.cpp \
  ipc/process.h \
  ipc/protocol.h
libbitnet_ipc_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitnet_ipc_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(LIBMULTIPROCESS_CFLAGS)

include $(MPGEN_PREFIX)/include/mpgen.mk
libbitnet_ipc_mpgen_output = \
  $(libbitnet_ipc_mpgen_input:=.c++) \
  $(libbitnet_ipc_mpgen_input:=.h) \
  $(libbitnet_ipc_mpgen_input:=.proxy-client.c++) \
  $(libbitnet_ipc_mpgen_input:=.proxy-server.c++) \
  $(libbitnet_ipc_mpgen_input:=.proxy-types.c++) \
  $(libbitnet_ipc_mpgen_input:=.proxy-types.h) \
  $(libbitnet_ipc_mpgen_input:=.proxy.h)
nodist_libbitnet_ipc_a_SOURCES = $(libbitnet_ipc_mpgen_output)
CLEANFILES += $(libbitnet_ipc_mpgen_output)
endif

%.raw.h: %.raw
	@$(MKDIR_P) $(@D)
	@{ \
	 echo "static unsigned const char $(*F)_raw[] = {" && \
	 $(HEXDUMP) -v -e '8/1 "0x%02x, "' -e '"\n"' $< | $(SED) -e 's/0x  ,//g' && \
	 echo "};"; \
	} > "$@.new" && mv -f "$@.new" "$@"
	@echo "Generated $@"

include Makefile.minisketch.include

include Makefile.crc32c.include
include Makefile.leveldb.include

include Makefile.cryptopp.include
include Makefile.libff.include
include Makefile.test_util.include
include Makefile.test_fuzz.include


include Makefile.test.include

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif

include Makefile.univalue.include
