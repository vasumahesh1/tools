#pragma once

#include "ToolsCore.h"

namespace EngineTools {
  class HashOperator {
    public:
      HashOperator() = default;
      HashOperator(U32 seed);
      virtual U32 evaluate(const void* bytes, UINT numBytes) const = 0;
      virtual U32 evaluate(const char* bytes, UINT len) const = 0;
      virtual U32 evaluate(const int& num) const = 0;

    protected:
      U32 mSeed{ 2166136261 };
  };

  class FNVHashOperator : public HashOperator {
    U32 mPrime{ 0x01000193 }; // 16777619
    public:
      FNVHashOperator() = default;
      FNVHashOperator(U32 seed);
      FNVHashOperator(U32 seed, U32 prime);
      U32 evaluate(const void* bytes, UINT numBytes) const override;
      U32 evaluate(const char* bytes, UINT len) const override;
      U32 evaluate(const int& num) const override;
  };
}
