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
        'make -C /lib/modules/`uname -r`/build M="`dirname "@INPUT0@"`"'
            + '&& mv "`dirname "@INPUT0"`"/fscompat.ko @OUTPUT@'
    ],
    build_by_default: true
)
