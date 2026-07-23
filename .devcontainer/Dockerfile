FROM antmicro/renode:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    gdb-multiarch \
    binutils-arm-none-eabi \
    make \
    git \
    curl \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install pyserial ecdsa