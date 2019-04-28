set -e

unset CC
PRIVATE_DIR="$1"
OUTPUT="$2"
shift 2

rm -rf "$PRIVATE_DIR"/fscompat-linux
mkdir -p "$PRIVATE_DIR"

for INPUT in "$@"
    FILENAME="`basename "$INPUT"`"
    OBJECTNAME="${$FILENAME%.*}.o"
    OBJECTS="$OBJECTS $OBJECTNAME"
done

SOURCE_DIR="`dirname "$1"`"
cp -R "$SOURCE_DIR" "$PRIVATE_DIR"/fscompat-linux
pushd "$PRIVATE_DIR"/fscompat-linux

echo "obj-m := $OBJECTS" > Kbuild
make -C /lib/modules/`uname -r`/build M="`pwd`"

popd

mv "$PRIVATE_DIR"/fscompat-linux/fscompat.ko "$OUTPUT"
