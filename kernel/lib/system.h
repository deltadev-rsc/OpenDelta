#ifndef SYSTEM_H
#define SYSTEM_H

#include "./time.h"
#include "./types.h"
#include "./string.h"

/*---types---*/
typedef signed int pid_t;
typedef unsigned int user_t;
typedef unsigned int status_t;

/*---macros---*/
#define KERNEL_STACK_SIZE 0x8000
#define NUMSIGNS 38 // numder of signals
#define USER_ROOT_UID (user_t)0
#define IRQ_OFF { asm volatile ("cli"); }
#define PAUSE { asm volatile ("hlt"); }

/*---structures---*/
typedef struct page {
    unsigned int present:1;
    unsigned int rw:1;
    unsigned int user:1;
    unsigned int write_through:1;
    unsigned int cache_disable:1;
    unsigned int accessed:1;
    unsigned int dirty:1;
    unsigned int pat:1;
    unsigned int global:1;
    unsigned int unused:3;
    unsigned int frame:20;
} __attribute__((packed)) page_t;

typedef struct PageTable {
    page_t pages[1024];
} page_table_t;

typedef struct PageDir {
    uintptr_t physical_tables[1024];
    page_table_t *tables[1024];
    uintptr_t physical_address;
    int32_t ref_count;
} page_dir_t;

typedef struct thread {
    uintptr_t esp;
    uintptr_t ebp;
    uintptr_t eip;
    uint8_t fpu_enabled;
    uint8_t fp_regs[512];
    uint8_t padding[32];
    page_dir_t *page_dir;
} thread_t;

typedef struct image {
    size_t size;
    uintptr_t entry;
    uintptr_t heap;
    uintptr_t head_actual;
    uintptr_t stack;
    uintptr_t user_stack;
    uintptr_t start;
    uintptr_t shm_heap;
    volatile int lock[2];
} image_t;



#endif 
