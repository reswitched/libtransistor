# libtransistor
[![Build Status](https://travis-ci.org/reswitched/libtransistor.svg?branch=development)](https://travis-ci.org/reswitched/libtransistor) [![Chat on Discord](https://img.shields.io/badge/chat-Discord-brightgreen.svg)](https://discordapp.com/invite/ZdqEhed)

Libtransistor is a userland library for the Nintendo Switch. Binaries should run under Mephisto, Yuzu, Ryujinx, and on 3.0.0 consoles via ROhan or nsphax (Homebrew Launcher).

## Documentation
The documentation is automatically built and can be found here: https://reswitched.github.io/libtransistor

## Installation

For a more in-depth explanation, see [The Guide](https://reswitchedweekly.github.io/Development-Setup).

Download our [latest release](https://github.com/reswitched/libtransistor/releases/latest). Choose either `libtransistor_vX.X.X.tar.gz` or `libtransistor_vX.X.X.zip`, and extract it. The recommended place to extract these archives is into `/opt/libtransistor/`. Next, set the `LIBTRANSISTOR_HOME` environment variable to wherever you extracted the archive.

The `tests_{nro,nso}.{tar.gz,zip}` archives contain builds of all of the tests included with libtransistor.

## Usage

If you're using a Makefile-based build system, include `$(LIBTRANSISTOR_HOME)/libtransistor.mk`. You will also need to provide custom linking rules. See [`projects/example/`](https://github.com/reswitched/libtransistor/blob/development/projects/example/Makefile) for an example of how to do this.

Otherwise, specify `CC_FLAGS` and `LD_FLAGS` and such based off of [`libtransistor.mk`](https://github.com/reswitched/libtransistor-base/blob/master/libtransistor.mk).

## Building

For a more in-depth explanation, see [The Guide](https://reswitchedweekly.github.io/Development-Setup).

First, clone the repo with

```
git clone --recursive https://github.com/reswitched/libtransistor
```

Next, get a copy of [libtransistor-base](https://github.com/reswitched/libtransistor-base.git). You can either [build it yourself](https://github.com/reswitched/libtransistor-base#building), or download a [pre-built release](https://github.com/reswitched/libtransistor-base/releases). Pick a release with a version number equal to the version of libtransistor that you are building, or the next lowest if no such version exists. If you build it yourself, copy the `dist/` folder from libtransistor-base to the root of this repository's contents, so it's in the same place as this `README.md` and `lib` and `include`. If you download a release, extract it into a new folder called `dist`.

You will need Python 3 and the python packages listed in [`dist/requirements.txt`](https://github.com/reswitched/libtransistor-base/blob/master/requirements.txt). You'll also need clang and lld >=5.0 (llvm linker).

You *should* just be able to run `make`. If that doesn't work, submit an issue (or pull request). This will produce a number of `nro` and `nso` files in `build/test/`. These are binaries for the Nintendo Switch. NRO files are relocatable shared objects suitable for use with [ROhan](https://reswitched.tech/rohan), [the Homebrew Launcher](https://switchbrew.github.io/nx-hbl/), or any other loader taking NROs. Both NRO and NSO binaries can be run under Mephisto.

### Building on Fedora

Fedora does not ship recent enough clang and lld binaries. However, pre-built clang binaries from [llvm.org](https://releases.llvm.org) can be used. 

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

### Building on Arch Linux

You'll need to install some packages.
```bash
sudo pacman -S llvm clang lld python python-pip squashfs-tools base-devel git cmake
```

and you'll also need to install some python dependencies via pip.
```bash
pip install --user -r requirements.txt
```
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
