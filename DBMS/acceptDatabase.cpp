#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include<ctype.h>
#include "makeRelationSchema.h"
#include "globals.h"

using namespace std;

std::map<std::string, std::vector<std::string> > attributeList;

void acceptDatabase()
{
    int numberOfRelations;
//    vector<string> primaryKeys;
//    vector<string> foreignKeys;

    cout<<"Enter number of relations"<<endl;
    cin>>numberOfRelations;

    while(numberOfRelations--)
    {
        cout<<"Enter the relation name"<<endl;
        string relation;
        int numberOfAttributes;

        cin>>relation;
        cout<<"Enter number of attributes"<<endl;
        cin>>numberOfAttributes;
        cout<<"Enter the attribute names"<<endl;

        vector<string> attributes;
        while(numberOfAttributes--)
        {
            string attribute;
            cin>>attribute;

            attributes.push_back(attribute);
        }
        attributeList[relation] = attributes;

//        cout<<"Enter number of primary keys"<<endl;
//        cin>>numberOfPrimaryKeys;
//        cout<<"Enter the primary key names"<<endl;

//        while(numberOfPrimaryKeys--) //change this. try including superkey
//        {
//            string primaryKey;
//            cin>>primaryKey;
//
//            primaryKeys.push_back(primaryKey);
//        }
//
//        cout<<"Enter number of foreign keys"<<endl;
//        cin>>numberOfForeignKeys;
//        cout<<"Enter the foreign key names"<<endl;
//
//        while(numberOfForeignKeys--)
//        {
//            string foreignKey;
//            cin>>foreignKey;
//
//            foreignKeys.push_back(foreignKey);
//        }

        mapAttributesToRelations(relation, attributes);
        //mapJoinCompatible(relation, foreignKeys);
    }
}
