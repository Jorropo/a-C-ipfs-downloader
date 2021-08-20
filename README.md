# Fast-IPFS

Fast IPFS is my custom C data oriented implementation of the IPFS protocol that aims multi Gigabytes per second speeds focusing on speed rather than correctness or security.

It's mostly also me wanting to write some more C code.

# Safety / Consistenty

This is not a goal, I agree that RCE and memory corruptions are an issue but the code is written to see some sweet high numbers.

I'm not a good C programer, be aware this software has bugs.

# Implemented Libs

- [Unsigned-varuint](https://github.com/multiformats/unsigned-varint)
  - [varuint.h](./varuint.h)
  - [varuint.c](./varuint.c)

# Requirement

- Linux >= 5.3
