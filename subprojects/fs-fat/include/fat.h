/* SPDX-License-Identifier: CC0
fscompat FAT driver  
Written in 2019 by fscompat Developers

To the extent possible under law, the author(s) have dedicated all
copyright and related and neighboring rights to this software to the
public domain worldwide. This software is distributed without any
warranty.

You should have received a copy of the CC0 Public Domain Dedication along
with this software. If not, see
<http://creativecommons.org/publicdomain/zero/1.0/>.

The full text of the CC0 Public Domain Dedication is contained in the
COPYING file.
*/

#ifndef __FSCOMPAT_FAT__
#define __FSCOMPAT_FAT__

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

struct fc_fat_instance;
struct fc_fat_instance *fc_fat_init();
void fc_fat_deinit(struct fc_fat_instance *instance);
int fc_fat_open(struct fc_fat_instance *instance, const char *path,
    int flags);
int fc_fat_read(struct fc_fat_instance *instance, const char *path,
    char *buf, size_t size, off_t offset, int fh);
int fc_fat_getattr(struct fc_fat_instance *instance, const char *path,
    struct stat *stbuf);

#endif
