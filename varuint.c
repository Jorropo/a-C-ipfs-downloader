/*
    This implements the varuint <https://github.com/multiformats/unsigned-varint>
    specification.
*/

#include "varuint.h"
#include <limits.h>

uint64_t varuint_F_toU64(const uint8_t* data) {
  {
    uint64_t result;
    varuint_M_toUnsigned(result, data, error);
    return result;
  }
error:
  return ULONG_MAX;
}
uint32_t varuint_F_toU32(const uint8_t* data) {
  {
    uint32_t result;
    varuint_M_toUnsigned(result, data, error);
    return result;
  }
error:
  return UINT_MAX;
}

size_t varuint_F_len(const uint8_t* data) {
  uint64_t result = 0;
  varuint_M_len(result, data);
  return result;
}
