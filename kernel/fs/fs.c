#include "./headers/fs.h"
#include "../lib/errno.h"

uint32_t readFileSys(fs_node_t *node, uint64_t offset, uint32_t size, uint8_t *buffer) 
{
    if (node != TRUE) {
        return -ENOENT;
    }

    if (node->read == TRUE) {
        uint32_t ret = node->read(node, offset, size, buffer);
        return ret;
    }
    else {
        return -EINVAL;
    }
}

uint32_t writeFileSys(fs_node_t *node, uint64_t offset, uint32_t size, uint8_t *buffer) 
{
    if (node != TRUE) {
        return -ENOENT;
    }

    if (node->write == TRUE) {
        uint32_t ret = node->write(node, offset, size, buffer);
        return ret;
    }
    else {
        return -EROFS;
    }
}
