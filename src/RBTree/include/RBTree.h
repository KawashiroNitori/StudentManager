#ifndef __RBTREE_H__
#define __RBTREE_H__

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

void LeftRotate(RBTree &Tree,RBTreeNode* x)
{
	if (x->right!=nil)
	{
		RBTreeNode* y=getRight(x);
		x->right=y->left;
		if (y->left!=nil)
			y->left->parent=x;
		y->parent=x->parent;
		if (x->parent!=nil)
			Tree=y;
		else if (x==getLeft(getParent(x)))
			x->parent->left=y;
		else
			x->parent->right=y;
		y->left=x;
		x->parent=y;
	}
}

void RightRotate(RBTree &Tree,RBTreeNode* x)
{
	if (x->left!=nil)
	{
		RBTreeNode* y=getLeft(x);
		x->left=y->right;
		if (y->right!=nil)
			y->right->parent=x;
		y->parent=x->parent;
		if (x->parent==nil)
			Tree=y;
		else
			if (x==getLeft(getParent(x)))
				x->parent->left=y;
			else
				x->parent->right=y;
		y->right=x;
		x->parent=y;
	}
}

void InsertFixup(RBTree &Tree,RBTreeNode* node)
{
	RBTreeNode* y;
	while (getParent(node)->color=Red)
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
	Tree->color=Black;
}

void Insert(Tree &Tree,Student* )

#endif 








