project('fscompat')

subproject('interface')
subproject('fs-fat')

fuse = dependency('fuse', required: false)
if fuse.found()
    message('Building FUSE module')
    subproject('frontend-fuse')
else
    message('FUSE not found; not building FUSE module')
endif
if build_machine.system() == 'linux' and host_machine.system() == 'linux'
    message('Building Linux kernel module')
    subproject('frontend-linux')
else
    message('Not on Linux; not building Linux kernel module')
endif
if build_machine.system() == 'freebsd' and host_machine.system() == 'freebsd'
    message('Building FreeBSD kernel module')
    subproject('frontend-freebsd')
else
    message('Not on FreeBSD; not building FreeBSD kernel module')
endif
if build_machine.system() == 'darwin' and host_machine.system() == 'darwin'
    message('Building macOS kext')
    subproject('frontend-darwin')
else
    message('Not on macOS; not building macOS kext')
endif
