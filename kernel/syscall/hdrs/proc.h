#ifndef PROC_H
#define PROC_H

#include "../../lib/system.h"
#include "../../lib/stdbase.h"

void initProcTree(void);
sys_process_t *spawnInit(void);
sys_process_t *spawnKIdle(void);

#endif 
