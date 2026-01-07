#pragma once

#include <stdbool.h>

#include "utils/result_code.h"

struct Stack_t;
typedef struct Stack_t Stack;

ResultCode Stack_Create(Stack **);
ResultCode Stack_Push(Stack *, void *);
ResultCode Stack_Pop(Stack *, void **);
bool Stack_IsEmpty(Stack *);
void Stack_Destroy(Stack *);
