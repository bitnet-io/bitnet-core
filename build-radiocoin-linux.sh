sh autogen.sh
 ./configure --with-incompatible-bdb --prefix=/usr --enable-sse2
echo 'adjust -j24 to your system core count to avoid compiler panics check with htop or etcetcetc..
make -j24
make -j24 install
'
