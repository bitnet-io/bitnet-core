#!/bin/sh

# must also be install on every new image on a LAN behind clamav squid proxy including fresh docker images or KVM images or yum, apt, wget, curl \
# wont work due to not having the self signed cert for squidguard clamav virus scanning
# cert must also be import to each browser on a LAN firefox or chrome as a CA import

#fedora
echo "
-----BEGIN CERTIFICATE-----
MIIBrzCCAVSgAwIBAgIBADAKBggqhkjOPQQDBDAdMQ4wDAYDVQQDEwVFQ0RTQTEL
MAkGA1UEBhMCVVMwHhcNMjEwMzIzMTI0NzI2WhcNMzEwMzIxMTI0NzI2WjAdMQ4w
DAYDVQQDEwVFQ0RTQTELMAkGA1UEBhMCVVMwWTATBgcqhkjOPQIBBggqhkjOPQMB
BwNCAATE186oMbvokUyrrvgUYSJXG9+M5EUNVz0cydzn4x5TdHkuMk5/vlweKBhr
TV0CKZN0rUs1QWklhX/34e/tQOp1o4GEMIGBMB0GA1UdDgQWBBQeBQCziCMHz6oa
2K/TkLAGt7pHnzBFBgNVHSMEPjA8gBQeBQCziCMHz6oa2K/TkLAGt7pHn6EhpB8w
HTEOMAwGA1UEAxMFRUNEU0ExCzAJBgNVBAYTAlVTggEAMAwGA1UdEwQFMAMBAf8w
CwYDVR0PBAQDAgEGMAoGCCqGSM49BAMEA0kAMEYCIQC1MJQfvBpqzONLKNuCuxng
3Y7e+PuMnLiW+nHnkqdofAIhANYqlKFybVs4fBT4qxut+pCpR9HCUKmarDHMvL19
ot2P
-----END CERTIFICATE-----
" > ECDSA.crt
 cp ECDSA.crt /usr/share/pki/ca-trust-source/anchors/
 update-ca-trust


## ubuntu
echo "
-----BEGIN CERTIFICATE-----
MIIBrzCCAVSgAwIBAgIBADAKBggqhkjOPQQDBDAdMQ4wDAYDVQQDEwVFQ0RTQTEL
MAkGA1UEBhMCVVMwHhcNMjEwMzIzMTI0NzI2WhcNMzEwMzIxMTI0NzI2WjAdMQ4w
DAYDVQQDEwVFQ0RTQTELMAkGA1UEBhMCVVMwWTATBgcqhkjOPQIBBggqhkjOPQMB
BwNCAATE186oMbvokUyrrvgUYSJXG9+M5EUNVz0cydzn4x5TdHkuMk5/vlweKBhr
TV0CKZN0rUs1QWklhX/34e/tQOp1o4GEMIGBMB0GA1UdDgQWBBQeBQCziCMHz6oa
2K/TkLAGt7pHnzBFBgNVHSMEPjA8gBQeBQCziCMHz6oa2K/TkLAGt7pHn6EhpB8w
HTEOMAwGA1UEAxMFRUNEU0ExCzAJBgNVBAYTAlVTggEAMAwGA1UdEwQFMAMBAf8w
CwYDVR0PBAQDAgEGMAoGCCqGSM49BAMEA0kAMEYCIQC1MJQfvBpqzONLKNuCuxng
3Y7e+PuMnLiW+nHnkqdofAIhANYqlKFybVs4fBT4qxut+pCpR9HCUKmarDHMvL19
ot2P
-----END CERTIFICATE-----
" > ECDSA.crt
 cp ECDSA.crt /usr/local/share/ca-certificates/
 update-ca-certificates 
