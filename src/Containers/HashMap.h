#pragma once

#include "../common.h"
#include "../MemoryAllocators/PoolAllocator.h"
#include "../Utils/Hash.h"

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

      void insert(Key key, Value value);
      bool get(Key key, Value* value);
      bool exists(Key key);

      private:
      U32 generateHash(int key);
      U32 generateHash(const char* key);

      HashEntryT* findEntry(Key key);
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
    bool HashMap<Key, Value, BUCKETS>::get(Key key, Value* value) {
      HashEntryT* entry = findEntry(key);
      bool result = false;

      if (entry != nullptr) {
        *value = entry->mValue;
        result = true;
      }

      return result;
    }

  // TODO: Need better template overloading for the Keys
  template <typename Key, typename Value, int BUCKETS>
    U32 HashMap<Key, Value, BUCKETS>::generateHash(int key) {
      return mHashOp.evaluate(key);
    }

  template <typename Key, typename Value, int BUCKETS>
    U32 HashMap<Key, Value, BUCKETS>::generateHash(const char* key) {
      return mHashOp.evaluate(key, strlen(key));
    }

  template <typename Key, typename Value, int BUCKETS>
    bool HashMap<Key, Value, BUCKETS>::exists(Key key) {
      return findEntry(key) != nullptr;
    }

  template <typename Key, typename Value, int BUCKETS>
    HashEntry<Key, Value>* HashMap<Key, Value, BUCKETS>::findEntry(Key key) {
      U32 idx = generateHash(key);
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
    void HashMap<Key, Value, BUCKETS>::insert(Key key, Value value) {
      U32 idx = generateHash(key);
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
