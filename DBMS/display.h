#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "globals.h"

void calcExecPlan(treeNode *traverse);
void printExecPlan(treeNode *project, treeNode * select);
void printTree(treeNode *project);

#endif // DISPLAY_H_INCLUDED
