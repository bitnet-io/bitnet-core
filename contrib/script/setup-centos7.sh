#!/bin/sh

# Setup Qtum build environment for CentOS 7
yum -y install centos-release-scl
yum -y install devtoolset-10-gcc devtoolset-10-gcc-c++
yum -y install autoconf automake binutils bison ca-certificates curl faketime git libtool patch pkgconfig python3 python3-pip cmake curl-devel gmp-devel libmicrohttpd-devel miniupnpc-devel
yum -y install http://repo.okay.com.mx/centos/7/x86_64/release/automake-1.14-1.el7.x86_64.rpm

DEVTOOLSET="source scl_source enable devtoolset-10"
FILENAME="/etc/profile"
if grep "$DEVTOOLSET" $FILENAME > /dev/null
then
   echo "devtoolset-10 enabled"
else
   echo $DEVTOOLSET | tee -a $FILENAME
   reboot
fi
