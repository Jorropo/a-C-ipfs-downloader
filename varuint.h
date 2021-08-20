/*
    This implements the varuint <https://github.com/multiformats/unsigned-varint> specification.
*/

// I'll reffer as unsigned-varint as varuint because I like myself.

// This REALLY expects you have optimisation enabled.

#ifndef varuint_h
#define varuint_h

#include <stddef.h>
#include <stdint.h>

uint64_t varuint_F_toU64(const uint8_t*);
uint32_t varuint_F_toU32(const uint8_t*);
size_t varuint_F_len(const uint8_t*);

// Reads a varuint into an unsigned integer up to 64 bits wide.
/*
  - result must be an unsigned integer and will be overwriten, it will addapt to any size up to 64 bits automagicaly
  - data must be an `const uint8_t*` and will be advanced to the next byte after the varuint red.
  - error must be a label.
*/
// The value of result is undefined in case of failure, you should expect garbage data. data will not be fully over the current varuint in
// case failure, to do so use varuint_M_toUnsigned_fullySkip
#define varuint_M_toUnsigned(result, data, error)                                                                                          \
  do {                                                                                                                                     \
    result = 0;                                                                                                                            \
    size_t usedBits = 0;                                                                                                                   \
    do {                                                                                                                                   \
      typeof(result) cur = *data & 0b01111111;                                                                                             \
      if (            /* Is the number we are trying to write using more bits than the type of result allows to store ? */                 \
          cur != 0 && /* Skip if cur is 0 because clz is undefined if the input is 0 */                                                    \
          sizeof(typeof(result)) * 8 - /* Fetch the index of the first bit from the number of lead zeros */                                \
              ((sizeof(typeof(result)) * 8 > 32)                                                                                           \
                 ? (__builtin_clzl(cur) - (sizeof(uint64_t) * 8 - sizeof(typeof(result)) * 8))                                             \
                 : (__builtin_clz(cur) -                                                                                                   \
                    (sizeof(uint32_t) * 8 -                                                                                                \
                     sizeof(typeof(result)) * 8))) /* Use the correct clz and compensate if the size of clz doesn't match result's size */ \
              + usedBits                           /* Plus already used bits */                                                            \
            > sizeof(typeof(result)) *                                                                                                     \
                8 /* Is the total number of bits required by the number bigged than what we have available in result ? */                  \
      ) {                                                                                                                                  \
        goto error;                                                                                                                        \
      }                                                                                                                                    \
      result |= cur << usedBits;                                                                                                           \
      usedBits += 7;                                                                                                                       \
    } while (*data++ & 0b10000000);                                                                                                        \
  } while (0)

// varuint_M_toUnsigned_fullySkip is the same as varuint_M_toUnsigned but fully advance the data pointer over the current varuint even in
// case of failure.
#define varuint_M_toUnsigned_fullySkip(result, data, error)                                                                                \
  do {                                                                                                                                     \
    varuint_M_toUnsigned(result, data, varuint_M_toUnsigned_fullySkip_error);                                                              \
    goto varuint_M_toUnsigned_fullySkip_end;                                                                                               \
  varuint_M_toUnsigned_fullySkip_error : {                                                                                                 \
    size_t zzz; /* Doesn't matter and should be optimised away. */                                                                         \
    varuint_M_len(zzz, data);                                                                                                              \
    goto error;                                                                                                                            \
  }                                                                                                                                        \
  varuint_M_toUnsigned_fullySkip_end:                                                                                                      \
  } while (0)

// Same as varuint_F_toU64 but advance the data pointer.
/*
  - result must be incrementable and will be incremented how many bytes the varuint takes.
  - data must be an `const uint8_t*` and will be advanced to the next byte after the varuint red.
*/
#define varuint_M_len(result, data)                                                                                                        \
  do {                                                                                                                                     \
    result++;                                                                                                                              \
  } while (*data++ & 0b10000000)

#endif
