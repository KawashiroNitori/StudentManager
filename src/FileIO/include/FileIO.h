#ifndef __FILEIO_H__
#define __FILEIO_H__

int LoadDatabase(char* filename);

int SaveDatabase(char* filename);

int LoadStudent(FILE* file);

int SaveStudent(FILE* file);


#endif
