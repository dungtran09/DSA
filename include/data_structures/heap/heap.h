#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "../../utils/comparators.h"
#include "../../utils/result_code.h"

struct Heap_t;
typedef struct Heap_t Heap;

ResultCode Heap_Create(size_t size, sort_strategy, Heap **);
ResultCode Heap_Insert(Heap *, void *);
ResultCode Heap_Resize(Heap *, size_t);
ResultCode Heap_Reproiritize(Heap *, void *);
ResultCode Heap_Delete(Heap *, void *);
ResultCode Heap_Extract(Heap *, void **);
ResultCode Heap_Peek(Heap *, void **);

size_t Heap_Size(Heap *);
size_t Heap_MaxSize(Heap *);
bool Heap_Exists(Heap *, void *);
bool Heap_IsEmpty(Heap *);
void Heap_Destroy(Heap *, freer);
