#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"
#include "../../FileIO/include/FileIO.h"

int main()
{
    setlocale(LC_ALL,"");
    unsigned int ID;
    int i;
    wchar_t Name[20];
    //unsigned int Age;
    //char Birthday[9];
    FILE* file=fopen("data.txt","rt");
    RBTree IDTree=NULL,NameTree=NULL;
    Student* temp;/*
    for (i=1;i<=34;i++)
    {
        fscanf(file,"%d%ls",&ID,Name);
        temp=BuildStudent(ID,Name,19,Male,"19700101");
        Insert(&IDTree,temp,IDSort);
        Insert(&NameTree,temp,NameSort);
        printf("%d %ls\n",ID,Name);
    }*/

    printf("%d\n",LoadDatabase("database.dat",&IDTree,&NameTree));
    printf("\n");
    InOrderTranverse(IDTree,PrintNode);
    SaveDatabase(IDTree,"database1.dat");
    printf("\n");
    while (1)
    {
        scanf("%d",&ID);
        Delete(&IDTree,SearchByID(IDTree,ID));
        InOrderTranverse(IDTree,PrintNode);
    }
    //DestroyRBTree(&IDTree);
    printf("\n");
    //DestroyRBTree(&NameTree);
    return 0;
}
