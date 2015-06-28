#include "../include/RBTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

RBTreeNode* nil=NULL;

void LeftRotate(RBTree* Tree,RBTreeNode* x)
{
    RBTreeNode* right=x->right;
    if ((x->right=right->left))
        right->left->parent=x;
    right->left=x;
    if ((right->parent=x->parent))
    {
        if (x==x->parent->right)
            x->parent->right=right;
        else
            x->parent->left=right;
    }
    else
        *Tree=right;
    x->parent=right;
}

void RightRotate(RBTree* Tree,RBTreeNode* x)
{
    RBTreeNode* left=x->left;
    if ((x->left=left->right))
        left->right->parent=x;
    left->right=x;
    if ((left->parent=x->parent))
    {
        if (x==x->parent->right)
            x->parent->right=left;
        else
            x->parent->left=left;
    }
    else
        *Tree=left;
    x->parent=left;
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

RBTreeNode* Successor(RBTreeNode* node)
{
    if (node->right!=nil)
    {
        RBTreeNode* p=node->right;
        while (p->left!=nil)
            p=p->left;
        return p;
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
    RBTreeNode *x,*y;
    if (node->left==nil || node->right==nil)
        y=node;
    else
        y=Successor(node);

    if (y->left!=nil)
        x=y->left;
    else
        x=y->right;

    if (x!=nil)
        x->parent=y->parent;

    if (y->parent==nil)
        *Tree=x;
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
        DeleteFixup(Tree,y->parent,x);
    if (y->data!=NULL)
        DestroyStudent(y->data);//destroy student
    if (y->dup!=NULL)
    {
        DupNameList* temp=y->dup;
        DupNameList* prev=NULL;
        while (temp->Next!=NULL)
        {
            prev=temp;
            temp=temp->Next;
            free(prev);
        }
        free(temp);
    }
    free(y);    //destroy Tree Node
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

void InOrderTranverse(RBTree Tree,void (*visitor)(RBTreeNode* node))
{
    if (Tree!=nil)
    {
        InOrderTranverse(Tree->left,visitor);
        visitor(Tree);
        InOrderTranverse(Tree->right,visitor);
    }
}

void DestroyRBTree(RBTree Tree)
{
    while (Tree!=NULL && Tree!=nil)
        Delete(&Tree,Tree);
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








