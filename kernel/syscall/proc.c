#include "../lib/system.h"
#include "../mem/header/memory.h"
#include "../lib/stdbase.h" 

void initProcTree(void) {
    return;
}

process_t *spawnInit(void) {
    process_t *init = malloc(sizeof(process_t));
    return init;
}

process_t *spawnKIdle(void) {
    process_t *idle = malloc(sizeof(process_t));
    memset(idle, 0x00, sizeof(process_t));
    return idle;
}
