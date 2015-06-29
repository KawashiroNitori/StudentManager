#include "../include/RBTree.h"
#include "../../FileIO/include/FileIO.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

RBTreeNode* nil=NULL;

void LeftRotate(RBTree* Tree,RBTreeNode* x)
{
	RBTreeNode *y;

	y = x->right;
	x->right = y->left;
	if (y->left != nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil) {
		*Tree = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}

void RightRotate(RBTree* Tree,RBTreeNode* x)
{
	RBTreeNode *y;

	y = x->left;

	x->left = y->right;
	if (y->right != nil) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nil) {
		*Tree = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}

	y->right = x;
	x->parent = y;
}

void InsertFixup(RBTree* Tree,RBTreeNode* node)
{
    RBTreeNode* Father,*GrandParent,*Uncle;
    while ((Father=node->parent)!=nil && Father->color==Red)
    {
        GrandParent=Father->parent;
        if (Father==GrandParent->left)
        {
            Uncle=GrandParent->right;
            if (Uncle!=nil && Uncle->color==Red)
            {
                GrandParent->color=Red;
                Father->color=Black;
                Uncle->color=Black;
                node=GrandParent;
            }
            else
            {
                if (node==Father->right)
                {
                    node=Father;
                    LeftRotate(Tree,node);
                    Father=node->parent;
                }
                Father->color=Black;
                GrandParent->color=Red;
                RightRotate(Tree,GrandParent);
            }
        }
        else
        {
            Uncle=GrandParent->left;
            if (Uncle!=nil && Uncle->color==Red)
            {
                GrandParent->color=Red;
                Father->color=Black;
                Uncle->color=Black;
                node=GrandParent;
            }
            else
            {
                if (node==Father->left)
                {
                    node=Father;
                    RightRotate(Tree,node);
                    Father=node->parent;
                }
                Father->color=Black;
                GrandParent->color=Red;
                LeftRotate(Tree,GrandParent);
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
    node->dup=NULL;
    node->color=Red;
    curNode=*Tree;
    p=nil;
    while (curNode!=nil)
    {
        p=curNode;
        switch (mode)
        {
        case IDSort:
            if (Stu->ID < p->data->ID)
                curNode=curNode->left;
            else if (Stu->ID > p->data->ID)
                curNode=curNode->right;
            else
                return -2;  //error:duplicate ID
            break;
        case NameSort:
            if (wcscmp(Stu->Name,p->data->Name)<0)
                curNode=curNode->left;
            else if (wcscmp(Stu->Name,p->data->Name)>0)
                curNode=curNode->right;
            else
                curNode=nil;
            break;
        };
    }
    if (p==nil)
        *Tree=node;
    else
    {
        switch (mode)
        {
        case IDSort:
            if (Stu->ID < p->data->ID)
                p->left=node;
            else if (Stu->ID > p->data->ID)
                p->right=node;
            else
                return -2;  //error:duplicate ID
            break;
        case NameSort:
            if (wcscmp(Stu->Name,p->data->Name)<0)
                p->left=node;
            else if (wcscmp(Stu->Name,p->data->Name)>0)
                p->right=node;
            else
            {
                DupNameList* temp=(DupNameList*)malloc(sizeof(DupNameList));
                temp->node=node;
                temp->Next=NULL;
                if (p->dup==NULL)
                    p->dup=temp;
                else
                {
                    DupNameList* past=p->dup;
                    while (past->Next!=NULL)
                        past=past->Next;
                    past->Next=temp;
                }
                return 0;
            }
            break;
        };
    }

    node->parent=p;
    InsertFixup(Tree,node);
    return 0;
}

RBTreeNode *MinImum(RBTree *rbTree)
{
	RBTreeNode *curNode, *targetNode;

	curNode = *rbTree;
	targetNode = NULL;
	while (curNode != NULL) {
		targetNode = curNode;
		curNode = curNode->left;
	}
	return targetNode;
}

RBTreeNode* Successor(RBTreeNode* x)
{
	RBTreeNode *targetNode;

	if (x == NULL) return NULL;
	if (x->right != NULL) {
		targetNode = MinImum(&(x->right));
	} else {
		while ( x->parent != NULL && x->parent->left != x) {
			x  = x->parent;
		}
		targetNode = x->parent;
	}

	return targetNode;
}

void DeleteFixup(RBTree* Tree,RBTreeNode* node,RBTreeNode* x)
{
    RBTreeNode* Brother;
    while ((x==nil || x->color==Black) && x!=*Tree)
    {
        if (x==node->left)
        {
            Brother=node->right;
            if (Brother->color==Red) //Case 1:Brother node is red.
            {
                Brother->color=Black;
                node->color=Red;
                LeftRotate(Tree,node);
                Brother=node->right;
            }
            if ((Brother->left==nil || Brother->left->color==Black) && (Brother->right==nil || Brother->right->color==Black))
            {
                Brother->color=Red;
                x=node;
                node=node->parent;
            }
            else
            {
                if (Brother->right==nil || Brother->color==Black)
                {
                    Brother->left->color=Black;
                    Brother->color=Red;
                    RightRotate(Tree,Brother);
                    Brother=node->right;
                }
                Brother->color=node->color;
                node->color=Black;
                Brother->right->color=Black;
                LeftRotate(Tree,node);
                x=*Tree;
            }
        }
        else
        {
            Brother=node->left;
            if (Brother->color==Red)
            {
                Brother->color=Black;
                node->color=Red;
                RightRotate(Tree,node);
                Brother=node->left;
            }
            if ((Brother->left==nil || Brother->left->color==Black) && (Brother->right==nil || Brother->right->color==Black))
            {
                Brother->color=Red;
                x=node;
                node=node->parent;
            }
            else
            {
                if (Brother->left==nil || Brother->left->color==Black)
                {
                    Brother->right->color=Black;
                    Brother->color=Red;
                    LeftRotate(Tree,Brother);
                    Brother=node->left;
                }
                Brother->color=node->color;
                node->color=Black;
                Brother->left->color=Black;
                RightRotate(Tree,node);
                x=*Tree;
            }
        }
    }
    if (x!=nil)
        x->color=Black;
}

void Delete(RBTree* Tree,RBTreeNode* node)
{
    RBTreeNode *realDel,*child;

    if (node->left==nil || node->right==nil)
        realDel=node;
    else
        realDel=Successor(node);

    if (realDel->left!=nil)
        child=realDel->left;
    else
        child=realDel->right;

    if (child!=nil)
        child->parent=realDel->parent;

    if (realDel->parent==nil)
        *Tree=child;
    else
    {
        if (realDel->parent->left==realDel)
            realDel->parent->left=child;
        else
            realDel->parent->right=child;
    }

    if (node!=realDel)
        node->data=realDel->data;

    if (realDel->color==Black)
        DeleteFixup(Tree,realDel->parent,child);

    if (realDel->dup!=NULL)
    {
        DupNameList* temp=realDel->dup;
        DupNameList* prev=NULL;
        while (temp->Next!=NULL)
        {
            prev=temp;
            temp=temp->Next;
            free(prev);
        }
        free(temp);
    }
    free(realDel);    //destroy Tree Node
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
            if (sum<maxSize)
                ResultArray[sum++]=Tree;
            if (Tree->dup!=NULL)
            {
                DupNameList* temp=Tree->dup;
                if (sum<maxSize)
                    ResultArray[sum++]=temp->node;
                while (temp->Next!=NULL)
                {
                    temp=temp->Next;
                    if (sum<maxSize)
                        ResultArray[sum]=temp->node;
                    sum++;
                }
            }
            return sum;
        }
    }
    return 0;
}

void PreOrderTranverse(FILE* file,RBTree Tree,int (*visitor)(FILE* file,RBTreeNode* node))
{
    if (Tree!=nil)
    {
        PreOrderTranverse(file,Tree->left,visitor);
        visitor(file,Tree);
        PreOrderTranverse(file,Tree->right,visitor);
    }
}

void InOrderTranverse(RBTree Tree,void (*visitor)(RBTreeNode* node))
{
    if (Tree!=nil)
    {
        InOrderTranverse(Tree->left,visitor);
        visitor(Tree);
        InOrderTranverse(Tree->right,visitor);
    }
}

void DestroyRBTree(RBTree* Tree)
{
    while (*Tree!=nil)
    {
        printf("Deleting %d\n",(*Tree)->data->ID);/*
        if ((*Tree)->data!=NULL)
            DestroyStudent((*Tree)->data);*/
        Delete(Tree,*Tree);
    }
}

void PrintNode(RBTreeNode* node)
{
    printf("%d %ls\n",node->data->ID,node->data->Name);
    if (node->dup!=NULL)
    {
        DupNameList* temp=node->dup;
        while (temp!=NULL)
        {
            printf("%d %ls\n",temp->node->data->ID,temp->node->data->Name);
            temp=temp->Next;
        }
    }
}








