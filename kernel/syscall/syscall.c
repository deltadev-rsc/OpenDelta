#include "../lib/syscall.h"
#include "../lib/screen.h"
#include "../lib/system.h"

static sys_process_t *current_process = {0};

static int __attribute((noreturn)) sys_exit(int retval);
