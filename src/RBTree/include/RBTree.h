#ifndef __RBTREE_H__
#define __RBTREE_H__
#include "../../Student/include/Student.h"
#include <stdio.h>

typedef enum ColorType
{
	Red,Black
}ColorType;

typedef struct RBTreeNode
{
	struct RBTreeNode* parent;
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	struct Student* data;
	ColorType color;
} RBTreeNode,*RBTree;

RBTreeNode* nil=NULL;

RBTreeNode* getParent(RBTreeNode* node);

RBTreeNode* getLeft(RBTreeNode* node);

RBTreeNode* getRight(RBTreeNode* node);

void LeftRotate(RBTree* Tree,RBTreeNode* x);

void RightRotate(RBTree* Tree,RBTreeNode* x);

void InsertFixup(RBTree* Tree,RBTreeNode* node);

void Insert(RBTree* Tree,Student* data);

#endif








