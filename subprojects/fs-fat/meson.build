project('fscompat-backend-fat', 'c',
    license: 'CC0',
    default_options : [
        'c_std=c11', 'b_lto=true',
        'warning_level=3', 'werror=true'
    ]
)

interface = subproject('interface').get_variable('interface_dep')

add_project_arguments('-ffreestanding', '-pedantic', language: 'c')

inc = include_directories('include')
lib = static_library('fscompat-backend-fat', 'src/fat.c',
    include_directories: inc,
    dependencies: interface
)

fat_dep = declare_dependency(include_directories: inc, link_with: lib)
