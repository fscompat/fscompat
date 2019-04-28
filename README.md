# fscompat [![Build Status](https://travis-ci.com/fscompat/fscompat.svg?branch=master)](https://travis-ci.com/fscompat/fscompat)

fscompat aims to create public domain implementations of many filesystems
with a shared interface, so they can all be easily ported to many
operating systems. Currently, as a proof-of-concept, only FAT(12|16|32)
is being implemented, though contributions from those familiar with other
filesystems are definitely welcome.

There are currently four frontends: a macOS kext (`frontend-darwin`), a
FreeBSD kernel module (`frontend-freebsd`), a FUSE module
(`frontend-fuse`), and a Linux kernel module (`frontend-linux`). The goal
is to have every filesystem functional with every frontend.

## License

Each subproject is licensed separately. Most are licensed under CC0 and
many frontends are dual- or triple- licensed under the ISC license and/or
the GPL as well.

Subprojects which do not state a license are dedicated to the public
domain under CC0.

## Building

fscompat uses Meson for building. To compile every platform that is
supported on your machine (based on OS and installed libraries),
run Meson as normal from the root directory:

    meson setup build
    cd build
    ninja
