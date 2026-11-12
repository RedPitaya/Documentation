#!/bin/bash

# Usage: sudo ./updatematplotlib.sh [partition]
# Example: sudo ./updatematplotlib.sh /dev/sdd2

IMAGE_PARTITION="${1:-/dev/sdd2}"
MOUNT_POINT="/mnt/arm_root"
QEMU_BINARY="/usr/bin/qemu-arm-static"

if [[ $EUID -ne 0 ]]; then
   echo "Error: This script must be run as root (use sudo)."
   exit 1
fi

echo "Using partition: $IMAGE_PARTITION"
if [ ! -b "$IMAGE_PARTITION" ]; then
    echo "Error: $IMAGE_PARTITION is not a valid block device."
    echo "Available devices:"
    lsblk
    exit 1
fi

if [ ! -f "$QEMU_BINARY" ]; then
    apt-get update && apt-get install -y qemu-user-static
fi

mkdir -p "$MOUNT_POINT"
mount "$IMAGE_PARTITION" "$MOUNT_POINT" || {
    echo "Mounting failed. Check:"
    echo "1. Does $IMAGE_PARTITION exist?"
    echo "2. Is it already mounted? (run: mount | grep sdd2)"
    echo "3. Is it a valid filesystem?"
    exit 1
}

mount -o bind /dev/ "${MOUNT_POINT}/dev/"
mount -o bind /dev/pts "${MOUNT_POINT}/dev/pts"
mount -t proc proc "${MOUNT_POINT}/proc/"
mount -t sysfs sys "${MOUNT_POINT}/sys/"
mount -o bind /run "${MOUNT_POINT}/run"


cp "$QEMU_BINARY" "$MOUNT_POINT/usr/bin/"

cp /etc/resolv.conf    "$MOUNT_POINT/etc/"
echo "nameserver 8.8.8.8" > /etc/resolv.conf

chroot "$MOUNT_POINT" /bin/bash <<EOF
set -e
echo "Chroot architecture: \$(uname -m)"


echo "Installing/upgrading matplotlib..."
ping 8.8.8.8 -c 5

# Install build dependencies for matplotlib and Pillow
echo "Installing build dependencies..."
apt-get update
apt-get install -y \
    libjpeg-dev \
    zlib1g-dev \
    libtiff-dev \
    libfreetype6-dev \
    liblcms2-dev \
    libwebp-dev \
    libopenjp2-7-dev \
    python3-dev \
    build-essential

# Remove system matplotlib to avoid conflicts
apt-get remove -y python3-matplotlib || true

# Upgrade matplotlib to version compatible with NumPy 2.x (keep current NumPy)
pip install matplotlib --upgrade --force-reinstall

echo ""
echo "Verifying installation..."
python3 -c "import numpy; print(f'NumPy version: {numpy.__version__}')"
python3 -c "import matplotlib; print(f'Matplotlib version: {matplotlib.__version__}')"
python3 -c "from mpl_toolkits.mplot3d import Axes3D; print('3D projection: OK')" || echo "3D projection: FAILED"
echo "Operation completed successfully."
EOF

echo "Unmounting..."

sync
umount -l "${MOUNT_POINT}/run/"
umount -l "${MOUNT_POINT}/sys/"
umount -l "${MOUNT_POINT}/proc/"
umount -l "${MOUNT_POINT}/dev/pts"
umount -l "${MOUNT_POINT}/dev/"
umount -l "$MOUNT_POINT"

rmdir "$MOUNT_POINT"

echo "Script finished. Partition $IMAGE_PARTITION unmounted."
