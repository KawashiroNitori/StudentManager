#ifndef __FILEIO_H__
#define __FILEIO_H__

int aToi(char* str,int l,int r);

int getAge(char* str);

int LoadDatabase(char* filename,RBTree* IDTree,RBTree* NameTree);

int SaveDatabase(RBTree Tree,char* filename);

Student* LoadStudent(FILE* file);

int SaveStudent(FILE* file,Student* Student);

int SaveNode(FILE* file,RBTreeNode* node);


#endif
