#pragma once
#include "utils/result_code.h"
#include <common/comparator.h>
#include <stddef.h>

typedef enum { BLACK, RED } Color;

typedef struct RBNode {
  struct RBNode *left;
  struct RBNode *right;
  struct RBNode *parent;
  void *payload;
  size_t size;
  Color color;
} RBNode;

typedef struct {
  comparator cp;
  RBNode *root;
  size_t n;
} RBTree;

ResultCode RBTree_Insert(RBTree *, void *);
ResultCode RBTree_Delete(RBTree *, const void *, void **);
