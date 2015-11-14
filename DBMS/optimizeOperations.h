#ifndef OPTIMIZESELECT_H_INCLUDED
#define OPTIMIZESELECT_H_INCLUDED
#include "globals.h"

void categorizeConditions();
void mapOptimizedConditions(treeNode *select);
void mapJoinConditions(treeNode *select);
void moveProjectOperation(treeNode *traverse);

#endif // OPTIMIZESELECT_H_INCLUDED
