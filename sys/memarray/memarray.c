/*
 * Copyright (C) 2017 Tobias Heider <heidert@nm.ifi.lmu.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "memarray.h"
#include "string.h"

void *memarray_alloc(memarray_t *mem) {
  if (mem->first_free == NULL) {
    return NULL;
  }
  void *free = mem->first_free;
  mem->first_free = *((void **)mem->first_free);
  return free;
}

void memarray_init(memarray_t *mem) {
  for (size_t i = 0; i < mem->count-1; i++) {
    void *next = ((char *)mem->data) + ((i + 1) * mem->size);
    memcpy(((char *)mem->data) + (i * mem->size), &next, sizeof(void *));
  }
}

uint8_t memarray_free(memarray_t *mem, void *ptr) {
  char *iter = mem->data;
  for (size_t i = 0; i < mem->count; i++) {
    if (iter == ptr) {
      memcpy(iter, &mem->first_free, sizeof(void *));
      mem->first_free = iter;
      return 0;
    }
    iter += mem->size;
  }
  return 1;
}
