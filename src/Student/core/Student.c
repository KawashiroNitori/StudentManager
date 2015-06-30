#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Student.h"
#include "../../RBTree/include/RBTree.h"

Student* BuildStudent(unsigned int ID,wchar_t* Name,unsigned int Age,SexType Sex,char* Birthday)
{
    Student* tempStudent=(Student*)malloc(sizeof(Student));
    if (tempStudent==NULL)
        return NULL;
    tempStudent->ID=ID;
    wcscpy(tempStudent->Name,Name);
    tempStudent->Age=Age;
    tempStudent->Sex=Sex;
    strcpy(tempStudent->Birthday,Birthday);
    tempStudent->CustomInfoCount=0;
    tempStudent->CustomInfo=NULL;
    return tempStudent;
}

void DestroyStudent(Student* Student)
{
    StudentInfoNode* Info=Student->CustomInfo;
    StudentInfoNode* temp;
    while (Info!=NULL)
    {
        temp=Info->Next;
        free(Info);
        Info=temp;
    }
    free(Student);
    Student=NULL;
}

int InsertInfo(Student* Student,wchar_t* Name,wchar_t* Info)
{
    if (SearchInfo(Student,Name)!=NULL)
        return -2;  //error:duplicate name.
    StudentInfoNode* NewInfo=(StudentInfoNode*)malloc(sizeof(StudentInfoNode));
    if (NewInfo==NULL)
        return -1;  //error:get memory failed.
    wcscpy(NewInfo->Name,Name);
    wcscpy(NewInfo->data,Info);
    NewInfo->Next=NULL;
    Student->CustomInfoCount++;
    StudentInfoNode* node=Student->CustomInfo;
    if (node==NULL)
        Student->CustomInfo=NewInfo;
    else
    {
        while (node->Next!=NULL)
            node=node->Next;
        node->Next=NewInfo;
    }
    return 0;
}

StudentInfoNode* SearchInfo(Student* Student,wchar_t* Name)
{
    StudentInfoNode* node=Student->CustomInfo;
    if (node==NULL)
        return NULL;
    else
        while (node!=NULL && wcscmp(node->Name,Name))
            node=node->Next;
    if (node==NULL || wcscmp(node->Name,Name))
        return NULL;
    else
        return node;
}

int DeleteInfo(Student* Student,wchar_t* Name)
{
    StudentInfoNode* node=Student->CustomInfo;
    StudentInfoNode* prev=NULL;
    if (node==NULL)
        return -1;  //error:search failed.
    else
        while (node!=NULL && wcscmp(node->Name,Name))
        {
            prev=node;
            node=node->Next;
        }
    if (node==NULL || wcscmp(node->Name,Name))
        return -1;  //error:search failed.
    else
    {
        if (prev==NULL) //searched first node.
            Student->CustomInfo=node->Next;
        else
            prev->Next=node->Next;
    }
    Student->CustomInfoCount--;
    free(node);
    return 0;
}

int ChangeInfo(Student* Student,wchar_t* OldName,wchar_t* NewName,wchar_t* NewData)
{
    StudentInfoNode* node=SearchInfo(Student,OldName);
    if (node==NULL)
        return -1;
    wcscpy(node->Name,NewName);
    wcscpy(node->data,NewData);
    return 0;
}















