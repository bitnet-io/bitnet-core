
Debian
====================
This directory contains files used to package bitnetd/bitnet-qt
for Debian-based Linux systems. If you compile bitnetd/bitnet-qt yourself, there are some useful files here.

## bitnet: URI support ##


bitnet-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitnet-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitnet-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

bitnet-qt.protocol (KDE)

