#include "../include/RBTree.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

RBTreeNode* nil=NULL;

RBTreeNode* getParent(RBTreeNode* node)
{
	return node->parent;
}

RBTreeNode* getLeft(RBTreeNode* node)
{
	return node->left;
}

RBTreeNode* getRight(RBTreeNode* node)
{
	return node->right;
}

void LeftRotate(RBTree* Tree,RBTreeNode* x)
{
	if (x->right!=nil)
	{
		RBTreeNode* y=getRight(x);
		x->right=y->left;
		if (y->left!=nil)
			y->left->parent=x;
		y->parent=x->parent;
		if (x->parent!=nil)
			Tree=&y;
		else if (x==getLeft(getParent(x)))
			x->parent->left=y;
		else
			x->parent->right=y;
		y->left=x;
		x->parent=y;
	}
}

void RightRotate(RBTree* Tree,RBTreeNode* x)
{
	if (x->left!=nil)
	{
		RBTreeNode* y=getLeft(x);
		x->left=y->right;
		if (y->right!=nil)
			y->right->parent=x;
		y->parent=x->parent;
		if (x->parent==nil)
			Tree=&y;
		else
			if (x==getLeft(getParent(x)))
				x->parent->left=y;
			else
				x->parent->right=y;
		y->right=x;
		x->parent=y;
	}
}

void InsertFixup(RBTree* Tree,RBTreeNode* node)
{
	RBTreeNode* y;
	while (getParent(node)->color==Red)
	{
		if (getParent(getParent(node))->left==getParent(node))
		{
			y=getParent(getParent(node))->right;
			if (y->color==Red) //case 1
			{
				y->color=Black;
				node->parent->color=Black;
				node->parent->parent->color=Red;
				node=node->parent->parent;
			}
			else
			{
				if (node==node->parent->right) //case 2
				{
					node=node->parent;
					LeftRotate(Tree,node);
				}
				node->parent->color=Black; //case 3
				node->parent->parent->color=Red;
				RightRotate(Tree,node->parent->parent);
			}
		}
		else
		{
			y=getParent(getParent(node))->left;
			if (y->color==Red)
			{
				y->color=Black;
				node->parent->color=Black;
				node->parent->parent->color=Red;
				node=node->parent->parent;
			}
			else
			{
				if (node==node->parent->left)
				{
					node=node->parent;
					RightRotate(Tree,node);
				}
				node->parent->color=Black;
				node->parent->parent->color=Red;
				LeftRotate(Tree,node->parent->parent);
			}
		}
	}
	(*Tree)->color=Black;
}

int Insert(RBTree* Tree,Student* Stu,SortMode mode)
{
    RBTreeNode *node,*p,*curNode;
    node=(RBTreeNode*)malloc(sizeof(RBTreeNode));
    if (node==NULL)
        return -1;  //error:get memory failed
    node->data=Stu;
    node->left=nil;
    node->right=nil;
    node->color=Red;
    curNode=*Tree;
    p=nil;
    while (curNode!=nil)
    {
        p=curNode;
        switch (mode)
        {
        case ID:
            if (Stu->ID <= p->data->ID)
                curNode=curNode->left;
            else if (Stu->ID > p->data->ID)
                curNode=curNode->right;
            else
                return -2;  //error:duplicate ID
            break;
        case Name:
            if (wcscmp(Stu->Name,p->data->Name)<=0)
                curNode=curNode->left;
            else
                curNode=curNode->right;
            break;
        };
    }
    if (p==nil)
        *Tree=node;
    else
    {
        switch (mode)
        {
        case ID:
            if (Stu->ID < p->data->ID)
                p->left=node;
            else if (Stu->ID > p->data->ID)
                p->right=node;
            else
                return -2;  //error:duplicate ID
            break;
        case Name:
            if (wcscmp(Stu->Name,p->data->Name)<=0)
                p->left=node;
            else
                p->right=node;
            break;
        };
    }

    node->parent=p;
    InsertFixup(Tree,node);
    return 0;
}

