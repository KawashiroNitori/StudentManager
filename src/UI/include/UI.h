#ifndef __UI_H__
#define __UI_H__
#include <stdio.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"
#include "../../FileIO/include/FileIO.h"

void printStartMenu();

void printMainMenu();

void printCmdErr();

void inputCorrectInt(int* cmd,int l,int r);

void printAllStudent(RBTree Tree);

void printSingleStudent(RBTreeNode* node);




#endif
