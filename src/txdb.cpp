// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <txdb.h>

#include <chain.h>
#include <pow.h>
#include <random.h>
#include <shutdown.h>
#include <uint256.h>
#include <util/system.h>
#include <util/translation.h>
#include <util/vector.h>
#include <validation.h>
#include <chainparams.h>

#include <stdint.h>

static constexpr uint8_t DB_COIN{'C'};
static constexpr uint8_t DB_BLOCK_FILES{'f'};
static constexpr uint8_t DB_BLOCK_INDEX{'b'};

////////////////////////////////////////// // qtum
static constexpr uint8_t DB_HEIGHTINDEX{'h'};
static constexpr uint8_t DB_STAKEINDEX{'s'};
static constexpr uint8_t DB_DELEGATEINDEX{'d'};
//////////////////////////////////////////

static constexpr uint8_t DB_BEST_BLOCK{'B'};
static constexpr uint8_t DB_HEAD_BLOCKS{'H'};
static constexpr uint8_t DB_FLAG{'F'};
static constexpr uint8_t DB_REINDEX_FLAG{'R'};
static constexpr uint8_t DB_LAST_BLOCK{'l'};

////////////////////////////////////////// // qtum
static constexpr uint8_t DB_ADDRESSINDEX{'a'};
static constexpr uint8_t DB_ADDRESSUNSPENTINDEX{'u'};
static constexpr uint8_t DB_TIMESTAMPINDEX{'S'};
static constexpr uint8_t DB_BLOCKHASHINDEX{'z'};
static constexpr uint8_t DB_SPENTINDEX{'p'};
//////////////////////////////////////////

// Keys used in previous version that might still be found in the DB:
static constexpr uint8_t DB_COINS{'c'};
static constexpr uint8_t DB_TXINDEX_BLOCK{'T'};
//               uint8_t DB_TXINDEX{'t'}

std::optional<bilingual_str> CheckLegacyTxindex(CBlockTreeDB& block_tree_db)
{
    CBlockLocator ignored{};
    if (block_tree_db.Read(DB_TXINDEX_BLOCK, ignored)) {
        return _("The -txindex upgrade started by a previous version cannot be completed. Restart with the previous version or run a full -reindex.");
    }
    bool txindex_legacy_flag{false};
    block_tree_db.ReadFlag("txindex", txindex_legacy_flag);
    if (txindex_legacy_flag) {
        // Disable legacy txindex and warn once about occupied disk space
        if (!block_tree_db.WriteFlag("txindex", false)) {
            return Untranslated("Failed to write block index db flag 'txindex'='0'");
        }
        return _("The block index db contains a legacy 'txindex'. To clear the occupied disk space, run a full -reindex, otherwise ignore this error. This error message will not be displayed again.");
    }
    return std::nullopt;
}

bool CCoinsViewDB::NeedsUpgrade()
{
    std::unique_ptr<CDBIterator> cursor{m_db->NewIterator()};
    // DB_COINS was deprecated in v0.15.0, commit
    // 1088b02f0ccd7358d2b7076bb9e122d59d502d02
    cursor->Seek(std::make_pair(DB_COINS, uint256{}));
    return cursor->Valid();
}

namespace {

struct CoinEntry {
    COutPoint* outpoint;
    uint8_t key;
    explicit CoinEntry(const COutPoint* ptr) : outpoint(const_cast<COutPoint*>(ptr)), key(DB_COIN)  {}

    SERIALIZE_METHODS(CoinEntry, obj) { READWRITE(obj.key, obj.outpoint->hash, VARINT(obj.outpoint->n)); }
};

struct DelegateEntry {
    uint160 address;
    uint8_t fee;
    DelegateEntry(uint160 _address = uint160(), uint8_t _fee = 0) :
        address(_address), fee(_fee)
    {}

    template<typename Stream>
    void Serialize(Stream &s) const {
        s << address;
        s << fee;
    }

    template<typename Stream>
    void Unserialize(Stream& s) {
        s >> address;
        s >> fee;
    }
};

} // namespace

