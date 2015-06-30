#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include "../include/UI.h"

void printStartMenu()
{
	wprintf(L"学生信息管理系统已启动。\n");
	wprintf(L"==========================================\n");
	wprintf(L"1:读取现有数据库\n2:创建新的数据库\n");
	wprintf(L"==========================================\n");
}

void printMainMenu()
{
	wprintf(L"请输入数字选择：\n==============\n");
	wprintf(L"1:浏览学生信息\n2:查询学生信息\n4:添加新学生信息\n5:保存并退出\n6:直接退出\n");
}

void printCmdErr()
{
    wprintf(L"指令输入错误，请重新输入。\n");
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

void printAllStudent(RBTree Tree)
{
    wprintf(L"学生基本信息如下：\n\n");
    wprintf(L"学号\t\t姓名\t\t性别\t年龄\t生日\n");
    wprintf(L"========================================================================\n");
    InOrderTranverse(Tree,printSingleStudent);
    printf("\n");
}

void printSingleStudent(RBTreeNode* node)
{
    wprintf(L"%d\t%s\t",node->data->ID,node->data->Name);
    if (wcslen(node->data->Name)<4)
        printf("\t");
    if (node->data->Sex==Male)
        wprintf(L"男\t");
    else
        wprintf(L"女\t");
    wprintf(L"%d\t",node->data->Age);
    printf("%s\n",node->data->Birthday);
}








