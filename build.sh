#!/bin/sh

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> parent of 2725f1e9554e (aaaaaa)
if [ "$1 " = "env " ]; then echo "Type 'exit' to quit environment."; ARCH=arm64 CC=clang LD=ld.lld AS=llvm-as AR=llvm-ar NM=llvm-nm OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- LLVM=1 LLVM_IAS=1 debian_chroot="Redmi Note 11/NFC Kernel" bash; exit; fi

=======
>>>>>>> parent of e71c15230078 (a)
RELEASE=$(make -j$(nproc --all) kernelrelease)

# Build the kernel.
if [ ! -e .config ]; then
	echo "Setting defconfig"
	cp arch/arm64/configs/spesnd_defconfig .config
fi
if [ -d AnyKernel3 ]; then rm -r AnyKernel3; fi
git clone https://github.com/CHRISL7/AnyKernel3 -b master
cd AnyKernel3
sed -i "s/kernel.string=$(grep "kernel.string" anykernel.sh | cut -d= -f2)/kernel.string=$RELEASE/g" anykernel.sh
sed -i "s/kernel.compiler=$(grep "kernel.compiler" anykernel.sh | cut -d= -f2)/kernel.compiler=\"llvm and clang\"/g" anykernel.sh
if ! grep "=m$" ../.config 2>/dev/null >/dev/null; then
	sed -i "s/do.modules=$(grep "do.modules" anykernel.sh | cut -d= -f2)/do.modules=0/g" anykernel.sh
fi
rm README*
cd ..
make -j$(nproc --all) INSTALL_MOD_PATH=$(pwd)/AnyKernel3/modules/ ARCH=arm64 CC=clang LD=ld.lld AS=llvm-as AR=llvm-ar NM=llvm-nm OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- LLVM=1 LLVM_IAS=1 Image.gz dtbo.img
if ! [ "$?" -eq "0" ]; then
	echo "The compilation did not go well. Exiting..."
	exit 1
else
	cp arch/arm64/boot/Image.gz arch/arm64/boot/dtbo.img AnyKernel3
	cd AnyKernel3
	zip -r9 ../SPESND.zip * -x .git README.md *placeholder
	cd ..
	echo "Zip saved as SPESND.zip. Please flash it into your phone's recovery if supported."
fi
