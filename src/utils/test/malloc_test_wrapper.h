#pragma once

#include <stddef.h>

#if defined(NDEBUG)
#define FAILED_MALLOC_TEST(code_block)                                         \
  {                                                                            \
    code_block;                                                                \
  }
#else
#define FAILED_MALLOC_TEST(code_block)                                         \
  {                                                                            \
    InterceptMalloc();                                                         \
    code_block;                                                                \
    CU_ASSERT_EQUAL(1, MallocInterceptCount());                                \
    ResetMalloc();                                                             \
  }
#endif

void InterceptMalloc(void);
size_t MallocInterceptCount(void);
void ResetMalloc(void);