CCoinsViewDB::CCoinsViewDB(fs::path ldb_path, size_t nCacheSize, bool fMemory, bool fWipe) :
    m_db(std::make_unique<CDBWrapper>(ldb_path, nCacheSize, fMemory, fWipe, true)),
    m_ldb_path(ldb_path),
    m_is_memory(fMemory) { }

void CCoinsViewDB::ResizeCache(size_t new_cache_size)
{
    // We can't do this operation with an in-memory DB since we'll lose all the coins upon
    // reset.
    if (!m_is_memory) {
        // Have to do a reset first to get the original `m_db` state to release its
        // filesystem lock.
        m_db.reset();
        m_db = std::make_unique<CDBWrapper>(
            m_ldb_path, new_cache_size, m_is_memory, /*fWipe=*/false, /*obfuscate=*/true);
    }
}

bool CCoinsViewDB::GetCoin(const COutPoint &outpoint, Coin &coin) const {
    return m_db->Read(CoinEntry(&outpoint), coin);
}

bool CCoinsViewDB::HaveCoin(const COutPoint &outpoint) const {
    return m_db->Exists(CoinEntry(&outpoint));
}

uint256 CCoinsViewDB::GetBestBlock() const {
    uint256 hashBestChain;
    if (!m_db->Read(DB_BEST_BLOCK, hashBestChain))
        return uint256();
    return hashBestChain;
}

std::vector<uint256> CCoinsViewDB::GetHeadBlocks() const {
    std::vector<uint256> vhashHeadBlocks;
    if (!m_db->Read(DB_HEAD_BLOCKS, vhashHeadBlocks)) {
        return std::vector<uint256>();
    }
    return vhashHeadBlocks;
}

bool CCoinsViewDB::BatchWrite(CCoinsMap &mapCoins, const uint256 &hashBlock) {
    CDBBatch batch(*m_db);
    size_t count = 0;
    size_t changed = 0;
    size_t batch_size = (size_t)gArgs.GetIntArg("-dbbatchsize", nDefaultDbBatchSize);
    int crash_simulate = gArgs.GetIntArg("-dbcrashratio", 0);
    assert(!hashBlock.IsNull());

    uint256 old_tip = GetBestBlock();
    if (old_tip.IsNull()) {
        // We may be in the middle of replaying.
        std::vector<uint256> old_heads = GetHeadBlocks();
        if (old_heads.size() == 2) {
            assert(old_heads[0] == hashBlock);
            old_tip = old_heads[1];
        }
    }

    // In the first batch, mark the database as being in the middle of a
    // transition from old_tip to hashBlock.
    // A vector is used for future extensibility, as we may want to support
    // interrupting after partial writes from multiple independent reorgs.
    batch.Erase(DB_BEST_BLOCK);
    batch.Write(DB_HEAD_BLOCKS, Vector(hashBlock, old_tip));

    for (CCoinsMap::iterator it = mapCoins.begin(); it != mapCoins.end();) {
        if (it->second.flags & CCoinsCacheEntry::DIRTY) {
            CoinEntry entry(&it->first);
            if (it->second.coin.IsSpent())
                batch.Erase(entry);
            else
                batch.Write(entry, it->second.coin);
            changed++;
        }
        count++;
        CCoinsMap::iterator itOld = it++;
        mapCoins.erase(itOld);
        if (batch.SizeEstimate() > batch_size) {
            LogPrint(BCLog::COINDB, "Writing partial batch of %.2f MiB\n", batch.SizeEstimate() * (1.0 / 1048576.0));
            m_db->WriteBatch(batch);
            batch.Clear();
            if (crash_simulate) {
                static FastRandomContext rng;
                if (rng.randrange(crash_simulate) == 0) {
                    LogPrintf("Simulating a crash. Goodbye.\n");
                    _Exit(0);
                }
            }
        }
    }

    // In the last batch, mark the database as consistent with hashBlock again.
    batch.Erase(DB_HEAD_BLOCKS);
    batch.Write(DB_BEST_BLOCK, hashBlock);

    LogPrint(BCLog::COINDB, "Writing final batch of %.2f MiB\n", batch.SizeEstimate() * (1.0 / 1048576.0));
    bool ret = m_db->WriteBatch(batch);
    LogPrint(BCLog::COINDB, "Committed %u changed transaction outputs (out of %u) to coin database...\n", (unsigned int)changed, (unsigned int)count);
    return ret;
}

