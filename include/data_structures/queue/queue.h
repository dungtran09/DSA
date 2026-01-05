#pragma once

#include <stdbool.h>

#include "../../utils/result_code.h"

struct Queue_t;
typedef struct Queue_t Queue;

ResultCode Queue_Create(Queue **);
ResultCode Queue_Enqueue(Queue *, void *);
ResultCode Queue_Dequeue(Queue *, void **);
bool Queue_IsEmpty(Queue *);
void Queue_Destroy(Queue *);
