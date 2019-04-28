/*
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

#ifndef __FSCOMPAT_FUSED_SHARED__
#define __FSCOMPAT_FUSED_SHARED__

struct fc_fuse_options {
    const char *device;
};

extern struct fc_fuse_options fc_fuse_options;

#endif
