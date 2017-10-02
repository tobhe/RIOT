/*
 * Copyright (C) 2017 Tobias Heider <heidert@nm.ifi.lmu.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
/**
 * @defgroup    sys_memarray memory array allocator
 * @ingroup     sys
 * @brief       memory array allocator
 * @{
 *
 * @brief       pseudo dynamic allocation in static memory arrays
 * @author      Tobias Heider <heidert@nm.ifi.lmu.de>
 */

#ifndef MEMARRAY_H
#define MEMARRAY_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *first_free; /**< head of the free list */
} memarray_t;

/**
 * Initialize memory
 */
#define MEMARRAY(name, size, num)                                         \
    static uint8_t _data_ ## name[num * size];                            \
    static memarray_t name = { .first_free = _data_ ## name };

void memarray_init(memarray_t *mem, size_t num, size_t size);

void *memarray_alloc(memarray_t *mem);

void memarray_free(memarray_t *mem, void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* MEMARRAY_H */