size_t CCoinsViewDB::EstimateSize() const
{
    return m_db->EstimateSize(DB_COIN, uint8_t(DB_COIN + 1));
}

CBlockTreeDB::CBlockTreeDB(size_t nCacheSize, bool fMemory, bool fWipe) : CDBWrapper(gArgs.GetDataDirNet() / "blocks" / "index", nCacheSize, fMemory, fWipe) {
}

bool CBlockTreeDB::ReadBlockFileInfo(int nFile, CBlockFileInfo &info) {
    return Read(std::make_pair(DB_BLOCK_FILES, nFile), info);
}

bool CBlockTreeDB::WriteReindexing(bool fReindexing) {
    if (fReindexing)
        return Write(DB_REINDEX_FLAG, uint8_t{'1'});
    else
        return Erase(DB_REINDEX_FLAG);
}

void CBlockTreeDB::ReadReindexing(bool &fReindexing) {
    fReindexing = Exists(DB_REINDEX_FLAG);
}

bool CBlockTreeDB::ReadLastBlockFile(int &nFile) {
    return Read(DB_LAST_BLOCK, nFile);
}

/** Specialization of CCoinsViewCursor to iterate over a CCoinsViewDB */
class CCoinsViewDBCursor: public CCoinsViewCursor
{
public:
    // Prefer using CCoinsViewDB::Cursor() since we want to perform some
    // cache warmup on instantiation.
    CCoinsViewDBCursor(CDBIterator* pcursorIn, const uint256&hashBlockIn):
        CCoinsViewCursor(hashBlockIn), pcursor(pcursorIn) {}
    ~CCoinsViewDBCursor() = default;

    bool GetKey(COutPoint &key) const override;
    bool GetValue(Coin &coin) const override;

    bool Valid() const override;
    void Next() override;

private:
    std::unique_ptr<CDBIterator> pcursor;
    std::pair<char, COutPoint> keyTmp;

    friend class CCoinsViewDB;
};

std::unique_ptr<CCoinsViewCursor> CCoinsViewDB::Cursor() const
{
    auto i = std::make_unique<CCoinsViewDBCursor>(
        const_cast<CDBWrapper&>(*m_db).NewIterator(), GetBestBlock());
    /* It seems that there are no "const iterators" for LevelDB.  Since we
       only need read operations on it, use a const-cast to get around
       that restriction.  */
    i->pcursor->Seek(DB_COIN);
    // Cache key of first record
    if (i->pcursor->Valid()) {
        CoinEntry entry(&i->keyTmp.second);
        i->pcursor->GetKey(entry);
        i->keyTmp.first = entry.key;
    } else {
        i->keyTmp.first = 0; // Make sure Valid() and GetKey() return false
    }
    return i;
}

bool CCoinsViewDBCursor::GetKey(COutPoint &key) const
{
    // Return cached key
    if (keyTmp.first == DB_COIN) {
        key = keyTmp.second;
        return true;
    }
    return false;
}

bool CCoinsViewDBCursor::GetValue(Coin &coin) const
{
    return pcursor->GetValue(coin);
}

bool CCoinsViewDBCursor::Valid() const
{
    return keyTmp.first == DB_COIN;
}

void CCoinsViewDBCursor::Next()
{
    pcursor->Next();
    CoinEntry entry(&keyTmp.second);
    if (!pcursor->Valid() || !pcursor->GetKey(entry)) {
        keyTmp.first = 0; // Invalidate cached key after last record so that Valid() and GetKey() return false
    } else {
        keyTmp.first = entry.key;
    }
}

