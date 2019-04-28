/*
fscompat
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

#ifndef __FC_CONFIG_H__
#define __FC_CONFIG_H__

#include <stdlib.h>
#include <unistd.h>

void *fc_malloc(size_t size);
void fc_free(void *ptr);
struct fc_state *fc_state_init();
void fc_state_deinit(struct fc_state *state);
off_t fc_lseek(struct fc_state *state, off_t offset, int whence);
ssize_t fc_read(struct fc_state *state, void *buf, size_t count);
ssize_t fc_write(struct fc_state *state,void *buf, size_t count);

#endif
