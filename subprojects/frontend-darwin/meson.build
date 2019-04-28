project('fscompat-darwin', 'c',
    license: ['CC0', 'ISC'],
    default_options : ['c_std=c11', 'b_lto=true']
)

name = get_option('name')
version = get_option('version')
build_number = get_option('build_number')
domain = get_option('domain')

kext_build = version + 'd' + build_number

bundle_id = domain + '.kext' + name
bundle = name + '.kext'

package = name + '.pkg'

add_project_arguments(
    '-DKERNEL',
    '-DKERNEL_PRIVATE',
    '-DDRIVER_PRIVATE',
    '-DAPPLE',
    '-DNeXT',
    '-DKEXTNAME_S="' + name + '"',
    '-DKEXTVERSION_S="' + version + '"',
    '-DKEXTBUILD_S="' + kext_build + '"',
    '-DBUNDLEID_S="' + bundle_id + '"',
    '-DBUNDLEID=' + bundle_id,
    '-fno-builtin',
    '-fno-common',
    '-mkernel',
    '-msoft-float',
    language: 'c'
)

add_project_link_arguments(
    '-nostdlib',
    '-Xlinker', '-kext',
    '-Xlinker', '-object_path_lto',
    '-Xlinker', '-export_dynamic',
    '-Xlinker', '-fatal_warnings',
    '-static',
    language: 'c'
)

c_compiler = meson.get_compiler('c')
kmod = c_compiler.find_library('kmod')
cc_kext = c_compiler.find_library('cc_kext')

kernel_headers = include_directories(
    '/System/Library/Frameworks/Kernel.framework/Headers'
)

fat = subproject('fs-fat').get_variable('fat_dep')

macho = executable(name, 'src/fscompat.c',
    dependencies: [kmod, cc_kext],
    include_directories: kernel_headers
)
bundle_tgt = custom_target(bundle,
    input: [files('src/Info.plist'), macho],
    output: bundle,
    command: [
        files('generate-bundle.sh'),
        '@INPUT@', '@OUTPUT@',
        name, version, kext_build, bundle_id
    ],
    build_by_default: true
)
custom_target(package,
    input: bundle_tgt,
    output: package,
    command: [
        files('generate-package.sh'),
        '@INPUT@', '@OUTPUT@', '@PRIVATE_DIR@'
    ]
)