bool CBlockTreeDB::WriteBatchSync(const std::vector<std::pair<int, const CBlockFileInfo*> >& fileInfo, int nLastFile, const std::vector<const CBlockIndex*>& blockinfo) {
    CDBBatch batch(*this);
    for (std::vector<std::pair<int, const CBlockFileInfo*> >::const_iterator it=fileInfo.begin(); it != fileInfo.end(); it++) {
        batch.Write(std::make_pair(DB_BLOCK_FILES, it->first), *it->second);
    }
    batch.Write(DB_LAST_BLOCK, nLastFile);
    for (std::vector<const CBlockIndex*>::const_iterator it=blockinfo.begin(); it != blockinfo.end(); it++) {
        batch.Write(std::make_pair(DB_BLOCK_INDEX, (*it)->GetBlockHash()), CDiskBlockIndex(*it));
    }
    return WriteBatch(batch, true);
}

bool CBlockTreeDB::WriteFlag(const std::string &name, bool fValue) {
    return Write(std::make_pair(DB_FLAG, name), fValue ? uint8_t{'1'} : uint8_t{'0'});
}

bool CBlockTreeDB::ReadFlag(const std::string &name, bool &fValue) {
    uint8_t ch;
    if (!Read(std::make_pair(DB_FLAG, name), ch))
        return false;
    fValue = ch == uint8_t{'1'};
    return true;
}

/////////////////////////////////////////////////////// // qtum
bool CBlockTreeDB::WriteHeightIndex(const CHeightTxIndexKey &heightIndex, const std::vector<uint256>& hash) {
    CDBBatch batch(*this);
    batch.Write(std::make_pair(DB_HEIGHTINDEX, heightIndex), hash);
    return WriteBatch(batch);
}

int CBlockTreeDB::ReadHeightIndex(int low, int high, int minconf,
        std::vector<std::vector<uint256>> &blocksOfHashes,
        std::set<dev::h160> const &addresses, ChainstateManager &chainman) {

    if ((high < low && high > -1) || (high == 0 && low == 0) || (high < -1 || low < 0)) {
       return -1;
    }

    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    pcursor->Seek(std::make_pair(DB_HEIGHTINDEX, CHeightTxIndexIteratorKey(low)));

    int curheight = 0;

    for (size_t count = 0; pcursor->Valid(); pcursor->Next()) {

        std::pair<uint8_t, CHeightTxIndexKey> key;
        if (!pcursor->GetKey(key) || key.first != DB_HEIGHTINDEX) {
            break;
        }

        int nextHeight = key.second.height;

        if (high > -1 && nextHeight > high) {
            break;
        }

        if (minconf > 0) {
            int conf = chainman.ActiveChain().Height() - nextHeight;
            if (conf < minconf) {
                break;
            }
        }

        curheight = nextHeight;

        auto address = key.second.address;
        if (!addresses.empty() && addresses.find(address) == addresses.end()) {
            continue;
        }

        std::vector<uint256> hashesTx;

        if (!pcursor->GetValue(hashesTx)) {
            break;
        }

        count += hashesTx.size();

        blocksOfHashes.push_back(hashesTx);
    }

    return curheight;
}

bool CBlockTreeDB::EraseHeightIndex(const unsigned int &height) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    CDBBatch batch(*this);

    pcursor->Seek(std::make_pair(DB_HEIGHTINDEX, CHeightTxIndexIteratorKey(height)));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_HEIGHTINDEX && key.second.height == height) {
            batch.Erase(key);
            pcursor->Next();
        } else {
            break;
        }
    }

    return WriteBatch(batch);
}

bool CBlockTreeDB::WipeHeightIndex() {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    CDBBatch batch(*this);

    pcursor->Seek(DB_HEIGHTINDEX);

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_HEIGHTINDEX) {
            batch.Erase(key);
            pcursor->Next();
        } else {
            break;
        }
    }

    return WriteBatch(batch);
}


