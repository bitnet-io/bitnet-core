echo 'you can change this file for 8 cores with make -j8
cd depends
make -j8 HOST=x86_64-pc-linux-gnu
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure
make -j8
'
sleep 1s
echo 'will not build the binary using 1 core'
sleep 1s

cd depends
make -j24 HOST=x86_64-pc-linux-gnu
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure --with-gui=no --prefix=$PWD/bitnet-shared-ubuntu-diff --disable-tests --disable-bench --disable-fuzz-binary

make -j24
