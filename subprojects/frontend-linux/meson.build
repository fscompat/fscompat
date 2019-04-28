project('fscompat-linux',
    license: ['CC0', 'ISC', 'GPL-2.0+'],
    default_options : ['c_std=gnu11']
)

custom_target('fscompat.ko',
    output: 'fscompat.ko',
    input: files('fscompat.c'),
    command: ['sh', '-c', 'make -C /lib/modules/`uname -r`/build M=$PWD']
)
