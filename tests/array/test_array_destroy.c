#include "data_structures/array/array.h"
#include "utils/result_code.h"
#include <assert.h>
#include <stdio.h>

void test_Array_Destroy_normal() {

  Array *arr = NULL;
  ResultCode result = Array_Create(sizeof(int), &arr);
  assert(result == kSuccess);
  assert(arr != NULL);
  Array_Destroy(arr);

  printf("[PASS]: Array_Destroy_normal\n");
}

void test_Array_Destroy_nullInput() {
  Array_Destroy(NULL);
  printf("[PASS]: Array_Destroy_nullInput\n");
}
