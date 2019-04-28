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

#include <fscompat.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <fused-shared.h>

#ifndef O_DIRECT
#define O_DIRECT 0
#endif

struct fc_state {
    int fd;
};

void *fc_malloc(size_t size) {
    return malloc(size);
}

void fc_free(void *ptr) {
    free(ptr);
}

struct fc_state *fc_state_init() {
    struct fc_state *state = (struct fc_state *) malloc(sizeof *state);
    state->fd = open(fc_fuse_options.device, O_DIRECT);
    return state;
}

void fc_state_deinit(struct fc_state *state) {
    close(state->fd);
    free(state);
}

off_t fc_lseek(struct fc_state *state, off_t offset, int whence) {
    return lseek(state->fd, offset, whence);
}

ssize_t fc_read(struct fc_state *state, void *buf, size_t count) {
    return read(state->fd, buf, count);
}

ssize_t fc_write(struct fc_state *state, void *buf, size_t count) {
    return write(state->fd, buf, count);
}