bool CBlockTreeDB::WriteStakeIndex(unsigned int height, uint160 address) {
    CDBBatch batch(*this);
    batch.Write(std::make_pair(DB_STAKEINDEX, height), address);
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadStakeIndex(unsigned int height, uint160& address){
    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    pcursor->Seek(std::make_pair(DB_STAKEINDEX, height));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        pcursor->GetKey(key); //note: it's apparently ok if this returns an error https://github.com/bitcoin/bitcoin/issues/7890
        if (key.first == DB_STAKEINDEX) {
            pcursor->GetValue(address);
            return true;
        }else{
            return false;
        }
    }
    return false;
}
bool CBlockTreeDB::ReadStakeIndex(unsigned int high, unsigned int low, std::vector<uint160> addresses){
    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    pcursor->Seek(std::make_pair(DB_STAKEINDEX, low));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        pcursor->GetKey(key); //note: it's apparently ok if this returns an error https://github.com/bitcoin/bitcoin/issues/7890
        if (key.first == DB_STAKEINDEX && key.second.height < high) {
            uint160 value;
            pcursor->GetValue(value);
            addresses.push_back(value);
            pcursor->Next();
        } else {
            break;
        }
    }

    return true;
}

bool CBlockTreeDB::EraseStakeIndex(unsigned int height) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    CDBBatch batch(*this);

    pcursor->Seek(std::make_pair(DB_STAKEINDEX, height));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_HEIGHTINDEX && key.second.height == height) {
            batch.Erase(key);
            pcursor->Next();
        } else {
            break;
        }
    }

    return WriteBatch(batch);
}

bool CBlockTreeDB::WriteDelegateIndex(unsigned int height, uint160 address, uint8_t fee) {
    CDBBatch batch(*this);
    batch.Write(std::make_pair(DB_DELEGATEINDEX, height), DelegateEntry(address, fee));
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadDelegateIndex(unsigned int height, uint160& address, uint8_t& fee){
    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    pcursor->Seek(std::make_pair(DB_DELEGATEINDEX, height));

    DelegateEntry info;
    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        pcursor->GetKey(key);
        if (key.first == DB_DELEGATEINDEX) {
            pcursor->GetValue(info);
            address = info.address;
            fee = info.fee;
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool CBlockTreeDB::EraseDelegateIndex(unsigned int height) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    CDBBatch batch(*this);

    pcursor->Seek(std::make_pair(DB_DELEGATEINDEX, height));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CHeightTxIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_HEIGHTINDEX && key.second.height == height) {
            batch.Erase(key);
            pcursor->Next();
        } else {
            break;
        }
    }

    return WriteBatch(batch);
}

bool CBlockTreeDB::WriteAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount > >&vect) {
    CDBBatch batch(*this);
    for (std::vector<std::pair<CAddressIndexKey, CAmount> >::const_iterator it=vect.begin(); it!=vect.end(); it++)
        batch.Write(std::make_pair(DB_ADDRESSINDEX, it->first), it->second);
    return WriteBatch(batch);
}

bool CBlockTreeDB::EraseAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount > >&vect) {
    CDBBatch batch(*this);
    for (std::vector<std::pair<CAddressIndexKey, CAmount> >::const_iterator it=vect.begin(); it!=vect.end(); it++)
        batch.Erase(std::make_pair(DB_ADDRESSINDEX, it->first));
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadAddressIndex(uint256 addressHash, int type,
                                    std::vector<std::pair<CAddressIndexKey, CAmount> > &addressIndex,
                                    int start, int end) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    if (start > 0 && end > 0) {
        pcursor->Seek(std::make_pair(DB_ADDRESSINDEX, CAddressIndexIteratorHeightKey(type, addressHash, start)));
    } else {
        pcursor->Seek(std::make_pair(DB_ADDRESSINDEX, CAddressIndexIteratorKey(type, addressHash)));
    }

    while (pcursor->Valid()) {
        std::pair<uint8_t,CAddressIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_ADDRESSINDEX && key.second.hashBytes == addressHash) {
            if (end > 0 && key.second.blockHeight > end) {
                break;
            }
            CAmount nValue;
            if (pcursor->GetValue(nValue)) {
                addressIndex.push_back(std::make_pair(key.second, nValue));
                pcursor->Next();
            } else {
                return error("failed to get address index value");
            }
        } else {
            break;
        }
    }

    return true;
}

