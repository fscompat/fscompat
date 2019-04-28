/* SPDX-License-Identifier: CC0 OR ISC OR GPL-3.0-or-later
fscompat for FUSE
Written in 2019 by fscompat Developers

To the extent possible under law, the author(s) have dedicated all
copyright and related and neighboring rights to this software to the
public domain worldwide. This software is distributed without any
warranty.

You should have received a copy of the CC0 Public Domain Dedication along
with this software. If not, see
<http://creativecommons.org/publicdomain/zero/1.0/>.

The full text of the CC0 Public Domain Dedication is contained in the
COPYING.CC0 file.
*/

#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <stddef.h>

#include <fused-shared.h>

#ifndef FSNAME
#error FSNAME not defined
#endif

#define FN_WITH_NAME(fs, name) fc_ ## fs ## _ ## name
#define FN_WITH_NAME2(fs, name) FN_WITH_NAME(fs, name)
#define FN(name) FN_WITH_NAME2(FSNAME, name)
#define HOOK_WITH_NAME(fs, name) fc_fuse_ ## fs ## _ ## name
#define HOOK_WITH_NAME2(fs, name) HOOK_WITH_NAME(fs, name)
#define HOOK(name) HOOK_WITH_NAME2(FSNAME, name)

struct fc_fuse_options fc_fuse_options;
struct FN(instance) *instance;

void *HOOK(init)(struct fuse_conn_info *conn) {
    instance = FN(init)();
    return NULL;
}

int HOOK(open)(const char *path, struct fuse_file_info *fi) {
    int result = FN(open)(instance, path, fi->flags);
    if (result >= 0) {
        fi->fh = result;
        return 0;
    } else {
        return result;
    }
}

int HOOK(read)(const char *path, char *buf, size_t size, off_t offset,
    struct fuse_file_info *fi) {
    return FN(read)(instance, path, buf, size, offset, fi->fh);
}

int HOOK(getattr)(const char *path, struct stat *stbuf) {
    return FN(getattr)(instance, path, stbuf);
}

#define OPHOOK(name) . name = HOOK(name)
struct fuse_operations operations = {
    OPHOOK(init),
    OPHOOK(open),
    OPHOOK(read),
    OPHOOK(getattr)
};

struct fuse_opt option_spec[] = {
    { "--device=%s", offsetof(struct fc_fuse_options, device), 1 },
    FUSE_OPT_END
};

int main(int argc, char *argv[]) {

    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    if (fuse_opt_parse(&args, &fc_fuse_options, option_spec, NULL)
        == -1) {
        return 1;
    }
    int ret = fuse_main(args.argc, args.argv, &operations, NULL);
    fuse_opt_free_args(&args);
    return ret;
}
