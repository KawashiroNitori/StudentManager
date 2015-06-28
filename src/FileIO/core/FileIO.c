#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"

int LoadDatabase(char* filename)
{
    return 0;
}

int SaveDatabase(char* filename)
{
    FILE* file=fopen(filename,"wb");
    if (file==NULL)
        return -1;  //error:file open failed.
    fwrite("JOJO",sizeof(char),4,file);
    return 0;
}

Student* LoadStudent(FILE* file)
{

    return 0;
}

int SaveStudent(FILE* file,Student* Student)
{
    fputc(0xff,file);   //write a mark,indicate the next bytes is a normal student.
    fwrite(&Student->ID,sizeof(unsigned int),1,file);
    unsigned char len=wcslen(Student->Name);
    fputc(len,file);    //write name length.
    fwrite(Student->Name,sizeof(wchar_t),len,file); //write name.
    fputc(Student->Sex,file);   //write sex.
    fwrite(Student->Birthday,sizeof(char),8,file);  //write birthday.
    fputc(Student->CustomInfoCount,file);   //write custom information count.

    if (Student->CustomInfo!=NULL)
    {
        StudentInfoNode* temp=Student->CustomInfo;
        while (temp!=NULL)
        {
            len=wcslen(temp->Name);
            fputc(len,file); //write information name length.
            fwrite(temp->Name,sizeof(wchar_t),len,file);    //write information name.
            len=wcslen(temp->data);
            fputc(len,file);    //write information data length.
            fwrite(temp->data,sizeof(wchar_t),len,file);    //write information data.
            temp=temp->Next;
        }
    }
    return 0;
}














