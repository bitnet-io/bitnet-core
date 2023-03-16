cd depends
    make HOST=x86_64-w64-mingw32
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=$PWD/bitnet-shared-windows-diff --with-incompatible-bdb --enable-sse2 --without-natpmp --disable-tests --disable-bench --disable-fuzz --disable-fuzz-binary
