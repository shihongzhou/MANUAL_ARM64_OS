// fs/ext2.h
#ifndef EXT2_H
#define EXT2_H

#include <stdint.h>

#define EXT2_SUPER_MAGIC 0xEF53

typedef struct {
    uint32_t inode_count;
    uint32_t block_count;
    uint32_t reserved_block_count;
    uint32_t free_block_count;
    uint32_t free_inode_count;
    uint32_t first_data_block;
    uint32_t log_block_size;
    // 更多字段...
} ext2_superblock_t;

typedef struct {
    uint16_t mode;
    uint16_t uid;
    uint32_t size;
    uint32_t atime;
    uint32_t ctime;
    uint32_t mtime;
    uint32_t dtime;
    uint16_t gid;
    uint16_t links_count;
    uint32_t blocks;
    uint32_t flags;
    // 更多字段...
} ext2_inode_t;

// 函数原型
void ext2_init(void);
int ext2_create(const char *filename);
int ext2_read(const char *filename, char *buffer, uint32_t size);
int ext2_write(const char *filename, const char *buffer, uint32_t size);

#endif
