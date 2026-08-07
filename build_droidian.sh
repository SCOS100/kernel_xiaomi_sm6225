#!/bin/sh

echo "CREATE dirs"
mkdir -p debian/source
cp arch/arm64/configs/spes_kernel_info.mk debian/kernel-info.mk
echo "3.0 (native)" > debian/source/format
cat > debian/rules <<EOF
#!/usr/bin/make -f

include /usr/share/linux-packaging-snippets/kernel-snippet.mk

%:
	dh \$@
EOF
chmod +x debian/rules

echo "CLEAN out"
rm -f ./out/*.deb ./out/*.build* ./out/*.changes

echo "START build"
docker run --dns 1.1.1.1 --rm \
	-v ./out:/buildd \
	-v .:/buildd/sources \
	-it quay.io/droidian/build-essential:next-amd64 \
	bash -c "apt install linux-packaging-snippets; cd buildd/sources; rm -f debian/control; debian/rules debian/control; RELENG_HOST_ARCH=\"arm64\" releng-build-package"

echo "END build"
