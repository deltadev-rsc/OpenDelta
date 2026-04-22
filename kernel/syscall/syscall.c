#include "../lib/syscall.h"
#include "../lib/screen.h"
#include "../lib/system.h"
#include "../lib/stdbase.h"

static sys_process_t *current_process = {0};

static int __attribute((noreturn)) sysExit(int retval) {
    taskExit((retval & 0xFF) << 8);
    for (;;) { ; }
}

static int sysGeteuid(void) {
    return current_process->user;
}

static int sysOpen(const char *file, int flags, int mode) {
    int fd = 0;
    return fd;
}

static int sysRead(int fd, char *ptr, int len) {
    return fd;
}

static int sysWrite(int fd, char *ptr, int len) {
    return fd;
}

static int sysClose(int fd) {
    return 0;
}

static int (*syscalls[]) = {
    [SYS_EXT] = sysExit,
    [SYS_GETEUID] = sysGeteuid,
    [SYS_OPEN] = sysOpen,
    [SYS_READ] = sysRead,
    [SYS_WRITE] = sysWrite,
    [SYS_CLOSE] = sysClose,
};

uint32_t num_syscalls = sizeof(syscalls) / sizeof(*syscalls);

void syscallInstall(void)
{
    char syscallAscii[2] = "";
    int_to_ascii(num_syscalls, syscallAscii);
    prints("\n[info]: [initializing syscall table with ]", WHITE);
    prints(syscallAscii, 0x08);
    prints(" functions\n", WHITE);
}
