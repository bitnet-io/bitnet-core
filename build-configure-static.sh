cd depends
make HOST=x86_64-pc-linux-gnu
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure --prefix=$PWD/bitnet-shared-diff --with-incompatible-bdb --enable-sse2 --without-natpmp --disable-tests --disable-bench --disable-fuzz --disable-fuzz-binary
