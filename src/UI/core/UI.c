#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/UI.h"

int getWCSRealLength(wchar_t* str)
{
    int i,realLen=0;
    int len=wcslen(str);
    for (i=0;i<len;i++)
        if (str[i]<128)
            realLen++;
        else
            realLen+=2;
    return realLen;
}

int AlignBySpace(wchar_t* str,int TargetLength)
{
    int i=TargetLength-getWCSRealLength(str);
    if (i<=0)
        return -1;  //error:target length must be bigger than string length.
    else
        while (i--)
            printf(" ");
    return TargetLength-getWCSRealLength(str);
}

void printStartMenu()
{
	wprintf(L"学生信息管理系统已启动。\n");
	wprintf(L"==========================================\n");
	wprintf(L"1:读取现有数据库\n2:创建新的数据库\n");
	wprintf(L"==========================================\n");
}

void printMainMenu()
{
	wprintf(L"请输入数字选择：\n");
	wprintf(L"================\n");
	wprintf(L"1:浏览学生信息\n2:查询学生信息\n3:添加新学生信息\n4:保存并退出\n5:直接退出\n");
}

void printCmdErr()
{
    wprintf(L"输入非法，请重新输入。\n");
}

void inputCorrectInt(int* cmd,int l,int r)
{
    while (1)
    {
        if (scanf("%d",cmd)!=1 || (*cmd<l || *cmd>r))
        {
            printCmdErr();
            continue;
        }
        else
            break;
    }
}

int inputYesOrNo()
{
    char cmd;
    getchar();
    while (1)
    {
        if (scanf("%c",&cmd)!=1 || (cmd!='y' && cmd!='n'))
        {
            printCmdErr();
            continue;
        }
        else
            break;
    }
    switch (cmd)
    {
    case 'y':
        return 1;
        break;
    case 'n':
        return 0;
        break;
    };
    return -1;
}

void inputCorrectWCS(wchar_t* str,int maxLen)
{
    while (1)
    {
        if (scanf("%ls",str)!=1 || maxLen<wcslen(str))
        {
            printCmdErr();
            continue;
        }
        else
            break;
    }
}

void printStudentListHead()
{
    wprintf(L"学号\t\t姓名\t\t性别\t年龄\t出生日期\n");
    wprintf(L"========================================================================\n");
}

void printAllStudent(RBTree Tree)
{
    system("cls");
    wprintf(L"学生基本信息如下：\n\n");
    printStudentListHead();
    InOrderTranverse(Tree,printSingleStudent);
    printf("\n");
    system("pause");
}

void printSingleStudent(RBTreeNode* node)
{
    wprintf(L"%d\t%s",node->data->ID,node->data->Name);
    AlignBySpace(node->data->Name,16);
    if (node->data->Sex==Male)
        wprintf(L"男\t");
    else
        wprintf(L"女\t");
    wprintf(L"%d\t",node->data->Age);
    printf("%s\n",node->data->Birthday);
}

void printSearchStudent(RBTree IDTree,RBTree NameTree)
{
    int cmd,i;
    int ID;
    wchar_t name[50];
    RBTreeNode* Result[10];

    system("cls");
    wprintf(L"请输入数字选择：\n");
    wprintf(L"================\n");
    wprintf(L"1:按学号查询\n2:按姓名查询\n");
    inputCorrectInt(&cmd,1,2);
    switch (cmd)
    {
    case 1:
        {
            wprintf(L"请输入要查询的学号：\n");
            inputCorrectInt(&ID,1,2E+9);
            RBTreeNode* tempNode=SearchByID(IDTree,ID);
            if (tempNode!=nil)
            {
                system("cls");
                printStudentListHead();
                printSingleStudent(tempNode);
                printStudentInfo(tempNode);
                printSelectStudentInfo(IDTree,NameTree,tempNode);
            }
            else
            {
                wprintf(L"找不到该学生的信息。\n");
                return;
            }
            break;
        }
    case 2:
        {
            wprintf(L"请输入要查询的姓名：\n");
            scanf("%ls",name);
            int sum=SearchByName(NameTree,name,Result,10);
            if (sum>0)
            {
                system("cls");
                wprintf(L"找到了%d名学生的信息：\n",sum);
                printStudentListHead();
                for (i=0;i<(sum>10?10:sum);i++)
                    printSingleStudent(Result[i]);
                printf("\n");
                system("pause");
                return;
            }
            else
            {
                wprintf(L"找不到该学生的信息。\n");
                system("pause");
                return;
            }
            break;
        }

    };

}

void printStudentInfo(RBTreeNode* node)
{
    Student* Student=node->data;
    StudentInfoNode* temp=Student->CustomInfo;
    if (temp==NULL)
    {
        wprintf(L"该学生无扩展信息。\n");
        return;
    }
    wprintf(L"扩展属性信息：\n");
    wprintf(L"属性名称                属性内容\n");
    wprintf(L"========================================================================\n");
    while (temp!=NULL)
    {
        wprintf(L"%s",temp->Name);
        AlignBySpace(temp->Name,24);
        wprintf(L"%s\n",temp->data);
        temp=temp->Next;
    }
}

