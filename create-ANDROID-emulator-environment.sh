#!/bin/bash
echo "requires around 20gb of free space"
sleep 2s
echo "******CAUTION*******"
echo "******CAUTION*******"
echo "******CAUTION*******"
echo "THIS SCRIPT WILL UPDATE GRUB2 bootloader automatically to enable iommu for KVM for hardware x86 functions of the android emulator crtl-C to cancel this script to review the script, script will pause for 10 seconds while you decide"
echo "******CAUTION*******"
echo "******CAUTION*******"
echo "******CAUTION*******"
sleep 10s

echo "where /root/Android/Sdk is the android-studio install dir"

cd /opt
wget https://redirector.gvt1.com/edgedl/android/studio/ide-zips/2020.3.1.25/android-studio-2020.3.1.25-linux.tar.gz
tar -xvf android-studio-2020.3.1.25-linux.tar.gz
sh android-studio/bin/studio.sh


echo '
export ANDROID_SDK_HOME=/root/Android/Sdk
export PATH=$PATH:/usr/lib64/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/var/lib/snapd/snap/bin:/usr/bin/gradle-6.5.1/bin:/root/Android/Sdk/tools/bin:/root/Android/Sdk/tools:/root/Android/Sdk/platform-tools/:/root/Android/Sdk/build-tools/29.0.2/:/root/Android/Sdk/tools/bin/
' >> /root/.bashrc

source /root/.bashrc





sdkmanager --install "platforms;android-29"
sdkmanager --install "build-tools;29.0.2"
sdkmanager --install "system-images;android-29;google_apis_playstore;x86"
echo "no" | avdmanager --verbose create avd --force --name Nexus --abi google_apis_playstore/x86 --package "system-images;android-29;google_apis_playstore;x86"


echo '
#!/bin/bash
cd /root/Android/Sdk/emulator
QTWEBENGINE_DISABLE_SANDBOX=1 ./emulator @Nexus -no-boot-anim -netdelay none -no-snapshot -wipe-data -skin 800x1440 & 
' > /usr/bin/EMULATOR
chmod +x /usr/bin/EMULATOR

sed -s s'/rhgb/intel_iommu=on iommu=pt rhgb/g' /etc/default/grub > grub.txt
cat grub.txt 
cp -rf grub.txt /etc/default/grub 
echo "y" |cp -rf grub.txt /etc/default/grub
sed -s s'/GRUB_ENABLE_BLSCFG=true/GRUB_ENABLE_BLSCFG=false/g' /etc/default/grub > grub.txt
rm -rf grub.txt
grub2-mkconfig -o /boot/grub2/grub.cfg 
grub2-mkconfig -o /boot/efi/EFI/fedora/grub.cfg


echo "it is mandatory to reboot now"
echo "if kvm is loaded run the EMULATOR script"
echo "on reboot"
echo "lsmod | grep kvm"
echo "/usr/bin/EMULATOR should spawn a Nexus style android emulator run adb install apkfilename.apk or "adb shell" then "logcat" to inspect running emulator, apk"
