#!/bin/sh

KEXT="$1"
PKG="$2"
PRIVATE="$3"

mkdir -p "$PRIVATE"/root/System/Library/Extensions
cp -R "$1" "$PRIVATE"/root/System/Library/Extensions/
pkgbuild --analyze --root "$PRIVATE"/root/ "$PRIVATE"/package.plist

pkgbuild --root "$PRIVATE"/root/ --component-plist "$PRIVATE"/package.plist "$2"
