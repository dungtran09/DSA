#include <stdio.h>
void test_Array_Destroy_normal();
void test_Array_Destroy_nullInput();

int main(void) {
  printf("=== Running Array Tests ===\n");
  test_Array_Destroy_normal();
  test_Array_Destroy_nullInput();

  printf("=== All TESTS PASSED ===\n");
  return 0;
}
