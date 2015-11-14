#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include<ctype.h>
#include "globals.h"
#include "optimizeOperations.h"

using namespace std;

vector< vector<string> > executionPlan;

void calcExecPlan(treeNode *traverse)
{
    if(traverse == NULL)
        return;

    else
    {
        calcExecPlan(traverse->left);
        calcExecPlan(traverse->right);

        if(traverse->val==0)
        {
            vector<string> temp;
            string str = "Project these attributes : ";
            temp.push_back(str);

            temp.insert(temp.end(), traverse->attributes.begin(), traverse->attributes.end());
            executionPlan.push_back(temp);
        }
        else if(traverse->val==1)
        {
            vector<string> temp;
            string str = "Select rows where : ";
            temp.push_back(str);

            temp.insert(temp.end(), traverse->conditions.begin(), traverse->conditions.end());

            vector<string> temp2;
            str = "from above";
            temp2.push_back(str);

            temp.insert(temp.end(), temp2.begin(), temp2.end());

            executionPlan.push_back(temp);
        }
        else if(traverse->val==2)
        {
            vector<string> temp;
            temp.push_back(traverse->relationName);
            executionPlan.push_back(temp);
        }
        else if(traverse->val==3)
        {
            if(traverse->joinCondition.compare("")!=0)
            {
                vector<string> temp;
                string str = "Join based on ";
                str = str + traverse->joinCondition;
                temp.push_back(str);
                executionPlan.push_back(temp);
            }
            else
            {
                vector<string> temp;
                string str = "Cartesian product ";
                temp.push_back(str);
                executionPlan.push_back(temp);
            }
        }
    return;
    }
}
void printExecPlan(treeNode *project, treeNode * select)
{
    cout<<"\nExecution plan before optimization : \n";
    calcExecPlan(project);

    for(int i = 0; i < executionPlan.size(); i++)
    {
        for(int j = 0; j < executionPlan[i].size(); j++)
        {
            cout<<executionPlan[i][j]<<" ";
        }
        cout<<endl;
    }
    executionPlan.clear();

    cout<<"\nExecution plan after replacing cartesian product with Join : \n";
    mapJoinConditions(select);

    select->conditions = optimizedConditions;
    calcExecPlan(project);

    for(int i = 0; i < executionPlan.size(); i++)
    {
        for(int j = 0; j < executionPlan[i].size(); j++)
        {
            cout<<executionPlan[i][j]<<" ";
        }
        cout<<endl;
    }
    executionPlan.clear();

    cout<<"\nExecution plan after moving up select operations : \n";

    mapOptimizedConditions(select);
    project->left = select->left;
    free(select);
    calcExecPlan(project);

    for(int i = 0; i < executionPlan.size(); i++)
    {
        for(int j = 0; j < executionPlan[i].size(); j++)
        {
            cout<<executionPlan[i][j]<<" ";
        }
        cout<<endl;
    }
    executionPlan.clear();

    cout<<"\nExecution plan after moving up project operations : \n";

    moveProjectOperation(project);
    calcExecPlan(project);

    for(int i = 0; i < executionPlan.size(); i++)
    {
        for(int j = 0; j < executionPlan[i].size(); j++)
        {
            cout<<executionPlan[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}
void printTree(treeNode *project)
{
    treeNode *traverse = new treeNode();
    traverse = project;

    while(traverse != NULL)
    {
        if(traverse->val==0)
        {
            set<string>::iterator it;

            for(it = traverse->attributes.begin(); it!=traverse->attributes.end(); it++)
                cout<<*it<<" ";
            cout<<endl;
            traverse = traverse->left;
        }
        else if(traverse->val==1)
        {
            for(int i=0; i<traverse->conditions.size(); i++)
                cout<<traverse->conditions[i]<<" ";
            cout<<endl;
            traverse = traverse->left;
        }
        else if(traverse->val==3)
        {
            cout<<"X "<<traverse->joinCondition<<endl;

            if(traverse->right->val==1)
            {
                for(int i=0; i<traverse->right->conditions.size(); i++)
                    cout<<traverse->right->conditions[i]<<" ";
                cout<<endl;

                cout<<traverse->right->left->relationName<<endl;
            }
            else
               cout<<traverse->right->relationName<<endl;
            traverse = traverse->left;
        }
        else
        {
            cout<<traverse->relationName<<endl;
            break;
        }
    }
}
