#!/bin/sh

if [ "$USER" != "root" ]; then { echo "Please run as root!"; exit 1; }; fi
if [ -z "$SUDO_USER" ]; then { echo "Please run with sudo (or set SUDO_USER to root if you are running as root)!"; exit 1; }; fi

if ! docker -v >/dev/null; then
	echo "Please install docker!!!"
	exit 1
fi

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

echo "REOWN \*"
chown $SUDO_USER:$SUDO_USER -R * # usually the username is also the groupname.
