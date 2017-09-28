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
    size_t size;        /**< size of single array element*/
    size_t count;       /**< count of elements in array */
    void *first_free;   /**< first free element */
    void *data;         /**< static memory pool */
} memarray_t;

/**
 * Initialize memory
 */
#define MEMARRAY(name, structure, num)                                         \
    static structure _data_ ## name[num];                                      \
    static memarray_t name = { .size = sizeof(structure),                      \
                               .count = num,                                   \
                               .first_free = _data_ ## name,                   \
                               .data = _data_ ## name };

void memarray_init(memarray_t *mem);

void *memarray_alloc(memarray_t *mem);

uint8_t memarray_free(memarray_t *mem, void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* MEMARRAY_H */
