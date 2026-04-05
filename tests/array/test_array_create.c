#include <assert.h>
#include <stdio.h>

#include "data_structures/array/array.h"
#include "utils/result_code.h"

void test_Array_Create_success() {
  Array *arr = NULL;

  ResultCode rc = Array_Create(sizeof(int), &arr);

  assert(rc == kSuccess);
  assert(arr != NULL);
  assert(arr->size == 0);
  assert(arr->capacity > 0);
  assert(arr->item_size == sizeof(int));
  assert(arr->data != NULL);

  printf("[PASS]: Array_Create_success\n");

  Array_Destroy(arr);
}

void test_Array_Create_invalid_item_size() {
  Array *arr = NULL;

  ResultCode rc = Array_Create(0, &arr);

  assert(rc == kInvalidArgument);
  assert(arr == NULL);

  printf("[PASS]: Array_Create_invalid_item_size\n");
}

void test_Array_Create_null_out() {
  ResultCode rc = Array_Create(sizeof(int), NULL);

  assert(rc == kNullParameter);

  printf("[PASS]: Array_Create_null_out\n");
}
