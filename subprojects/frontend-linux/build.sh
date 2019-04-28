set -e

unset CC
PRIVATE_DIR="$1"
OUTPUT="$2"
shift 2

rm -rf "$PRIVATE_DIR"/fscompat-linux
mkdir -p "$PRIVATE_DIR"

for INPUT in "$@"
do
    FILENAME="`basename "$INPUT" .c`.o"
    OBJECTS="$OBJECTS $FILENAME"
done

SOURCE_DIR="`dirname "$1"`"
cp -R "$SOURCE_DIR" "$PRIVATE_DIR"/fscompat-linux
pushd "$PRIVATE_DIR"/fscompat-linux

echo "obj-m := $OBJECTS" > Kbuild
MODULE_DIR=/usr/src/linux-headers-*
if [[ -e "/lib/modules/`uname -r`/build" ]]
then
    MODULE_DIR="/lib/modules/`uname -r`/build"
fi
make -C "$MODULE_DIR" M="`pwd`"

popd

mv "$PRIVATE_DIR"/fscompat-linux/fscompat.ko "$OUTPUT"