bool CBlockTreeDB::UpdateAddressUnspentIndex(const std::vector<std::pair<CAddressUnspentKey, CAddressUnspentValue > >&vect) {
    CDBBatch batch(*this);
    for (std::vector<std::pair<CAddressUnspentKey, CAddressUnspentValue> >::const_iterator it=vect.begin(); it!=vect.end(); it++) {
        if (it->second.IsNull()) {
            batch.Erase(std::make_pair(DB_ADDRESSUNSPENTINDEX, it->first));
        } else {
            batch.Write(std::make_pair(DB_ADDRESSUNSPENTINDEX, it->first), it->second);
        }
    }
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadAddressUnspentIndex(uint256 addressHash, int type,
                                           std::vector<std::pair<CAddressUnspentKey, CAddressUnspentValue> > &unspentOutputs) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    pcursor->Seek(std::make_pair(DB_ADDRESSUNSPENTINDEX, CAddressIndexIteratorKey(type, addressHash)));

    while (pcursor->Valid()) {
        std::pair<uint8_t,CAddressUnspentKey> key;
        if (pcursor->GetKey(key) && key.first == DB_ADDRESSUNSPENTINDEX && key.second.hashBytes == addressHash) {
            CAddressUnspentValue nValue;
            if (pcursor->GetValue(nValue)) {
                unspentOutputs.push_back(std::make_pair(key.second, nValue));
                pcursor->Next();
            } else {
                return error("failed to get address unspent value");
            }
        } else {
            break;
        }
    }

    return true;
}

