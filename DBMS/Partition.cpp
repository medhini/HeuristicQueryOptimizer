#include<iostream>
#include<bits/stdc++.h>
#include "globals.h"

using namespace std;

void partitionQuery(string query)
{
    int l = query.length();
    int pos = 0;

    vector<string> words;

    for(int i=0; i<l; i++)
    {
        if(query[i]==' ' || query[i]==',')
        {
            if(i-pos==0)
            {
                pos = i + 1;
                continue;
            }
            string word = query.substr(pos, i - pos);

            words.push_back(word);
            pos = i + 1;
        }
    }
    string word = query.substr(pos, l - pos);
    words.push_back(word);

    int flag = 0;

    for(int i = 0; i < words.size(); i++)
    {
        if(words[i].compare("select")==0)
        {
            flag = 1;
            continue;
        }

        if(words[i].compare("from")==0)
        {
            flag = 2;
            continue;
        }

        if(words[i].compare("where")==0)
        {
            flag = 3;
            continue;
        }

        if(flag==1)
            attributes.push_back(words[i]);

        if(flag == 2)
            relations.push_back(words[i]);

        if(flag == 3)
            conditions.push_back(words[i]);
    }

     /*for(int i=0; i<attributes.size(); i++)
        cout<<attributes[i]<<endl;

    for(int i=0; i<relations.size(); i++)
        cout<<relations[i]<<endl;

    for(int i=0; i<conditions.size(); i++)
        cout<<conditions[i]<<endl;*/
}
