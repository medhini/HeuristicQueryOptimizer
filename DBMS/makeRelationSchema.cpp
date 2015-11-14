#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include "globals.h"

using namespace std;

void mapAttributesToRelations(string relation, vector<string> attributes)
{
    for(int i = 0; i < attributes.size(); i++)
    {
        mapAttribute[attributes[i]]=relation;
    }
}

//void mapJoinCompatible(string relation, vector<string> foreignKeys)
//{
//    set<string> temp;
//
//    for(int i = 0; i < foreignKeys.size(); i++)
//    {
//        temp.insert(mapAttribute[foreignKeys[i]]);
//    }
//
//    joinCompatible[relation] = temp;
//}
