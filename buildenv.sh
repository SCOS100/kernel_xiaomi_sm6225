#!/bin/sh

echo "Type 'exit' to quit environment."
ARCH=arm64 CC="distcc clang" LD=ld.lld AS=llvm-as AR=llvm-ar NM=llvm-nm OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- LLVM=1 LLVM_IAS=1 debian_chroot="Redmi Note 11/NFC Kernel" bash
