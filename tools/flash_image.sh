#!/bin/sh

IMAGE_NAME=$1

if [ -z "${IMAGE_NAME}" ] ; then
    IMAGE_NAME=image.bin
fi

if [ ! -f "${IMAGE_NAME}" ] ; then
    echo "binary not exist."
    exit -1
fi

flashrom --programmer ch341a_spi -w "${IMAGE_NAME}"