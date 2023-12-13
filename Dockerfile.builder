FROM ubuntu:23.04

# Conan build
RUN apt update \
    && DEBIAN_FRONTEND=noninteractive apt upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    # Compiler & Tools
    autoconf \
    automake \
    ccache \
    clang \
    clang-format \
    clang-tidy \
    cmake \
    cppcheck \
    git \
    golang \
    less \
    make \
    ninja-build \
    pkg-config \
    vim \
    # Libraries
    libbz2-dev \
    libc++-dev \
    libc++abi-dev \
    libcrypto++-dev \
    libgflags-dev \
    libgmp-dev \
    libgtest-dev \
    libjsoncpp-dev \
    liblz4-dev \
    libmicrohttpd-dev \
    libmpfr-dev \
    libssl-dev \
    libzstd-dev \
    prometheus-cpp-dev \
    rapidjson-dev \
    # Needed it for git (revisit)
    && apt install -y --reinstall ca-certificates \
    # Cleanup
    && rm -rf /var/lib/apt/lists/* && rm -rf /var/cache/apt/archives

WORKDIR /buildarea

ENV CC=clang
ENV CPP=clang-cpp
ENV CXX=clang++
ENV LD=ld.lld

# Hack, clang-cpp doesn't provide a symlink
RUN ln -s /usr/bin/clang-cpp-15 /usr/bin/clang-cpp

CMD ["echo", "Builder is ready 🎉"]
