FROM ubuntu:22.04
 
ENV DEBIAN_FRONTEND=noninteractive
 
RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    gdb-multiarch \
    qemu-system-arm \
    make \
    binutils-arm-none-eabi \
    git \
    curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
 
