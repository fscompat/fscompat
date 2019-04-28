project('fscompat-linux',
    license: ['CC0', 'ISC', 'GPL-2.0+'],
    default_options : ['c_std=gnu11']
)

dependency('libelf')

custom_target('fscompat.ko',
    output: 'fscompat.ko',
    input: files('fscompat.c', 'Kbuild'),
    command: [
        'sh',
        '-c',
        'unset CC'
            + '&& pushd "`dirname "@INPUT@"`"'
            + '&& MODDIR="`pwd`"'
            + '&& popd'
            + '&& mkdir @PRIVATE_DIR@'
            + '&& cd @PRIVATE_DIR@'
            + '&& make -C /lib/modules/`uname -r`/build '
                + 'M="$MODDIR"'
            + '&& mv "`dirname "$MODDIR"`"/fscompat.ko @OUTPUT@'
    ],
    build_by_default: true
)
