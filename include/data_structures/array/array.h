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
ResultCode Array_Create(size_t item_size, Array **);
void Array_Destroy(Array *);
void Array_Clear(Array *);

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
ResultCode Array_Get(const Array *, size_t index, const void **out);
ResultCode Array_Set(Array *, size_t index, const void *value);

// Unsafe (fast)
void *Array_GetUnchecked(const Array *, size_t index);

// ===== MODIFIERS =====
ResultCode Array_PushBack(Array *, const void *);
ResultCode Array_PopBack(Array *);

// Insert value at index
// Valid range: 0 <= index <= size
// index == size => equivalent to PushBack
// index > size  => return RESULT_OUT_OF_RANGE
ResultCode Array_Insert(Array *, size_t index, const void *);

ResultCode Array_Remove(Array *, size_t index);

#endif
