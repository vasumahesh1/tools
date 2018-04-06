#include "Hash.h"

namespace EngineTools {
  HashOperator::HashOperator(U32 seed): mSeed(seed) {
  }

  FNVHashOperator::FNVHashOperator(U32 seed): HashOperator(seed) {
  }

  FNVHashOperator::FNVHashOperator(U32 seed, U32 prime): HashOperator(seed), mPrime(prime) {
  }

  U32 FNVHashOperator::evaluate(const void* bytes, UINT numBytes) const {
    return FNVHash(bytes, numBytes, mSeed, mPrime);
  }

  U32 FNVHashOperator::evaluate(const char* bytes, UINT len) const {
    return evaluate((void*) bytes, len);
  }

  U32 FNVHashOperator::evaluate(const int& num) const {
    return evaluate(&num, sizeof(int));
  }
}
