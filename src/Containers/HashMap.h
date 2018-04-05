#pragma once

#include "ToolsCore.h"
#include "MemoryAllocators/PoolAllocator.h"
#include "Utils/Hash.h"

namespace EngineTools {

#define HASH_MAP_SEED 2166136261
#define DEFAULT_BUCKETS 97

  template <typename Key, typename Value>
    struct HashEntry {
      Key mKey;
      Value mValue;
      HashEntry<Key, Value>* mNext { nullptr };
    };

  template <typename Key, typename Value, int BUCKETS = DEFAULT_BUCKETS>
    class HashMap {
      using HashEntryT = HashEntry<Key, Value>;
      public:
      HashMap();
      HashMap(PoolAllocator<HashEntryT>* alloc);
      ~HashMap();

      void Insert(Key key, Value value);
      bool Get(Key key, Value* value);
      bool Exists(Key key);

      private:
      U32 GenerateHash(int key);
      U32 GenerateHash(const char* key);

      HashEntryT* FindEntry(Key key);
      bool mIsCustomAllocator { false };
      UINT mBuckets { BUCKETS }; // Must be Prime
      UINT mPoolSize{ 128 };
      HashEntryT* mData[BUCKETS];
      PoolAllocator<HashEntryT>* pAllocator { nullptr };
      FNVHashOperator mHashOp;
    };

  template <typename Key, typename Value, int BUCKETS>
    HashMap<Key, Value, BUCKETS>::HashMap() : mHashOp(FNVHashOperator(HASH_MAP_SEED)) {
      pAllocator = new PoolAllocator<HashEntryT>(mPoolSize);
      for (int itr = 0; itr < BUCKETS; itr++) {
        mData[itr] = nullptr;
      }
    }

  template <typename Key, typename Value, int BUCKETS>
    HashMap<Key, Value, BUCKETS>::HashMap(PoolAllocator<HashEntryT>* alloc) :
      pAllocator(alloc),
      mIsCustomAllocator(true),
      mHashOp(FNVHashOperator(HASH_MAP_SEED)) {
        for (int itr = 0; itr < BUCKETS; itr++) {
          mData[itr] = nullptr;
        }
      }

  template <typename Key, typename Value, int BUCKETS>
    HashMap<Key, Value, BUCKETS>::~HashMap() {
      if (!mIsCustomAllocator) {
        delete pAllocator;
      }
    }

  template <typename Key, typename Value, int BUCKETS>
    bool HashMap<Key, Value, BUCKETS>::Get(Key key, Value* value) {
      HashEntryT* entry = FindEntry(key);
      bool result = false;

      if (entry != nullptr) {
        *value = entry->mValue;
        result = true;
      }

      return result;
    }

  // TODO: Need better template overloading for the Keys
  template <typename Key, typename Value, int BUCKETS>
    U32 HashMap<Key, Value, BUCKETS>::GenerateHash(int key) {
      return mHashOp.evaluate(key);
    }

  template <typename Key, typename Value, int BUCKETS>
    U32 HashMap<Key, Value, BUCKETS>::GenerateHash(const char* key) {
      return mHashOp.evaluate(key, strlen(key));
    }

  template <typename Key, typename Value, int BUCKETS>
    bool HashMap<Key, Value, BUCKETS>::Exists(Key key) {
      return FindEntry(key) != nullptr;
    }

  template <typename Key, typename Value, int BUCKETS>
    HashEntry<Key, Value>* HashMap<Key, Value, BUCKETS>::FindEntry(Key key) {
      U32 idx = GenerateHash(key);
      idx = idx % BUCKETS;

      HashEntryT* entry = mData[idx];

      while (entry != nullptr) {
        if (entry->mKey == key) {
          return entry;
        }

        entry = entry->mNext;
      }

      return nullptr;
    }

  template <typename Key, typename Value, int BUCKETS>
    void HashMap<Key, Value, BUCKETS>::Insert(Key key, Value value) {
      U32 idx = GenerateHash(key);
      idx = idx % BUCKETS;

      HashEntryT* prevEntry = nullptr;
      HashEntryT* entry = mData[idx];

      while (entry != nullptr && entry->mKey != key) {
        prevEntry = entry;
        entry = entry->mNext;
      }

      if (entry == nullptr) {
        entry = pAllocator->allocate();
        entry->mKey = key;
        entry->mValue = value;

        if (prevEntry == nullptr) {
          mData[idx] = entry;
        }
        else {
          prevEntry->mNext = entry;
        }
      }
      else {
        entry->mValue = value;
      }
    }
};