RBTreeNode* Successor(RBTree* Tree,RBTreeNode* node)
{
    if (node->right!=nil)
    {
        RBTreeNode* p=nil;
        RBTreeNode* q=node->right;
        while (p->left!=nil)
        {
            q=p;
            p=p->left;
        }
        return q;
    }
    else
    {
        RBTreeNode* y=node->parent;
        while (y!=nil && node==y->right)
        {
            node=y;
            y=y->parent;
        }
        return y;
    }
}

void DeleteFixup(RBTree* Tree,RBTreeNode* node)
{
    while (node!=*Tree && node->color==Black)
    {
        if (node==node->parent->left)
        {
            RBTreeNode* w=node->parent->right;  //brother node
            if (w->color==Red)
            {
                w->color=Black;
                node->parent->color=Red;
                LeftRotate(Tree,node->parent);
                w=node->parent->right;
            }
            if (w->left->color==Black && w->right->color==Black)    //case 2:both child are black
            {
                w->color=Red;
                node=node->parent;
            }
            else if (w->right->color==Black)    //case 3:left child is red,right child is black
            {
                w->color=Red;
                w->left->color=Black;
                RightRotate(Tree,w);
                w=node->parent->right;
            }
            w->color=node->parent->color;   //case 4:right child is red;
            node->parent->color=Black;
            w->right->color=Black;
            LeftRotate(Tree,node->parent);
            node=*Tree;
        }
        else
        {
            RBTreeNode* w=node->parent->left;
            if (w->color==Red)
            {
                w->color=Black;
                node->parent->color=Red;
                RightRotate(Tree,node->parent);
                w=node->parent->left;
            }
            if (w->left->color==Black && w->right->color==Black)
            {
                w->color=Red;
                node=node->parent;
            }
            else if (w->left->color==Black)
            {
                w->color=Red;
                w->right->color=Black;
                LeftRotate(Tree,w);
                w=node->parent->left;
            }
            w->color=node->parent->color;
            node->parent->color=Black;
            w->left->color=Black;
            RightRotate(Tree,node->parent);
            node=*Tree;
        }
    }
    node->color=Black;
}

void Delete(RBTree* Tree,RBTreeNode* node)
{
    RBTreeNode *x,*y;
    if (node->left==nil || node->right==nil)
        y=node;
    else
        y=Successor(Tree,node);
    if (y->left!=nil)
        x=y->left;
    else
        x=y->right;

    x->parent=y->parent;
    if (y->parent==nil)
        Tree=&x;
    else
    {
        if (y==y->parent->left)
            y->parent->left=x;
        else
            y->parent->right=x;
    }
    if (y!=node)
        node->data=y->data;
    if (y->color==Black)
        DeleteFixup(Tree,x);
}

RBTreeNode* SearchByID(RBTree Tree,unsigned int ID)
{
    if (Tree!=nil)
    {
        if (ID < Tree->data->ID)
            return SearchByID(Tree->left,ID);
        else if (ID > Tree->data->ID)
            return SearchByID(Tree->right,ID);
        else
            return Tree;
    }
    return nil;
}

int SearchByName(RBTree Tree,wchar_t* Name,RBTreeNode** ResultArray,unsigned int maxSize)
{
    unsigned int sum=0;
    if (Tree!=nil)
    {
        if (wcscmp(Name,Tree->data->Name)<0)
            return SearchByName(Tree->left,Name,ResultArray,maxSize);
        else if (wcscmp(Name,Tree->data->Name)>0)
            return SearchByName(Tree->right,Name,ResultArray,maxSize);
        else
        {
            do
            {
				if (sum<maxSize)
                	ResultArray[sum]=Tree;
               	sum++;
				Tree=Tree->left;
            }while (wcscmp(Name,Tree->data->Name)==0);
            return sum;
        }
    }
    return 0;
}




