#include "data_structures/array/array.h"
#include "utils/result_code.h"
#include <bits/types/struct_itimerspec.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_INITIAL_CAPACITY 4

ResultCode Array_Create(size_t item_size, Array **result) {
  if (result)
    *result = NULL;

  if (result == NULL) {
    return kNullParameter;
  }

  if (item_size == 0)
    return kInvalidArgument;

  if (*result != NULL)
    return kOutputPointerIsNotNull;

  Array *array = (Array *)malloc(sizeof(Array));
  if (array == NULL)
    return kFailedMemoryAllocation;

  array->size = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->item_size = item_size;

  if (array->capacity > 0 && item_size > SIZE_MAX / array->capacity) {
    free(array);
    return kArithmeticOverflow;
  }
  array->data = malloc(array->capacity * item_size);
  if (array->data == NULL) {
    free(array);
    return kFailedMemoryAllocation;
  }

  *result = array;
  return kSuccess;
}

void Array_Destroy(Array *self) {
  if (self == NULL)
    return;
  if (self->data != NULL) {
    free(self->data);
    self->data = NULL;
  };

  self->size = 0;
  self->capacity = 0;
  self->item_size = 0;

  free(self);
}
