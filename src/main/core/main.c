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
    Student* temp;
    for (i=1;i<=34;i++)
    {
        fscanf(file,"%d%ls",&ID,Name);
        temp=BuildStudent(ID,Name,19,Male,"19700101");
        Insert(&IDTree,temp,IDSort);
        Insert(&NameTree,temp,NameSort);
        printf("%d %ls\n",ID,Name);
    }
    printf("\n");
    InOrderTranverse(NameTree,PrintNode);
    while (1)
    {
        scanf("%ls",Name);
        RBTreeNode* a[40];
        int sum=SearchByName(NameTree,Name,a,40);
        for (i=0;i<sum;i++)
            printf("%d %d %ls %s\n",i,a[i]->data->ID,a[i]->data->Name,a[i]->data->Birthday);
    }
    return 0;
}
