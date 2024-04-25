ARG SDK_VERSION=28
ARG NDK_VERSION=23.1.7779620
ARG BUILDTOOLS_VERSION=28.0.3

FROM androidsdk/android-${SDK_VERSION}

ARG SDK_VERSION
ARG NDK_VERSION
ARG BUILDTOOLS_VERSION

RUN sdkmanager --install "ndk;${NDK_VERSION}"
RUN sdkmanager --install "build-tools;${BUILDTOOLS_VERSION}"

# ANDROID_SDK is already set to /opt/android-sdk-linux
ENV ANDROID_NDK="${ANDROID_SDK}/ndk/${NDK_VERSION}"
ENV ANDROID_TOOLCHAIN_BIN="${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin"
ENV ANDROID_API_LEVEL="${SDK_VERSION}"
ENV HOST="aarch64-linux-android"

RUN apt-get update
RUN apt-get install -y autoconf automake libtool make pkg-config
RUN apt-get install -y gradle
