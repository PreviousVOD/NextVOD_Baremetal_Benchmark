#!/bin/sh

FLASH_SIZE=1048576

INPUT_IMAGE="$1"
BINARY_NAME="$2"

# ELF name not a valid name.
if [ ! -f "${INPUT_IMAGE}" ] ; then
    echo "No such file."
    exit -1
fi

# Output name not set..
if [ -z "${BINARY_NAME}" ] ; then
    echo "Binary name not set, using default"
    BINARY_NAME="image.bin"
fi

# Create binary file from ELF
sh-unknown-elf-objcopy -O binary ${INPUT_IMAGE} ${BINARY_NAME}
if [ "$?" -lt "0" ] ; then
    exit -2
fi

# Calculate size and padding length
BINARY_SIZE=`stat --format "%s" ${BINARY_NAME}`
PAD_SIZE=$((${FLASH_SIZE} - ${BINARY_SIZE}))

echo "Output binary size: ${BINARY_SIZE}, additional padding: ${PAD_SIZE}."

# Pad output file using `dd`
tr '\0' '\377' < /dev/zero | dd bs=1 count=${PAD_SIZE} of=${BINARY_NAME} conv=notrunc seek=${BINARY_SIZE}