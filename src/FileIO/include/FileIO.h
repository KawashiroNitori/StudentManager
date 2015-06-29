#ifndef __FILEIO_H__
#define __FILEIO_H__

unsigned int getAge(char* str);

int LoadDatabase(char* filename,RBTree IDTree,RBTree NameTree);

int SaveDatabase(RBTree Tree,char* filename);

int LoadStudent(FILE* file);

int SaveStudent(FILE* file);


#endif
