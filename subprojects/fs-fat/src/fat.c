/*
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

#include <fscompat.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <fat.h>

struct fc_fat_instance {
    struct fc_state *state;

    struct {
        uint8_t jump[3];
        uint8_t oem[8];
        uint16_t bytes_per_sector;
        uint8_t sectors_per_cluster;
        uint16_t reserved_sectors;
        uint8_t fats;
        uint16_t directory_entries;
        uint16_t total_sectors;
        uint8_t media_descriptor;
        uint16_t sectors_per_fat;
        uint16_t sectors_per_track;
        uint16_t heads;
        uint32_t hidden_sectors;
        uint32_t large_sector_count;
    } __attribute__((packed)) bpb;
    union {
        struct {
            uint32_t sectors_per_fat;
            uint16_t flags;
            uint16_t version;
            uint32_t root_cluster;
            uint16_t fsinfo_sector;
            uint16_t backup_sector;
            uint8_t zero[12];
            uint8_t drive_number;
            uint8_t nt_flags;
            uint8_t signature;
            uint32_t volume_id;
            uint8_t volume_label[11];
            uint64_t system_identifier;
            uint8_t boot_code[420];
            uint16_t bootable_signature;
        } __attribute__((packed)) fat32;
        struct {
            uint8_t drive_number;
            uint8_t nt_flags;
            uint8_t signature;
            uint32_t volume_id;
            uint8_t volume_label[11];
            uint64_t system_identifier;
            uint8_t boot_code[448];
            uint16_t bootable_signature;
        } __attribute__((packed)) fat16;
    } ebpb;

    uint32_t total_sectors;
    uint32_t sectors_per_fat;
    uint32_t root_dir_sectors;
    uint32_t first_data_sector;
    uint32_t first_root_dir_sector;
    uint32_t first_fat_sector;
    uint32_t data_sectors;
    uint32_t total_clusters;

    enum {
        TYPE_F12,
        TYPE_F16,
        TYPE_F32,
        TYPE_VFAT
    } type;
};

typedef struct fc_fat_instance *ins;

#define S (instance->state)
#define SECTOR_OFFSET(sector) (instance->bpb.bytes_per_sector * (sector))
#define CLUSTER_OFFSET(cluster) SECTOR_OFFSET( \
    instance->bpb.sectors_per_cluster * (cluster) \
)

ins fc_fat_init() {
    ins instance = fc_malloc(sizeof *instance);
    S = fc_state_init();
    // Read BPB
    fc_lseek(S, 0, SEEK_SET);
    fc_read(S, &instance->bpb, sizeof instance->bpb);
    // Read EBPB
    fc_read(S, &instance->ebpb, sizeof instance->ebpb);
    // Calculate parameters
    instance->total_sectors = instance->bpb.total_sectors;
    if (instance->total_sectors == 0) {
        instance->total_sectors = instance->bpb.large_sector_count;
    }
    instance->sectors_per_fat = instance->bpb.sectors_per_fat;
    if (instance->sectors_per_fat == 0) {
        instance->sectors_per_fat = instance->ebpb.fat32.sectors_per_fat;
    }
    instance->root_dir_sectors = ((instance->bpb.directory_entries * 32)
            + (instance->bpb.bytes_per_sector - 1))
        / instance->bpb.bytes_per_sector;
    instance->first_data_sector = instance->bpb.reserved_sectors +
        (instance->bpb.fats * instance->sectors_per_fat)
        + instance->root_dir_sectors;
    instance->first_root_dir_sector = instance->first_data_sector
        - instance->root_dir_sectors;
    instance->first_fat_sector = instance->bpb.reserved_sectors;
    instance->data_sectors = instance->total_sectors
        - (instance->bpb.reserved_sectors
            + (instance->bpb.fats * instance->sectors_per_fat)
            + instance->root_dir_sectors);
    instance->total_clusters = instance->data_sectors
        / instance->bpb.sectors_per_cluster;
    if (instance->total_clusters < 4085) {
        instance->type = TYPE_F12;
    } else if (instance->total_clusters < 65525) {
        instance->type = TYPE_F16;
    } else if (instance->total_clusters < 268435445) {
        instance->type = TYPE_F32;
    } else {
        instance->type = TYPE_VFAT;
    }
    return instance;
}

void fc_fat_deinit(ins instance) {
    fc_state_deinit(S);
    fc_free(instance);
}

int fc_fat_open(ins instance, const char *path, int flags) {
    return -ENOENT;
}

int fc_fat_read(ins instance, const char *path, char *buf, size_t size,
    off_t offset, int fh) {
    return -ENOENT;
}

int fc_fat_getattr(ins instance, const char *path, struct stat *stbuf) {
    return -ENOENT;
}
