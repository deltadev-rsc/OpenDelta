#ifndef BOOT_PARAMS_H
#define BOOT_PARAMS_H

#pragma once

#include "./types.h"

typedef struct {
    uint64_t begin, length;
    uint32_t type;
    uint32_t ACPI;
} MemoryRegion;

typedef struct {
    int region_count;
    MemoryRegion* regions;
} MemoryInfo;

typedef struct {
    MemoryInfo memory;
    uint8_t boot_device;
} BootParams;

#endif 
