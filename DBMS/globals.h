#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

extern std::vector<std::string> relations;
extern std::vector<std::string> conditions;
extern std::set<std::string> attributes;

extern std::vector<std::string> optimizedConditions;
extern std::vector<std::string> joinConditions;
extern std::vector< std::pair<int, std::string> > relationCount;

extern std::map<std::string, std::string> mapAttribute;
extern std::map<std::string, std::vector<std::string> > attributeList;
extern std::map< std::string, std::set<std::string> >  joinCompatible;
//extern std::map< std::string, std::set<std::string> >  projectAttributes;

struct treeNode
{
    int val; //0 is project, 1 is select, 2 is relation, 3 is join node

    std::vector<std::string> conditions;
    std::set<std::string> attributes;
    std::string relationName;
    std::string joinCondition;

    treeNode* left;
    treeNode* right;
};

void modifyTree(treeNode *traverse, std::string optimizedCondition, std::string relation);
void modifyTree(treeNode *traverse, std::string optimizedCondition, std::string relation1, std::string relation2);

#endif // GLOBALS_H_INCLUDED
