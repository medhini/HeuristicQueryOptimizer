#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include<ctype.h>
#include "optimizeOperations.h"
#include "parseQuery.h"
#include "acceptDatabase.h"
#include "display.h"

using namespace std;

vector<string> relations;
vector<string> conditions;
set<string> attributes;

vector<string> optimizedConditions;
vector<string> joinConditions;

map<string, string> mapAttribute;
map< string, set<string> >  joinCompatible;

treeNode *insertInto(treeNode *select, treeNode *traverse, treeNode *relation1)
{
    treeNode *joinNode = new treeNode();
    joinNode->val = 3;
    joinNode->left = traverse;
    joinNode->right = relation1;

    select->left = joinNode;

    return joinNode;
}

bool checkRelationNames() //Handles cases where attributes and conditions are from relations which arent selected. eg select pnumber from emp; select pnumber from project where empID=10
{
    set<string>::iterator i1;
    for(i1 = attributes.begin(); i1 != attributes.end(); i1++)
    {
        vector<string> :: iterator it;

        it = find(relations.begin(), relations.end(), mapAttribute[*i1]);

        if(it == relations.end())
            return false;
    }

    for(int i = 0; i < conditions.size(); i++)
    {
        int pos = -1;
        for(int j = 0; j < conditions[i].length(); j++)
        {
            if(conditions[i][j]=='=' || conditions[i][j]=='<' || conditions[i][j]=='!' || conditions[i][j]=='>')
            {
                pos = j;
                break;
            }
        }

        string attrib = conditions[i].substr(0, pos);

        if(attrib.compare("and")==0 || attrib.compare("or")==0 || attrib.compare("AND")==0 || attrib.compare("OR")==0)
            return true;

        vector<string> :: iterator it;

        it = find(relations.begin(), relations.end(), mapAttribute[attrib]);

        if(it == relations.end())
            return false;
    }
    return true;
}

void modifyTree(treeNode *traverse, string optimizedCondition, string relation)
{
    if(traverse->right !=NULL && traverse->right->val==2 && traverse->right->relationName==relation)
    {
        treeNode *newPtr = new treeNode();
        newPtr->val = 1;
        newPtr->conditions.push_back(optimizedCondition);
        newPtr->left = traverse->right;
        newPtr->right = NULL;
        traverse->right = newPtr;

        return;
    }
    else if(traverse->left->val==3)
    {
        modifyTree(traverse->left, optimizedCondition, relation);
    }
    else if(traverse->left->val==2 && traverse->left->relationName==relation)
    {
        treeNode *newPtr = new treeNode();
        newPtr->val = 1;
        newPtr->conditions.push_back(optimizedCondition);
        newPtr->left = traverse->left;
        newPtr->right = NULL;
        traverse->left = newPtr;

        return;
    }
}
void modifyTree(treeNode *traverse, string joinCondition, string relation1, string relation2)
{
    if(traverse->val==3 && (traverse->right->val==2 && traverse->right->relationName==relation1 && traverse->left->val==2 && traverse->left->relationName==relation2)||(traverse->right->val==2 && traverse->right->relationName==relation2 && traverse->left->val==2 && traverse->left->relationName==relation1))
    {
        traverse -> joinCondition = joinCondition;
        return;
    }
    else if((traverse->val==3) && (traverse->left->val==3 && (traverse->right->relationName==relation1 || traverse->right->relationName==relation2)))
    {
        traverse -> joinCondition = joinCondition;
        return;
    }
    else
    {
        modifyTree(traverse->left, joinCondition, relation1, relation2);
    }
}

int main()
{
    acceptDatabase();

    string query;

    string ch;
    getline(cin, ch);

    cout<<"Enter the query"<<endl;
    getline(cin, query);

    partitionQuery(query);
    categorizeConditions();
    reorderQuery();

    if(!checkRelationNames())
    {
        cout<<"Error in Query. Exit"<<endl;
        exit(0);
    }

    treeNode *project = new treeNode();
    treeNode *select = new treeNode();

    project->val = 0;
    project->attributes = attributes;
    project->right = NULL;

    select->val = 1;
    select->conditions = conditions;
    select->right = NULL;

    project->left = select;

    treeNode *traverse = new treeNode();

    if(relations.size() == 0)
        select->left=NULL;

    else if(relations.size() == 1)
    {
        treeNode *relation = new treeNode();
        relation->val = 2;
        relation->relationName = relations[0];
        relation->left = NULL;
        relation->right = NULL;

        select->left = relation;
    }

    else
    {
        treeNode *relation1 = new treeNode();
        relation1->val = 2;
        relation1->relationName = relations[0];
        relation1->left = NULL;
        relation1->right = NULL;

        treeNode *relation2 = new treeNode();
        relation2->val = 2;
        relation2->relationName = relations[1];
        relation2->left = NULL;
        relation2->right = NULL;

        treeNode *joinNode  = new treeNode();
        joinNode->val = 3;
        joinNode->left = relation1;
        joinNode->right = relation2;

        traverse = joinNode;
        select->left = joinNode;

        if(relations.size() >= 3)
        {
            for(int i = 2; i < relations.size(); i++)
            {
                treeNode *relation1 = new treeNode();
                relation1->val = 2;
                relation1->relationName = relations[i];
                relation1->left = NULL;
                relation1->right = NULL;

                traverse = insertInto(select, traverse, relation1);
            }
        }
    }
    printExecPlan(project, select);

    return 0;
}

