# libtransistor
[![Build Status](https://travis-ci.org/reswitched/libtransistor.svg?branch=master)](https://travis-ci.org/reswitched/libtransistor)

Libtransistor is a userland library for the Nintendo Switch. Currently, binaries can only be run under [Mephisto](https://github.com/reswitched/Mephisto). 

## Building

First, clone the repo with

```
git clone --recursive https://github.com/reswitched/libtransistor
```

You will need Python 2 and the python packages listed in [`requirements.txt`](https://github.com/reswitched/libtransistor/blob/master/requirements.txt). You'll also need clang and lld (llvm linker). 

You *should* just be able to run `make`. If that doesn't work, submit an issue (or pull request). This will produce a number of `nro` and `nso` files in `build/test/`. These are binaries for the Nintendo Switch. NRO files are relocatable shared objects suitable for use with [ROhan](https://reswitched.tech/rohan). Both NRO and NSO binaries can be run under Mephisto, but NSO binaries don't get relocated properly at the moment and will crash pretty quickly.

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
(gdb) add-symbol-file <path-to-libtransistor>/build/test/<binary>.nro.so 0x7100000000
add symbol table from file "<path-to-libtransistor>/build/test/<binary>.nro.so" at
	.text_addr = 0x7100000000
(y or n) y
Reading symbols from <path-to-libtransistor>/build/test/<binary>.nro.so...done.
(gdb) 
```
## Debian Info
On Debian Sid at least it's necessary to install the packages python-pyelftools nd python-lz4. Also it is necessary to install llvm using the official ppa by first adding this to the end of /etc/apt/sources.list
```
deb http://apt.llvm.org/unstable/ llvm-toolchain main
deb-src http://apt.llvm.org/unstable/ llvm-toolchain main
# 4.0 
deb http://apt.llvm.org/unstable/ llvm-toolchain-4.0 main
deb-src http://apt.llvm.org/unstable/ llvm-toolchain-4.0 main
# 5.0 
deb http://apt.llvm.org/unstable/ llvm-toolchain-5.0 main
deb-src http://apt.llvm.org/unstable/ llvm-toolchain-5.0 main
```
then run the following commands:
```
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
sudo apt-get update
sudo apt-get install clang-6.0 lldb-6.0 lld-6.0
```
