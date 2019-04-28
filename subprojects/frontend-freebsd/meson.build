project('fscompat-linux', license: ['CC0', 'ISC'])

custom_target('fscompat.ko',
    output: 'fscompat.ko',
    input: files('src/Makefile', 'src/fscompat.c'),
    command: [
        'sh',
        '-c',
        'make -C "`dirname "@INPUT0@`"'
            + '&& mv "`dirname @INPUT0@`"/fscompat.ko @OUTPUT@'
            + '|| rm -rf "`dirname @INPUT@`"/fscompat.ko'
    ]
)
