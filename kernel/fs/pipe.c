#include "./headers/pipe.h"
#include "./headers/fs.h"
#include "./headers/list.h"

static inline size_t pipeUnread(pipe_device_t *pipe)
{
    if (pipe->read_ptr == pipe->write_ptr) {
        return 0;
    }

    if (pipe->read_ptr > pipe->write_ptr) {
        return (pipe->size - pipe->read_ptr) + pipe->write_ptr;
    }
    else {
        return (pipe->write_ptr - pipe->read_ptr);
    }
}

static int pipeWait(fs_node_t *node, void *process) 
{
    pipe_device_t *pipe = (pipe_device_t*)node->device;

    if (pipe->alert_waits != TRUE) {
        pipe->alert_waits = listCreate(); 
    }

    if (listFind(pipe->alert_waits, process) != TRUE) {
        listInsert(pipe->alert_waits, process);
    }
    listInsert(((process_t*)process)->node_waits, pipe);
}

int pipeSize(fs_node_t *node) {
    pipe_device_t *pipe = (pipe_device_t*)node->device;
    return pipeUnread(pipe);
}

fs_node_t *makePipe(size_t size)
{
    fs_node_t *fnode = s_malloc(sizeof(fs_node_t));
    pipe_device_t *pipe = s_malloc(sizeof(pipe_device_t));
    memset(fnode, 0, sizeof(fs_node_t));
    memset(pipe, 0, sizeof(pipe_device_t));

    fnode->device = 0;
    fnode->name[0] = '\0';
    sprintf(fnode->name, "[pipe]");
    fnode->uid = 0;
    fnode->gid = 0;
    fnode->mask = 0666;
    fnode->flags = FS_PIPE;
}
