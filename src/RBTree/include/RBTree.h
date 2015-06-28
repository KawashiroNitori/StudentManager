#ifndef __RBTREE_H__
#define __RBTREE_H__
#include "../../Student/include/Student.h"

typedef enum ColorType
{
	Red,Black
}ColorType;

typedef enum SortMode
{
    IDSort,NameSort
}SortMode;

typedef struct RBTreeNode
{
	struct RBTreeNode* parent;
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	struct Student* data;
	struct DupNameList* dup;
	ColorType color;
} RBTreeNode,*RBTree;

typedef struct DupNameList
{
    struct RBTreeNode* node;
    struct DupNameList* Next;
} DupNameList;

RBTreeNode* nil;

void LeftRotate(RBTree* Tree,RBTreeNode* x);

void RightRotate(RBTree* Tree,RBTreeNode* x);

void InsertFixup(RBTree* Tree,RBTreeNode* node);

int Insert(RBTree* Tree,Student* data,SortMode mode);

RBTreeNode* Successor(RBTreeNode* node);

void DeleteFixup(RBTree* Tree,RBTreeNode* node,RBTreeNode* x);

void Delete(RBTree* Tree,RBTreeNode* node);

RBTreeNode* SearchByID(RBTree Tree,unsigned int ID);

int SearchByName(RBTree Tree,wchar_t* Name,RBTreeNode** ResultArray,unsigned int maxSize);

void InOrderTranverse(RBTree Tree,void (*visitor)(RBTreeNode* node));

void DestroyRBTree(RBTree Tree);

void PrintNode(RBTreeNode* node);

#endif








