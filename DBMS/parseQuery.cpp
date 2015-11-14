#include<iostream>
#include<bits/stdc++.h>
#include "globals.h"

using namespace std;

std::vector< std::pair<int, std::string> > relationCount;
vector<string> relationTemp;
map<string, int> relationEntry;

bool compare(pair<int, string> a,pair<int, string> b)
{
    if(a.first>b.first)
        return true;
    return false;
}

void reorderQuery()
{
    for(int i = 0; i < joinConditions.size(); i++)
    {
        int pos = (joinConditions[i].find_first_of('=') || joinConditions[i].find_first_of('!') || joinConditions[i].find_first_of('>') || joinConditions[i].find_first_of('<') );

        string lValue = joinConditions[i].substr(0, pos);
        string rValue = joinConditions[i].substr(pos+1, joinConditions[i].length()-pos-1);

        string relation1 = mapAttribute[lValue];
        string relation2 = mapAttribute[rValue];

        if(relationCount.size() == 0)
        {
            relationCount.push_back(make_pair(1, relation1));

            if(relation1.compare(relation2)!=0)
                relationCount.push_back(make_pair(1, relation2));
        }
        else
        {
            int mark = 0;

            for(int j = 0; j < relationCount.size(); j++)
            {
                if(relationCount[j].second.compare(relation1) == 0)
                {
                    relationCount[j].first += 1;
                    mark += 1;
                }
                else if(relationCount[j].second.compare(relation2) == 0)
                {
                    relationCount[j].first += 1;
                    mark += 2;
                }
            }

            if(mark == 1)
            {
                relationCount.push_back(make_pair(1, relation2));
               // cout<<relation2<<endl;

            }
            else if(mark == 2)
            {
                relationCount.push_back(make_pair(1, relation1));
               // cout<<relation1<<endl;
            }
            else if(mark == 0)
            {
                relationCount.push_back(make_pair(1, relation1));
                if(relation1.compare(relation2)!=0)
                    relationCount.push_back(make_pair(1, relation2));
               // cout<<relation1<<" "<<relation2<<endl;
            }
        }
        relationEntry[relation1] += 1;
        relationEntry[relation2] += 1;
    }
    sort(relationCount.begin(), relationCount.end(), compare);

    relations.clear();

    for(int i = 0; i < relationCount.size(); i++)
    {
        relations.push_back(relationCount[i].second);
    }

    for(int i = 0; i < relationTemp.size(); i++)
    {
        if(relationEntry[relationTemp[i]]==1)
        {
            relations.push_back(relationTemp[i]);
        }
    }

}
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
        if(words[i].compare("select")==0 || words[i].compare("SELECT")==0)
        {
            flag = 1;
            continue;
        }
        if(words[i].compare("from")==0|| words[i].compare("FROM")==0)
        {
            flag = 2;
            continue;
        }
        if(words[i].compare("where")==0 || words[i].compare("WHERE")==0)
        {
            flag = 3;
            continue;
        }

        if(flag == 1)
            attributes.insert(words[i]);

        if(flag == 2)
        {
            relationTemp.push_back(words[i]);
            relations.push_back(words[i]);
            relationEntry[words[i]] = 1;
        }

        if(flag == 3)
            conditions.push_back(words[i]);
    }
    string s = *attributes.begin();
    if(attributes.size()==1 && s.compare("*")==0)
    {
        attributes.clear();

        for(int i = 0; i < relations.size(); i++)
        {
            for(int j = 0; j < attributeList[relations[i]].size(); j++)
            {
               attributes.insert(attributeList[relations[i]][j]);
            }
        }
    }

     /*for(int i=0; i<attributes.size(); i++)
        cout<<attributes[i]<<endl;

    for(int i=0; i<relations.size(); i++)
        cout<<relations[i]<<endl;

    for(int i=0; i<conditions.size(); i++)
        cout<<conditions[i]<<endl;*/
}