void printSelectStudentInfo(RBTree IDTree,RBTree NameTree,RBTreeNode* node)
{
    int cmd;
    char newBir[9];
    wchar_t newName[20],oldName[20];
    wchar_t newData[100];
    printf("\n");
    wprintf(L"请输入数字选择：\n");
    wprintf(L"================\n");
    if (node->data->CustomInfoCount>0)
    {
        wprintf(L"1:返回\n2:修改出生日期\n3:删除学生\n4:添加学生扩展信息\n5:删除学生扩展信息\n6:修改学生扩展信息\n");
        inputCorrectInt(&cmd,1,6);
    }
    else
    {
        wprintf(L"1:返回\n2:修改出生日期\n3:删除学生\n4:添加学生扩展信息\n");
        inputCorrectInt(&cmd,1,4);
    }
    system("cls");
    switch (cmd)
    {
    case 1:
        {
            return;
            break;
        }
    case 2:
        {
            wprintf(L"请输入新出生日期(YYYYMMMDD)：\n");
            while (scanf("%s",newBir)!=1 || getAge(newBir)<1)
                wprintf(L"出生日期输入非法，请重新输入。\n");
            strcpy(node->data->Birthday,newBir);
            node->data->Age=getAge(newBir);
            wprintf(L"出生日期修改完成，按任意键返回。\n");
            break;
        }
    case 3:
        {
            wprintf(L"确认吗？(y/n)\n");
            if (inputYesOrNo())
            {
                Delete(&IDTree,node);
                Delete(&NameTree,node);
                wprintf(L"删除完成，按任意键返回。\n");
            }
            break;
        }
    case 4:
        {
            wprintf(L"输入新扩展信息名称（最大10字）：\n");
            inputCorrectWCS(newName,10);
            wprintf(L"输入新扩展信息内容（最大50字）：\n");
            inputCorrectWCS(newData,50);
            if (InsertInfo(node->data,newName,newData)==0)
            {
                wprintf(L"添加成功，按任意键返回。\n");
            }
            else
            {
                wprintf(L"添加失败。\n");
            }
            break;
        }
    case 5:
        {
            wprintf(L"输入扩展信息名称：\n");
            inputCorrectWCS(newName,10);
            if (SearchInfo(node->data,newName)==NULL)
            {
                wprintf(L"操作失败：扩展信息不存在。\n");
            }
            wprintf(L"确认吗？(y/n)\n");
            if (inputYesOrNo())
            {
                DeleteInfo(node->data,newName);
                wprintf(L"删除完成，按任意键返回。\n");
            }
            break;
        }
    case 6:
        {
            wprintf(L"输入扩展信息名称：\n");
            inputCorrectWCS(oldName,10);
            if (SearchInfo(node->data,oldName)==NULL)
            {
                wprintf(L"操作失败：扩展信息不存在。\n");
            }
            wprintf(L"输入新扩展信息名称：\n");
            inputCorrectWCS(newName,10);
            wprintf(L"输入新扩展信息内容：\n");
            inputCorrectWCS(newData,50);
            if (ChangeInfo(node->data,oldName,newName,newData)==0)
            {
                wprintf(L"添加成功，按任意键返回。\n");
            }
            else
            {
                wprintf(L"添加失败。\n");
            }
            break;
        }
    };

    system("pause");
    system("cls");
}

void printAddStudent(RBTree IDTree,RBTree NameTree)
{

    int ID,cmd;
    wchar_t name[20],newName[20],newData[100];
    SexType Sex;
    char newBir[9];
    Student* Student;

    system("cls");
    wprintf(L"输入新学生学号（不可修改）：\n");
    inputCorrectInt(&ID,1,2E+9);
    wprintf(L"输入新学生姓名（不可修改）：\n");
    inputCorrectWCS(name,10);
    wprintf(L"选择新学生性别（不可修改）：\n");
    wprintf(L"1:男\t2:女\n");
    inputCorrectInt(&cmd,1,2);
    switch (cmd)
    {
    case 1:
        Sex=Male;
        break;
    case 2:
        Sex=Female;
        break;
    };
    wprintf(L"输入出生日期(YYYYMMDD)：\n");
    while (scanf("%s",newBir)!=1 || getAge(newBir)<1)
        wprintf(L"出生日期输入非法，请重新输入。\n");

    Student=BuildStudent(ID,name,getAge(newBir),Sex,newBir);
    if (Student==NULL)
    {
        wprintf(L"添加失败。\n");
        system("pause");
        return;
    }
    Insert(&IDTree,Student,IDSort);
    Insert(&NameTree,Student,NameSort);

    wprintf(L"是否添加扩展信息？(y/n)");
    while (inputYesOrNo())
    {
        wprintf(L"输入新扩展信息名称（最大10字）：\n");
        inputCorrectWCS(newName,10);
        wprintf(L"输入新扩展信息内容（最大50字）：\n");
        inputCorrectWCS(newData,50);
        if (InsertInfo(Student,newName,newData)==0)
        {
            wprintf(L"添加成功，");
        }
        else
        {
            wprintf(L"添加失败，");
        }
        wprintf(L"是否继续添加(y/n)？\n");
    }
    wprintf(L"添加完成，按任意键返回。\n");
    system("pause");
    system("cls");
}

int printSaveAndExit(RBTree Tree,char* filename)
{
    wprintf(L"正在保存...\n");
    SaveDatabase(Tree,filename);
    wprintf(L"保存完成，是否退出(y/n)？\n");
    if (inputYesOrNo())
        return 1;
    else
        return 0;
    system("cls");
}

int printDirectExit()
{
    wprintf(L"未保存退出，确认吗(y/n)？\n");
    if (inputYesOrNo())
        return 1;
    else
        return 0;
    system("cls");
}






