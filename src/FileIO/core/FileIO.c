#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"
#include "../include/FileIO.h"

int aToi(char* str,int l,int r)
{
	int i,sum=0;
	for (i=l;i<=r;i++)
	{
	    sum*=10;
		sum+=str[i]-'0';
	}
	return sum;
}

int getAge(char* bir)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p=gmtime(&timep);
	int age;
	int year=0,month=0,day=0;

	if (strlen(bir)!=8)
        return -1;
	year=aToi(bir,0,3);
	month=aToi(bir,4,5);
	day=aToi(bir,6,7);

	if (year<1900 || year>1900+p->tm_year || month<1 || month>12 || day<1 || day>31)
        return -1;

	age=1900+p->tm_year-year;
	month=1+p->tm_mon-month;
	day=p->tm_mday-day;
	if (day<0)
		month--;
	if (month<0)
		age--;
	return age;
}

int LoadDatabase(char* filename,RBTree* IDTree,RBTree* NameTree)
{
	FILE* file=fopen(filename,"rb");
	Student* Student;
	int sum=0;
	char MarkStr[10];
	if (file==NULL)
		return -1;	//error:file open failed.
	fread(MarkStr,sizeof(unsigned char),4,file);
	MarkStr[4]=0;
	if (strcmp(MarkStr,"JOJO"))
		return -2;	//error:file is not a database.
	while ((Student=LoadStudent(file))!=NULL)
	{
		Insert(IDTree,Student,IDSort);
		Insert(NameTree,Student,NameSort);
		sum++;
	}
	fclose(file);
    return sum;
}

int SaveDatabase(RBTree Tree,char* filename)
{
    FILE* file=fopen(filename,"wb");
	if (file==NULL)
        return -1;  //error:file open failed.
    fwrite("JOJO",sizeof(char),4,file);
    PreOrderTranverse(file,Tree,SaveNode);
	fputc(0,file);	//write the EOF mark.
	fclose(file);
    return 0;
}

Student* LoadStudent(FILE* file)
{
	unsigned char mark=fgetc(file);
	unsigned char len;
	unsigned int ID,i;
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
		Name[len]=L'\0';
		fread(&Sex,sizeof(SexType),1,file);	//read sex.
		fread(Birthday,sizeof(char),8,file);	//read birthday.
		for (i=0;i<8;i++)
            Birthday[i]+='0';
		Birthday[8]=0;	//set the birthday string ending mark.
		Age=getAge(Birthday);	//get age.
		CustomCount=fgetc(file);	//read the custom information count.
		Student=BuildStudent(ID,Name,Age,Sex,Birthday);
		while (CustomCount--)
		{
			len=fgetc(file);	//read information name length.
			fread(Name,sizeof(wchar_t),len,file);	//read information name.
            Name[len]=L'\0';
			len=fgetc(file);
			fread(data,sizeof(wchar_t),len,file);	//read information data.
			data[len]=L'\0';
			InsertInfo(Student,Name,data);
		}
		return Student;
	}
	return NULL;
}

int SaveStudent(FILE* file,Student* Student)
{
    int i;
    fputc(0xff,file);   //write a mark,indicate the next bytes is a normal student.
    fwrite(&Student->ID,sizeof(unsigned int),1,file);
    unsigned char len=wcslen(Student->Name);
    fputc(len,file);    //write name length.
    fwrite(Student->Name,sizeof(wchar_t),len,file); //write name.
    fwrite(&Student->Sex,sizeof(SexType),1,file);   //write sex.
    for (i=0;i<8;i++)
        Student->Birthday[i]-='0';
    fwrite(Student->Birthday,sizeof(char),8,file);  //write birthday.
    for (i=0;i<8;i++)
        Student->Birthday[i]+='0';
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

int SaveNode(FILE* file,RBTreeNode* node)
{
    return SaveStudent(file,node->data);
}












