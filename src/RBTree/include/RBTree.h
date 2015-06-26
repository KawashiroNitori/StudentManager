#ifndef __RBTREE_H__
#define __RBTREE_H__
#include "../../Student/include/Student.h"

typedef enum ColorType
{
	Red,Black
}ColorType;

typedef enum SortMode
{
    ID,Name
}SortMode;

typedef struct RBTreeNode
{
	struct RBTreeNode* parent;
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	struct Student* data;
	ColorType color;
} RBTreeNode,*RBTree;

RBTreeNode* nil;

RBTreeNode* getParent(RBTreeNode* node);

RBTreeNode* getLeft(RBTreeNode* node);

RBTreeNode* getRight(RBTreeNode* node);

void LeftRotate(RBTree* Tree,RBTreeNode* x);

void RightRotate(RBTree* Tree,RBTreeNode* x);

void InsertFixup(RBTree* Tree,RBTreeNode* node);

int Insert(RBTree* Tree,Student* data,SortMode mode);

RBTreeNode* Successor(RBTree* Tree,RBTreeNode* node);

void DeleteFixup(RBTree* Tree,RBTreeNode* node);

void Delete(RBTree* Tree,RBTreeNode* node);

RBTreeNode* SearchByID(RBTree Tree,unsigned int ID);

int SearchByName(RBTree Tree,wchar_t* Name,RBTreeNode** ResultArray,unsigned int maxSize);

#endif








