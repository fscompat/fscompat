#!/bin/sh

INFO="$1"
MACHO="`pwd`/$2"
KEXT="`pwd`/$3"
NAME="$4"
VERSION="$5"
BUILD="$6"
BUNDLEID="$7"

cd "`dirname "$INFO"`"

mkdir -p "$KEXT"/Contents/MacOS
cp "$MACHO" "$KEXT"/Contents/MacOS/
cat Info.plist |
    sed -e "s/__KEXTNAME__/$NAME/g" \
        -e "s/__KEXTMACHO__/$NAME/g" \
        -e "s/__KEXTVERSION__/$VERSION/g" \
        -e "s/__KEXTBUILD__/$BUILD/g" \
        -e "s/__BUNDLEID__/$BUNDLEID/g" \
        -e "s/__LIBS__//g" \
    > "$KEXT"/Contents/Info.plist
LIBS="`kextlibs -xml "$KEXT"`"
cat Info.plist |
    sed -e "s/__KEXTNAME__/$NAME/g" \
        -e "s/__KEXTMACHO__/$NAME/g" \
        -e "s/__KEXTVERSION__/$VERSION/g" \
        -e "s/__KEXTBUILD__/$BUILD/g" \
        -e "s/__BUNDLEID__/$BUNDLEID/g" \
        -e "s/__LIBS__/$LIBS/g" \
    > "$KEXT"/Contents/Info.plist
