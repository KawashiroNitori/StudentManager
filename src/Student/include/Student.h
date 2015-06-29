#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <wchar.h>

typedef enum SexType
{
    Male,Female
}SexType;

typedef struct StudentInfoNode
{
	wchar_t Name[50];
	wchar_t data[100];
	struct StudentInfoNode* Next;
}StudentInfoNode,*StudentCustomInfo;

typedef struct Student
{
    unsigned int ID;
    wchar_t Name[20];
    unsigned int Age;
    SexType Sex;
    char Birthday[9];
	unsigned char CustomInfoCount;
	StudentCustomInfo CustomInfo;
} Student;

Student* BuildStudent(unsigned int ID,wchar_t* Name,unsigned int Age,SexType Sex,char* Birthday);

void DestroyStudent(Student* Student);

int InsertInfo(Student* Student,wchar_t* Name,wchar_t* Info);

StudentInfoNode* SearchInfo(Student* Student,wchar_t* Name);

int DeleteInfo(Student* Student,wchar_t* Name);

#endif
