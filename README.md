bitnet-io staging tree 24.x
===========================



How do I build the software?
----------------------------

The most troublefree and reproducable method of building the repository is via the depends method:

    git clone https://github.com/bitnet-io/bitnet-core
    cd bitnet-core/depends
    make HOST=x86_64-pc-linux-gnu
    cd ..
    ./autogen.sh
    CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure
    make



License
-------

Bitnet-Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.


