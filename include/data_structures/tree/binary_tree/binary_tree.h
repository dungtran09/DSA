#pragma once

#include <common/freer.h>
#include <common/visitor.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct BinaryTreeNode {
  struct BinaryTreeNode *left;
  struct BinaryTreeNode *right;
  struct BinaryTreeNode *parent;
  void *payload;
} BinaryTreeNode;

typedef struct {
  BinaryTreeNode *root;
  size_t n;
} BinaryTree;

BinaryTree *BinaryTree_Create(void);
void BinaryTree_Destroy(BinaryTree *, freer);

void BinaryTree_PreOrder(BinaryTree *, item_handler);
void BinaryTree_InOrder(BinaryTree *, item_handler);
void BinaryTree_PostOrder(BinaryTree *, item_handler);
