#ifndef INDEX_H
#define INDEX_H

#include <map>
#include "AvlTree.h"
#include "DocumentParser.h"

class Index
{
public:
    Index(){};
    void makeWordPersist(AvlTree<string, map<string, int>> &wordTree, string filepath);
    void makeNamePersist(AvlTree<string, set<string>> &nameMap, string filepath);
    void makeDocTreePersist(AvlTree<string, document> &nameMap, string filepath);
    void readWordPersist(AvlTree <string, map<string, int>> &tree, string filepath);
    void readNamePersist(AvlTree<string, set<string>> &nameMap, string filepath);
    void readDocTreePersist(AvlTree<string, document> &nameMap, string filepath);
};

#endif