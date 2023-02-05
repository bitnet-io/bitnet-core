#!/bin/bash
 
 yum install wget -y
 
 if [ ! -f checkinstall-1.6.2-1.x86_64.rpm ]; then
 wget https://raw.githubusercontent.com/rpmsphere/x86_64/master/c/checkinstall-1.6.2-1.x86_64.rpm
yum install checkinstall*.rpm psutils alien dpkg boost* rpm-build -y
    else
        echo "system already has checkinstall."
        rpm -qa | grep checkinstall
    fi
 

yum groupinstall "C Development Tools and Libraries" -y


sh autgen.sh
./configure --with-incompatible-bdb --prefix=/usr --enable-sse2
make -j24 clean
make -j24
make -j24 install

export PAGER=less

echo "checkinstall will build a debian set "version" to start with a number e.g. 0.0.1-version with option "3" Crtl-C to exit script will pause for 20 seconds"

sleep 20s
checkinstall -D --install=no --exclude=/sys/fs/selinux --pkgversion=0.0.1-changethis
alien --scripts --to-rpm *.deb

echo "check script for a macOS build"
# make -j24 deploy         to build for macOS ,,, review doc/build-osx.md        edit Makefile from PYTHON = /usr/local/bin/python3 to PYTHON = python2 for macosdeployqt errors on final step of constructing DMG
