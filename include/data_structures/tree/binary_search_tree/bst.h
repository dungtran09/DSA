#pragma once

#include "common/comparator.h"
#include "utils/result_code.h"
#include <stddef.h>

typedef struct BSTNode {
  struct BSTNode *left;
  struct BSTNode *right;
  struct BSTNode *parent;
  void *payload;
  size_t size; // order-statistic
} BSTNode;

typedef struct {
  comparator cp;
  BSTNode *root;
  size_t n;
} BST;

ResultCode BST_Insert(BST *, void *);
ResultCode BST_Delete(BST *, const void *, void **);
ResultCode BST_Search(const BST *, const void *, void **);

ResultCode BST_Min(const BST *, void **);
ResultCode BST_Max(const BST *, void **);
ResultCode BST_Rank(const BST *, const void *, size_t *);
ResultCode BST_Select(const BST *, size_t, void **);
