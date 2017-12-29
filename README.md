# libtransistor
[![Build Status](https://travis-ci.org/reswitched/libtransistor.svg?branch=master)](https://travis-ci.org/reswitched/libtransistor) [![Chat on Discord](https://img.shields.io/badge/chat-Discord-brightgreen.svg)](https://discordapp.com/invite/ZdqEhed)

Libtransistor is a userland library for the Nintendo Switch. Currently, binaries can only be run under [Mephisto](https://github.com/reswitched/Mephisto) or with pegaswitch with ACE on 3.0.0.

## Building

First, clone the repo with

```
git clone --recursive https://github.com/reswitched/libtransistor
```

You will need Python 2 and the python packages listed in [`requirements.txt`](https://github.com/reswitched/libtransistor/blob/master/requirements.txt). You'll also need clang and lld >=5.0 (llvm linker).

You *should* just be able to run `make`. If that doesn't work, submit an issue (or pull request). This will produce a number of `nro` and `nso` files in `build/test/`. These are binaries for the Nintendo Switch. NRO files are relocatable shared objects suitable for use with [ROhan](https://reswitched.tech/rohan). Both NRO and NSO binaries can be run under Mephisto, but NSO binaries don't get relocated properly at the moment and will crash pretty quickly.

### Building on Fedora

Fedora does not ship recent enough clang and lld binaries. However, pre-built clang binaries from [llvm.org](http://releases.llvm.org) can be used. 

Example:

```bash
wget -c http://releases.llvm.org/5.0.1/clang+llvm-5.0.1-x86_64-linux-gnu-Fedora27.tar.xz
tar xpf clang+llvm-5.0.1-x86_64-linux-gnu-Fedora27.tar.xz
export PATH=`pwd`/clang+llvm-5.0.1-x86_64-linux-gnu-Fedora27/bin:$PATH
cd libtransistor
make
```

If some of the cmake CXX tests fail, you may need to install the necessary dependencies.

```bash
sudo dnf -y install libstdc++-devel gcc-c++.x86_64
```

### Building with Docker
The docker image provides a shell that can build libtransistor and other libtransistor projects.
```
cd libtransistor
docker build -t libtransistor_shell .
docker run -it libtransistor_shell
```

In order to persist files between docker containers, you might be interested in using [bind mounts](https://docs.docker.com/engine/admin/volumes/bind-mounts/). For instance, to create and share a new directory named `share` to `/build/share` within the container, the following can be done:
```
mkdir $(pwd)/share
docker run -v $(pwd)/share:/build/share -it libtransistor_shell
```

And it can be observed that any files within `/build/share` within the container will also appear the host machine's filesystem.


## Running

```
$ ./ctu --load-nro <path-to-libtransistor>/build/test/<binary>.nro
```
For running the `bsd` test, you may want to also pass `--enable-sockets`. Don't pass that for anything you don't want phoning home, though.

## Debugging

Because Mephisto comes with a GDB stub and we produce standard ELF files before converting to NSO/NRO, we can debug libtransistor binaries very easily.

```
$ ./ctu --load-nro <path-to-libtransistor>/build/test/<binary>.nro --enable-gdb
[GdbStub] INFO: Starting GDB server on port 24689...
[GdbStub] INFO: Waiting for gdb to connect...
```
```
$ aarch64-none-elf-gdb 
(gdb) target remote localhost:24689
Remote debugging using localhost:24689
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x0000007100000080 in ?? ()
(gdb) add-symbol-file <path-to-libtransistor>/build/test/<binary>.nro.so 0x7100000000 -s .bss 0x7100000000
add symbol table from file "<path-to-libtransistor>/build/test/<binary>.nro.so" at
	.text_addr = 0x7100000000
	.bss_addr = 0x7100000000
(y or n) y
Reading symbols from <path-to-libtransistor>/build/test/<binary>.nro.so...done.
(gdb) 
```
