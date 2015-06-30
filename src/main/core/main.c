#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"
#include "../../FileIO/include/FileIO.h"
#include "../../UI/include/UI.h"

int main()
{
    char filename[100];
    int sum,cmd;
    RBTree IDTree=NULL,NameTree=NULL;
    setlocale(LC_ALL,"");
    printStartMenu();
    inputCorrectInt(&cmd,1,2);
    if (cmd==1)
    {
        wprintf(L"请输入文件名：\n");
        scanf("%s",filename);
        strcat(filename,".db");
        sum=LoadDatabase(filename,&IDTree,&NameTree);
        wprintf(L"正在尝试读取数据...\n");
        if (sum<0)
        {
            wprintf(L"读取失败。\n\n");
            system("pause");
            return 0;
        }
        else
        {
            system("cls");
            wprintf(L"已读取%d名学生信息。\n",sum);
        }
    }
    else
    {
        wprintf(L"请输入文件名：\n");
        scanf("%s",filename);
        strcat(filename,".db");
    }

    while(1)
    {
        printMainMenu();
        inputCorrectInt(&cmd,1,5);
        switch (cmd)
        {
        case 1: //output information
            printAllStudent(IDTree);
            system("cls");
            break;
        case 2: //search student
            printSearchStudent(IDTree,NameTree);
            system("cls");
            break;
        case 3:
            printAddStudent(IDTree,NameTree);
            system("cls");
            break;
        case 4:
            if (printSaveAndExit(IDTree,filename))
                return 0;
            system("cls");
            break;
        case 5:
            if (printDirectExit())
                return 0;
            system("cls");
            break;
        };
    }/*
    int i;
    int ID;
    wchar_t name[20];
    Student* Student;
    FILE* file=fopen("data.txt","rb");
    for (i=1;i<=34;i++)
    {
        fscanf(file,"%d%ls",&ID,name);
        Student=BuildStudent(ID,name,10,Male,"19700101");
        Insert(&IDTree,Student,IDSort);
        wprintf(L"%d %s\n",ID,name);
    }
    fclose(file);
    SaveDatabase(IDTree,"database.db");*/
    return 0;
}
