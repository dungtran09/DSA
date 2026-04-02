#ifndef ARRAY_H
#define ARRAY_H

#include "utils/result_code.h"
#include <stdbool.h>
#include <stddef.h>

// ==== STRUCT === //
typedef struct {
  size_t size;
  size_t capacity;
  size_t item_size;
  void *data;
} Array;

// ===== LIFECYCLE =====
Array *Array_Create(size_t item_size);
void Array_Destroy(Array *);

// ===== CAPACITY =====
size_t Array_Size(const Array *);
size_t Array_Capacity(const Array *);
bool Array_IsEmpty(const Array *);

ResultCode Array_Reserve(Array *, size_t new_capacity);
ResultCode Array_ShrinkToFit(Array *);

// ===== DATA ACCESS =====
void *Array_Data(Array *);
const void *Array_DataConst(const Array *);

// Safe access
ResultCode Array_Get(const Array *, size_t index, void **out);
ResultCode Array_Set(Array *, size_t index, const void *value);

// Unsafe (fast)
void *Array_GetUnchecked(const Array *, size_t index);

// ===== MODIFIERS =====
ResultCode Array_PushBack(Array *, const void *);
ResultCode Array_PopBack(Array *);

ResultCode Array_Insert(Array *, size_t index, const void *);
ResultCode Array_Remove(Array *, size_t index);

#endif
