# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitnet_cli*         | RPC client functionality used by *bitnet-cli* executable |
| *libbitnet_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitnet_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitnet_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitnet_node* and *libbitnet_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitnetconsensus*    | Shared library build of static *libbitnet_consensus* library |
| *libbitnet_kernel*      | Consensus engine and support library used for validation by *libbitnet_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitnetqt*           | GUI functionality used by *bitnet-qt* and *bitnet-gui* executables |
| *libbitnet_ipc*         | IPC functionality used by *bitnet-node*, *bitnet-wallet*, *bitnet-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitnet_node*        | P2P and RPC server functionality used by *bitnetd* and *bitnet-qt* executables. |
| *libbitnet_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitnet_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitnet_wallet*      | Wallet functionality used by *bitnetd* and *bitnet-wallet* executables. |
| *libbitnet_wallet_tool* | Lower-level wallet functionality used by *bitnet-wallet* executable. |
| *libbitnet_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitnetd* and *bitnet-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitnet_consensus* and *libbitnet_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitnet_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitnet_node* code lives in `src/node/` in the `node::` namespace
  - *libbitnet_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitnet_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitnet_util* code lives in `src/util/` in the `util::` namespace
  - *libbitnet_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitnet-cli[bitnet-cli]-->libbitnet_cli;

bitnetd[bitnetd]-->libbitnet_node;
bitnetd[bitnetd]-->libbitnet_wallet;

bitnet-qt[bitnet-qt]-->libbitnet_node;
bitnet-qt[bitnet-qt]-->libbitnetqt;
bitnet-qt[bitnet-qt]-->libbitnet_wallet;

bitnet-wallet[bitnet-wallet]-->libbitnet_wallet;
bitnet-wallet[bitnet-wallet]-->libbitnet_wallet_tool;

libbitnet_cli-->libbitnet_util;
libbitnet_cli-->libbitnet_common;

libbitnet_common-->libbitnet_consensus;
libbitnet_common-->libbitnet_util;

libbitnet_kernel-->libbitnet_consensus;
libbitnet_kernel-->libbitnet_util;

libbitnet_node-->libbitnet_consensus;
libbitnet_node-->libbitnet_kernel;
libbitnet_node-->libbitnet_common;
libbitnet_node-->libbitnet_util;

libbitnetqt-->libbitnet_common;
libbitnetqt-->libbitnet_util;

libbitnet_wallet-->libbitnet_common;
libbitnet_wallet-->libbitnet_util;

libbitnet_wallet_tool-->libbitnet_wallet;
libbitnet_wallet_tool-->libbitnet_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitnet-qt,bitnetd,bitnet-cli,bitnet-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitnet_wallet* and *libbitnet_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitnet_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitnet_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitnet_common* should serve a similar function as *libbitnet_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitnet_util* and *libbitnet_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitnet-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitnet_kernel* is not supposed to depend on *libbitnet_common*, only *libbitnet_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitnet_kernel* should only depend on *libbitnet_util* and *libbitnet_consensus*.

- The only thing that should depend on *libbitnet_kernel* internally should be *libbitnet_node*. GUI and wallet libraries *libbitnetqt* and *libbitnet_wallet* in particular should not depend on *libbitnet_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitnet_consensus*, *libbitnet_common*, and *libbitnet_util*, instead of *libbitnet_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitnetqt*, *libbitnet_node*, *libbitnet_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitnet_node* to *libbitnet_kernel* as part of [The libbitnetkernel Project #24303](https://github.com/bitnet/bitnet/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bitnet/bitnet/issues/15732)
