#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <math.h>

#include <chrono>
#include <set>

#include "AvlTree.h"
#include "DocumentParser.h"
#include "Index.h"
#include "Query.h"
#include "document.h"

using namespace std;
using namespace chrono;
class UserInterface {
   private:
   public:
    AvlTree<string, map<string, int>> wordTree;
    AvlTree<string, set<string>> people;
    AvlTree<string, set<string>> orgs;
    AvlTree<string, document> docTree;
    AvlTree<string, string> stopWords;
    vector<pair<string, int>> finalDocs;
    chrono::microseconds time;
    int numDocs;
    void displayMenu();
    void createIndex(string path);
    void writeIndex();  // tree to file
    void readIndex();   // file to tree
    void enterQuery(string query, bool letOpen);
    void outputStatistics();
    const vector<pair<string, int>>& readQueryResults() { return finalDocs; }
};

#endif