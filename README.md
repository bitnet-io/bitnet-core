
bitnet-io staging tree 24.x
===========================

* for releases for macos + windows + linux

* https://github.com/bitnet-io/bitnet-core/releases/tag/linux-windows-wallet


How do I build the software?
----------------------------

The most troublefree and reproducable method of building the repository is via the depends method:

# LINUX

```

    git clone https://github.com/bitnet-io/bitnet-core
    cd bitnet-core
    cd depends
    make -j12 HOST=x86_64-pc-linux-gnu  # -j12 for 12 cores adjust here
    cd ..
    ./autogen.sh

    CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure \
    --prefix=$PWD/bitnet-shared-linux --disable-tests --disable-bench --disable-fuzz-binary

    make -j12 				# -j12 for 12 cores adjust here
    make -j12 install 		        # -j12 for 12 cores adjust here

    files will be placed into bitnet-shared-linux folder
```
# WINDOWS 64-bit (only build the system using Ubuntu 22.04 Debian and Fedora the win64 exe will break and not work properly)
```
    git clone https://github.com/bitnet-io/bitnet-core
    cd bitnet-core

    apt-get update -y

    apt install build-essential libtool autotools-dev automake pkg-config \
    bsdmainutils curl git nsis nano sudo g++-mingw-w64-x86-64-posix -y

    cd depends
    make -j12 HOST=x86_64-w64-mingw32	# -j12 for 12 cores adjust here
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure \
     --prefix=$PWD/bitnet-shared-windows --disable-fuzz-binary --disable-bench

    make -j12 				# -j12 for 12 cores adjust here
    make -j12 install   		# -j12 for 12 cores adjust here
    make -j12 deploy			# for setup.exe adjust 12 cores to your core count requires nsis see doc/build-windows.md for deps

```

# macOS

```
From Terminal.app

/Applications/Utilities/Terminal.app

xcode-select --install

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

brew install automake libtool boost pkg-config libevent berkeley-db@4 qt@5 qrencode miniupnpc libnatpmp zeromq 

git clone https://github.com/bitnet-io/bitnet-core

cd bitnet-core

./autogen.sh

./configure --prefix=$PWD/bitnet-macos-shared --disable-tests --disable-bench \
 --disable-fuzz-binary

make -j8 				        # -j8 for 8 cores adjust here
make -j8 install 		        # -j8 for 8 cores adjust here

file will be in bitnet-core/bitnet-macos-shared
```


License
-------

Bitnet-Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.


