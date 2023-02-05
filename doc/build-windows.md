WINDOWS BUILD NOTES
====================

mkdir /opt/winradio

or from docker run -it -d -v /opt/winradio:/opt/winradio ubuntu:22.04

docker exec -it <docker_random_hash_> bash

as root

apt-get update && apt-get install git-core build-essential nano sudo -y

cd /opt/winradio

git clone https://github.com/bitnet-io/bitnet-core

cd bitnet-core

then as always install more of the general dependencies:

as root:
```
 apt-get update && apt-get upgrade && apt-get install apt aptitude apt-file wget nano build-essential git-core build-essential libtool autotools-dev automake pkg-config bsdmainutils curl git sudo nsis g++-mingw-w64-x86-64 protobuf* -y
 apt-get install *mingw* g++-mingw-w64-x86-64 mingw-w64-x86-64-dev -y
```
Then build using: (windows x86_64 64bit .exe binaries)
replace -j8 with your cpu core count (core i7 = 8 cores)

    cd depends
    make -j8 HOST=x86_64-w64-mingw32
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/usr
    #select 1 for posix both updates (dont forget to put back for standard linux or macOS builds)
    update-alternatives --config x86_64-w64-mingw32-g++
    update-alternatives --config x86_64-w64-mingw32-gcc
    make -j8    (where 200 is cpu core count)






original bitcoin-core build-windows.md notes

A host toolchain (`build-essential`) is necessary because some dependency
packages (such as `protobuf`) need to build host utilities that are used in the
build process.

## Building for 64-bit Windows

To build executables for Windows 64-bit, install the following dependencies:

    sudo apt-get install g++-mingw-w64-x86-64 mingw-w64-x86-64-dev

Then build using:

    cd depends
    make HOST=x86_64-w64-mingw32
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
    make

## Building for 32-bit Windows

To build executables for Windows 32-bit, install the following dependencies:

    sudo apt-get install g++-mingw-w64-i686 mingw-w64-i686-dev 

Then build using:

    cd depends
    make HOST=i686-w64-mingw32
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=/
    make

## Depends system

For further documentation on the depends system see [README.md](../depends/README.md) in the depends directory.

Installation
-------------

After building using the Windows subsystem it can be useful to copy the compiled
executables to a directory on the windows drive in the same directory structure
as they appear in the release `.zip` archive. This can be done in the following
way. This will install to `c:\workspace\bitcoin`, for example:

    make install DESTDIR=/mnt/c/workspace/bitcoin
