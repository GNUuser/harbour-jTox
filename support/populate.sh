#!/bin/bash

# Exit on errors
set -e

SSH_KEYDIR="~/SailfishOS/vmshare/ssh/private_keys/engine/mersdk"

# prepare extra
mkdir -p ../extra

# Prepare build dir and script
echo -en "Preparing build dir..\t\t\t"
ssh -p 2222 -i "$SSH_KEYDIR" mersdk@localhost 'mkdir -p ~/tox' &> /dev/null
scp -P 2222 -i "$SSH_KEYDIR" build.sh mersdk@localhost:~/tox &> /dev/null
echo "OK"

# Build
ssh -p 2222 -i "$SSH_KEYDIR" mersdk@localhost 'cd ~/tox; ./build.sh i486 && ./build.sh armv7hl'

# Copy everything where it's needed
echo -en "Copying libs and headers..\t\t"
scp -r -P 2222 -i "$SSH_KEYDIR" mersdk@localhost:~/tox/i486 ../extra  &> /dev/null
scp -r -P 2222 -i "$SSH_KEYDIR" mersdk@localhost:~/tox/armv7hl ../extra &> /dev/null
# Clean up unneeded files
# i486
rm -rf ../extra/i486/bin &> /dev/null
rm -rf ../extra/i486/lib/pkgconfig  &> /dev/null
rm ../extra/i486/lib/*.so* &> /dev/null
rm ../extra/i486/lib/*.la &> /dev/null
# arm
rm -rf ../extra/armv7hl/bin &> /dev/null
rm -rf ../extra/armv7hl/lib/pkgconfig &> /dev/null
rm ../extra/armv7hl/lib/*.so* &> /dev/null
rm ../extra/armv7hl/lib/*.la &> /dev/null
echo "OK"
