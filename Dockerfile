FROM debian:stretch
MAINTAINER reswitched

RUN echo "deb http://apt.llvm.org/stretch/ llvm-toolchain-stretch main \n\
deb-src http://apt.llvm.org/stretch/ llvm-toolchain-stretch main \n\
# 4.0 \n\
deb http://apt.llvm.org/stretch/ llvm-toolchain-stretch-4.0 main \n\
deb-src http://apt.llvm.org/stretch/ llvm-toolchain-stretch-4.0 main \n\
# 5.0 \n\
deb http://apt.llvm.org/stretch/ llvm-toolchain-stretch-5.0 main \n\
deb-src http://apt.llvm.org/stretch/ llvm-toolchain-stretch-5.0 main" >> /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y git build-essential wget squashfs-tools python python-pip
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

RUN apt-get update
RUN apt-get install -y clang-5.0 lld-5.0

RUN mkdir -p /tmp/bin/cmake
RUN wget --no-check-certificate --quiet -O - http://www.cmake.org/files/v3.4/cmake-3.4.3-Linux-x86_64.tar.gz | tar --strip-components=1 -xz -C /tmp/bin/cmake
ENV PATH="/tmp/bin/cmake/bin:${PATH}"

WORKDIR /build
COPY . libtransistor

WORKDIR /build/libtransistor
RUN pip2 install -r requirements.txt
RUN make LLVM_POSTFIX=-5.0 LD=ld.lld-5.0

WORKDIR /build

RUN echo "echo \"You are now in a shell that can compile libtransistor projects.\nFiles outside of volume shares will be deleted when this shell is exited.\nTo use a share, add it to the docker run command; see the readme for more info.\"" >> /root/.bashrc

CMD /bin/bash