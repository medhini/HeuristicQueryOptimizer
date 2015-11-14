#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include<ctype.h>
#include "globals.h"

using namespace std;

void categorizeConditions()
{
    for(int i = 0; i < conditions.size(); i++)
    {
        if(conditions[i].compare("and")==0 || conditions[i].compare("or")==0 || conditions[i].compare("AND")==0 || conditions[i].compare("OR")==0)
            continue;

        string rValue = "";
        int pos;

        for(int j = 0; j < conditions[i].length(); j++)
        {
            if(conditions[i][j]=='=' || conditions[i][j]=='<' || conditions[i][j]=='!' || conditions[i][j]=='>')
            {
                pos = j+1;
            }
        }

        for(int j = pos; j < conditions[i].length(); j++)
            rValue = rValue + conditions[i][j];

        if(mapAttribute[rValue].compare("")==0)
        {
            //cout<<conditions[i]<<endl;
            optimizedConditions.push_back(conditions[i]);
        }

        else
        {
            joinConditions.push_back(conditions[i]);
        }
    }
}

void mapOptimizedConditions(treeNode *select) //After optimizing where clause
{
    for(int i = 0; i < optimizedConditions.size(); i++)
    {
        int pos = -1;
        string attrib = "";

        for(int j = 0; j < optimizedConditions[i].length(); j++)
        {
            if(optimizedConditions[i][j]=='=' || optimizedConditions[i][j]=='<' || optimizedConditions[i][j]=='!' || optimizedConditions[i][j]=='>')
                break;

            attrib = attrib + optimizedConditions[i][j];
        }

        string relation = mapAttribute[attrib];
//
//        set temp = projectAttributes[relation];
//        temp.insert(attrib);
//        projectAttributes[relation] = temp;
//
        treeNode *traverse = new treeNode();
        traverse = select;

        modifyTree(traverse, optimizedConditions[i], relation);
    }
}

void mapJoinConditions(treeNode *select)
{
    for(int i = 0; i < joinConditions.size(); i++)
    {
        int pos = (joinConditions[i].find_first_of('=') || joinConditions[i].find_first_of('!') || joinConditions[i].find_first_of('>') || joinConditions[i].find_first_of('<') );

        string lValue = joinConditions[i].substr(0, pos);
        string rValue = joinConditions[i].substr(pos+1, joinConditions[i].length()-pos-1);

        string relation1 = mapAttribute[lValue];
        string relation2 = mapAttribute[rValue];

        treeNode *traverse = new treeNode();
        traverse = select->left;

        modifyTree(traverse, joinConditions[i], relation1, relation2);
    }
}
void moveProjectOperation(treeNode *traverse)
{
    vector<string> projectList;
    if(traverse->val == 0)
        projectList.insert(projectList.end(), traverse->attributes.begin(), traverse->attributes.end());

    while(traverse!=NULL)
    {
        if(traverse->val == 3 && traverse->joinCondition!="")
        {
            int pos = (traverse->joinCondition.find_first_of('=') || traverse->joinCondition.find_first_of('!') || traverse->joinCondition.find_first_of('>') || traverse->joinCondition.find_first_of('<') );

            string attrib1 = traverse->joinCondition.substr(0, pos);
            string attrib2 = traverse->joinCondition.substr(pos+1, traverse->joinCondition.length()-pos-1);

            projectList.push_back(attrib1);
            projectList.push_back(attrib2);

            string relationName;

            if(traverse->right->val == 2)
                relationName = traverse->right->relationName;
            else if(traverse->right->left->val == 2)
                relationName = traverse->right->left->relationName;

            treeNode *newPtr = new treeNode();
            treeNode *newPtr2 = new treeNode();
            newPtr->val = 0;
            newPtr2->val = 0;

            for(int i = 0; i < projectList.size(); i++)
            {
                if(mapAttribute[projectList[i]] == relationName)
                {
                    newPtr->attributes.insert(projectList[i]);
                }
                else
                {
                    newPtr2->attributes.insert(projectList[i]);
                }
            }
            if(newPtr->attributes.size()!=0)
            {
                newPtr->left = traverse->right;
                newPtr->right = NULL;
                traverse->right = newPtr;
            }
            if(newPtr2->attributes.size()!=0)
            {
                newPtr2->left = traverse->left;
                newPtr2->right = NULL;
                traverse->left = newPtr2;
            }
        }

        traverse = traverse ->left;
    }
}

