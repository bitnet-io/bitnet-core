#!/bin/bash
yum install qemu-img caja xorg-* mesa-* -y

sudo dnf -y install dnf-plugins-core
 sudo dnf config-manager \
    --add-repo \
    https://download.docker.com/linux/fedora/docker-ce.repo


 sudo dnf install docker-ce docker-ce-cli containerd.io

systemctl start docker

systemctl enable docker (for starting docker at system startup)
