#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <wchar.h>

typedef enum SexType
{
    Male,Female
}SexType;

typedef struct StudentInfoNode
{
	wchar_t InfoName[50];
	wchar_t data[100];
	StudentInfoNode* Next;
}StudentInfoNode,*StudentCustomInfo;

typedef struct Student
{
    unsigned int ID;
    wchar_t Name[20];
    unsigned int Age;
    SexType Sex;
    char Birthday[8];
	unsigned int CostomInfoCount;
	StudentCustomInfo CustomInfo;
} Student;

#endif