bool CBlockTreeDB::WriteTimestampIndex(const CTimestampIndexKey &timestampIndex) {
    CDBBatch batch(*this);
    batch.Write(std::make_pair(DB_TIMESTAMPINDEX, timestampIndex), 0);
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadTimestampIndex(const unsigned int &high, const unsigned int &low, const bool fActiveOnly, std::vector<std::pair<uint256, unsigned int> > &hashes, ChainstateManager &chainman) {

    std::unique_ptr<CDBIterator> pcursor(NewIterator());

    pcursor->Seek(std::make_pair(DB_TIMESTAMPINDEX, CTimestampIndexIteratorKey(low)));

    while (pcursor->Valid()) {
        std::pair<uint8_t, CTimestampIndexKey> key;
        if (pcursor->GetKey(key) && key.first == DB_TIMESTAMPINDEX && key.second.timestamp < high) {
            if (fActiveOnly) {
                if (blockOnchainActive(key.second.blockHash, chainman)) {
                    hashes.push_back(std::make_pair(key.second.blockHash, key.second.timestamp));
                }
            } else {
                hashes.push_back(std::make_pair(key.second.blockHash, key.second.timestamp));
            }

            pcursor->Next();
        } else {
            break;
        }
    }

    return true;
}

bool CBlockTreeDB::WriteTimestampBlockIndex(const CTimestampBlockIndexKey &blockhashIndex, const CTimestampBlockIndexValue &logicalts) {
    CDBBatch batch(*this);
    batch.Write(std::make_pair(DB_BLOCKHASHINDEX, blockhashIndex), logicalts);
    return WriteBatch(batch);
}

bool CBlockTreeDB::ReadTimestampBlockIndex(const uint256 &hash, unsigned int &ltimestamp) {

    CTimestampBlockIndexValue lts;
    if (!Read(std::make_pair(DB_BLOCKHASHINDEX, hash), lts))
       return false;

    ltimestamp = lts.ltimestamp;
    return true;
}

bool CBlockTreeDB::ReadSpentIndex(CSpentIndexKey &key, CSpentIndexValue &value) {
    return Read(std::make_pair(DB_SPENTINDEX, key), value);
}

bool CBlockTreeDB::UpdateSpentIndex(const std::vector<std::pair<CSpentIndexKey, CSpentIndexValue> >&vect) {
    CDBBatch batch(*this);
    for (std::vector<std::pair<CSpentIndexKey,CSpentIndexValue> >::const_iterator it=vect.begin(); it!=vect.end(); it++) {
        if (it->second.IsNull()) {
            batch.Erase(std::make_pair(DB_SPENTINDEX, it->first));
        } else {
            batch.Write(std::make_pair(DB_SPENTINDEX, it->first), it->second);
        }
    }
    return WriteBatch(batch);
}

bool CBlockTreeDB::blockOnchainActive(const uint256 &hash, ChainstateManager &chainman) {
    LOCK(cs_main);
    node::BlockMap::iterator mi = chainman.BlockIndex().find(hash);
    if (mi == chainman.BlockIndex().end())
        return false;

    CBlockIndex* pblockindex = &(*mi).second;
    return pblockindex && chainman.ActiveChain().Contains(pblockindex);
}
///////////////////////////////////////////////////////

bool CBlockTreeDB::LoadBlockIndexGuts(const Consensus::Params& consensusParams, std::function<CBlockIndex*(const uint256&)> insertBlockIndex)
{
    AssertLockHeld(::cs_main);
    std::unique_ptr<CDBIterator> pcursor(NewIterator());
    pcursor->Seek(std::make_pair(DB_BLOCK_INDEX, uint256()));

    // Load m_block_index
    while (pcursor->Valid()) {
        if (ShutdownRequested()) return false;
        std::pair<uint8_t, uint256> key;
        if (pcursor->GetKey(key) && key.first == DB_BLOCK_INDEX) {
            CDiskBlockIndex diskindex;
            if (pcursor->GetValue(diskindex)) {
                // Construct block index object
                CBlockIndex* pindexNew = insertBlockIndex(diskindex.ConstructBlockHash());
                pindexNew->pprev          = insertBlockIndex(diskindex.hashPrev);
                pindexNew->nHeight        = diskindex.nHeight;
                pindexNew->nFile          = diskindex.nFile;
                pindexNew->nDataPos       = diskindex.nDataPos;
                pindexNew->nUndoPos       = diskindex.nUndoPos;
                pindexNew->nVersion       = diskindex.nVersion;
                pindexNew->hashMerkleRoot = diskindex.hashMerkleRoot;
                pindexNew->nTime          = diskindex.nTime;
                pindexNew->nBits          = diskindex.nBits;
                pindexNew->nNonce         = diskindex.nNonce;
                pindexNew->nMoneySupply   = diskindex.nMoneySupply;
                pindexNew->nStatus        = diskindex.nStatus;
                pindexNew->nTx            = diskindex.nTx;
                pindexNew->hashStateRoot  = diskindex.hashStateRoot; // qtum
                pindexNew->hashUTXORoot   = diskindex.hashUTXORoot; // qtum
                pindexNew->nStakeModifier = diskindex.nStakeModifier;
                pindexNew->prevoutStake   = diskindex.prevoutStake;
                pindexNew->vchBlockSigDlgt    = diskindex.vchBlockSigDlgt; // qtum

                if (!CheckIndexProof(*pindexNew, consensusParams)) {
//                    return error("%s: CheckIndexProof failed: %s", __func__, pindexNew->ToString());
                }

                // NovaCoin: build setStakeSeen
                if (pindexNew->IsProofOfStake())
                    setStakeSeen.insert(std::make_pair(pindexNew->prevoutStake, pindexNew->nTime));
                pcursor->Next();
            } else {
                return error("%s: failed to read value", __func__);
            }
        } else {
            break;
        }
    }

    return true;
}

bool CBlockTreeDB::EraseBlockIndex(const std::vector<uint256> &vect)
{
    CDBBatch batch(*this);
    for (std::vector<uint256>::const_iterator it=vect.begin(); it!=vect.end(); it++)
        batch.Erase(std::make_pair(DB_BLOCK_INDEX, *it));
    return WriteBatch(batch);
}
