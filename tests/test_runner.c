#include <stdio.h>
void test_Array_Destroy_normal();
void test_Array_Destroy_nullInput();

void test_Array_Create_success();
void test_Array_Create_invalid_item_size();
void test_Array_Create_null_out();

int main(void) {
  printf("=== Running Array Tests ===\n");

  test_Array_Destroy_normal();
  test_Array_Destroy_nullInput();

  test_Array_Create_success();
  test_Array_Create_invalid_item_size();
  test_Array_Create_null_out();

  printf("=== All TESTS PASSED ===\n");
  return 0;
}
