project('fscompat-fuse', 'c',
    license: ['CC0', 'ISC', 'GPL-2.0+'],
    default_options : ['c_std=c11', 'b_lto=true']
)

inc = include_directories('include')

fuse = dependency('fuse')
interface = subproject('interface').get_variable('interface_dep')

fat = subproject('fs-fat').get_variable('fat_dep')
executable('fscompat-fuse-fat', ['src/io.c', 'src/fat.c'],
    dependencies: [fuse, fat, interface],
    install: true,
    include_directories: inc
)
