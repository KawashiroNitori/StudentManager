#ifndef __UI_H__
#define __UI_H__
#include <stdio.h>
#include "../../RBTree/include/RBTree.h"
#include "../../Student/include/Student.h"
#include "../../FileIO/include/FileIO.h"

int getWCSRealLength(wchar_t* str);

int AlignBySpace(wchar_t* str,int TargetLength);

void printStartMenu();

void printMainMenu();

void printCmdErr();

void inputCorrectInt(int* cmd,int l,int r);

int inputYesOrNo();

void inputCorrectWCS(wchar_t* str,int maxLen);

void printStudentListHead();

void printAllStudent(RBTree Tree);

void printSingleStudent(RBTreeNode* node);

void printSearchStudent(RBTree IDTree,RBTree NameTree);

void printStudentInfo(RBTreeNode* node);

void printSelectStudentInfo(RBTree IDTree,RBTree NameTree,RBTreeNode* node);

void printAddStudent(RBTree IDTree,RBTree NameTree);

int printSaveAndExit(RBTree Tree,char* filename);

int printDirectExit();





#endif
