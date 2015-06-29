#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"

unsigned int getAge(char* bir)
{
	time_t timep;
	char str[9];
	struct tm* p;
	time(&timep);
	p=gmtime(&timep);
	int date=(1900+p->tm_year)*10000+(1+p->tm_mon)*100+(p->tm_mday);
	int i,age;
	int year=0,month=0,day=0;

	for (i=0;i<=3;i++)
	{
		year+=bir[i]-'0';
		year*=10;
	}
	for (i=4;i<=5;i++)
	{
		month+=bir[i]-'0';
		month*=10;
	}
	for (i=6;i<=7;i++)
	{
		day+=bir[i]-'0';
		day*=10;
	}
	age=1900+p->tm_year-year;
	month=1+p->tm_mon-month;
	day=p->tm_mday-day;
	if (day<0)
		month--;
	if (month<0)
		age--;
	return age;
}

int LoadDatabase(char* filename,RBTree IDTree,RBTree NameTree)
{
	FILE* file=fopen(filename,"rb");
	Student* Student;
	int sum=0;
	char MarkStr[10];
	if (file==NULL)
		return -1;	//error:file open failed.
	fread(MarkStr,sizeof(unsigned char),4,file);
	MarkStr[5]=0;
	if (strcmp(MarkStr,"JOJO"))
		return -2;	//error:file is not a database.
	while ((Student=LoadStudent(file))!=NULL)
	{
		Insert(&IDTree,Student,IDSort);
		Insert(&NameTree,Student,NameSort);
		sum++;
	}
    return sum;
}

int SaveDatabase(RBTree Tree,char* filename)
{
    FILE* file=fopen(filename,"wb");
    Student* Student;
	if (file==NULL)
        return -1;  //error:file open failed.
    fwrite("JOJO",sizeof(char),4,file);
	while (Tree!=nil)
	{
		Student=Tree->data;
		SaveStudent(file,Student);	//save student.
		Tree=Successor(Tree);
	}
	fputc(0,file);	//write the EOF mark.
	fclose(file);
    return 0;
}

Student* LoadStudent(FILE* file)
{
	unsigned char mark=fgetc(file);
	unsigned char len;
	unsigned int ID;
	wchar_t Name[50];
	wchar_t data[100];
	unsigned int Age;
	SexType Sex;
	char Birthday[9];
	unsigned char CustomCount;
	Student* Student;

	if (mark==0)
		return NULL;	//0x0 is a mark,indicate the file ended.
	else if (mark==0xff)
	{
		fread(&ID,sizeof(unsigned int),1,file);	//read ID.
		len=fgetc(file);	//read name length.
		fread(Name,sizeof(wchar_t),len,file);	//read name.
		Sex=fgetc(file);	//read sex.
		fread(Birthday,sizeof(char),8,file);	//read birthday.
		Birthday[8]=0;	//set the birthday string end mark.
		Age=getAge(Birthday);	//get age.
		CustomCount=fgetc(file);	//read the custom information count.
		Student=BuildStudent(ID,Name,Age,Sex,Birthday);
		while (CustomCount--)
		{
			len=fgetc(file);	//read information name length.
			fread(Name,sizeof(wchar_t),len,file);	//read information name.
			len=fgetc(file);
			fread(data,sizeof(wchar_t),len,file);	//read information data.
			InsertInfo(Student,Name,data);
		}
		return Student;
	}
	return NULL;
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














