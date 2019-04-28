project('fscompat-linux',
    license: ['CC0', 'ISC', 'GPL-2.0+'],
    default_options : ['c_std=gnu11']
)

dependency('libelf')

bash = find_program('bash')

custom_target('fscompat.ko',
    output: 'fscompat.ko',
    input: 'fscompat.c',
    command: [
        bash,
        '-c',
        'unset CC'
            + '&& pushd "`dirname "@INPUT@"`"'
            + '&& MODDIR="`pwd`"'
            + '&& popd'
            + '&& mkdir -p @PRIVATE_DIR@'
            + '&& cd @PRIVATE_DIR@'
            + '&& make -C /lib/modules/`uname -r`/build '
                + 'M="$MODDIR"'
            + '&& mv "$MODDIR"/fscompat.ko @OUTPUT@'
    ],
    build_by_default: true
)
