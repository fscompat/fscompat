project('fscompat-linux',
    license: ['CC0', 'ISC', 'GPL-2.0+'],
    default_options : ['c_std=gnu11']
)

dependency('libelf')

bash = find_program('bash')

custom_target('fscompat.ko',
    output: 'fscompat.ko',
    input: files('fscompat.c'),
    command: [ bash, files('build.sh'), '@PRIVATE_DIR@', '@OUTPUT@', '@INPUT@' ],
    build_by_default: true
)
