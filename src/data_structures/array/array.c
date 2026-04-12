#include "data_structures/array/array.h"
#include "utils/result_code.h"
#include <bits/types/struct_itimerspec.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_INITIAL_CAPACITY 4

/* ============================================================================
 * INTERNAL HELPER FUNCTIONS (Private - not exposed in header)
 * ============================================================================
 */
/*
@brief Validates if the given index is within bounds
* @param arr Array to check
* @param index Index to validate
* @return KSuccess if valid , appropriate erorr code otherwise
*
Case hander:
* - arr == NULL -> kNullParameter
* - index >= size -> kInvalidIndex
* - otherwise -> kSuccess
*/

static ResultCode _check_index(const Array *arr, size_t index) {
  if (arr == NULL) {
    return kNullParameter;
  }
  if (index >= arr->size) {
    return kInvalidIndex;
  }
  return kSuccess;
}

/* ============================================================================
 * LIFECYCLE FUNCTIONS
 * ============================================================================
 */

/**
 * Array_Create - Creates a new dynamic array
 *
 * Implementation flow:
 * 1. Set output pointer to NULL (safety first)
 * 2. Validate all input parameters
 * 3. Check output pointer is not pointing to valid memory (prevent leak)
 * 4. Allocate Array struct
 * 5. Initialize struct fields with default values
 * 6. Check for overflow before allocating data
 * 7. Allocate data buffer with initial capacity
 * 8. Assign result and return success
 *
 * @param item_size Size of each element in bytes
 * @param result Output pointer to receive the new Array
 * @return Result code
 */

ResultCode Array_Create(size_t item_size, Array **result) {
  /* Step 1: Always set output to NULL first */
  if (result)
    *result = NULL;

  /* Step 2: Validate output parameter */
  if (result == NULL) {
    return kNullParameter;
  }

  /* Step 3: Validate item_size */
  if (item_size == 0)
    return kInvalidArgument;

  /* Step 4: Check output pointer is not already pointing to valid memory
   * This prevents memory leaks if caller passes an already-allocated pointer
   */
  if (*result != NULL)
    return kOutputPointerIsNotNull;

  /* Step 5: Allocate Array struct */
  Array *array = (Array *)malloc(sizeof(Array));
  if (array == NULL)
    return kFailedMemoryAllocation;

  /* Step 6: Initialize struct fields */
  array->size = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->item_size = item_size;

  /* Step 7: Check for overflow before allocating data
   * Example: capacity=16, item_size=1GB -> 16GB might overflow SIZE_MAX on
   * 32-bit Formula: item_size > SIZE_MAX / capacity -> overflow will occur
   */
  if (array->capacity > 0 && item_size > SIZE_MAX / array->capacity) {
    free(array);
    return kArithmeticOverflow;
  }

  /* Step 8: Allocate data buffer */
  array->data = malloc(array->capacity * item_size);
  if (array->data == NULL) {
    free(array);
    return kFailedMemoryAllocation;
  }

  /* Step 9: Success - set output and return */
  *result = array;
  return kSuccess;
}

/**
 * Array_Destroy - Frees all memory associated with the array
 *
 * Implementation flow:
 * 1. Check if array is NULL (silently return)
 * 2. Free the data buffer if it exists
 * 3. Reset all fields to zero (helps detect use-after-free bugs)
 * 4. Free the Array struct itself
 *
 * @param arr Array to destroy (can be NULL)
 */
void Array_Destroy(Array *self) {
  /* Step 1: Handle NULL gracefully */
  if (self == NULL)
    return;

  /* Step 2: Free data buffer if allocated */
  if (self->data != NULL) {
    free(self->data);
    self->data = NULL; /* Prevent dangling pointer */
  };

  /* Step 3: Reset fields (helps debug use-after-free issues) */
  self->size = 0;
  self->capacity = 0;
  self->item_size = 0;

  /* Step 4: Free the struct itself */
  free(self);
}

/**
 * Array_Clear - Removes all elements but keeps the capacity
 *
 * Simply resets size to 0. The data buffer remains allocated
 * to avoid reallocation when elements are added again.
 *
 * @param arr Array to clear
 */
void Array_Clear(Array *arr) {
  if (arr != NULL) {
    arr->size = 0;
  }
}

/* ============================================================================
 * CAPACITY FUNCTIONS
 * ============================================================================
 */

/**
 * Array_Size - Returns the number of elements currently in the array
 * Returns 0 if array is NULL (safe behavior)
 */

size_t Array_Size(const Array *arr) { return arr == NULL ? 0 : arr->size; }

/**
 * Array_Capacity - Returns the current capacity (maximum elements before
 * reallocation) Returns 0 if array is NULL
 */
size_t Array_Capacity(const Array *arr) {
  return arr == NULL ? 0 : arr->capacity;
}

/**
 * Array_IsEmpty - Checks if the array contains any elements
 * Returns true if array is NULL or empty
 */

bool Array_IsEmpty(const Array *arr) {
  return arr == NULL ? true : arr->size == 0;
}
