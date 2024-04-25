# building QT for Android

git clone https://github.com/bitnet-io/bitnet-core
cd bitnet-core

docker build -t android-bitcoin .

docker run --rm -v $(pwd):/work --user "$(id -u):$(id -g)" -it android-bitcoin /bin/bash


cd /work
make -j24 -C depends
./autogen.sh
./configure --host=${HOST} --prefix=/work/depends/${HOST}   --disable-bench   --disable-gui-tests   --disable-tests --disable-fuzz-binary

make -j24
make -j24 -C src/qt apk

mv src/qt/android/build/outputs/apk/release/android-release-unsigned.apk .
mv src/qt/android/build/outputs/apk/debug/android-debug.apk .
