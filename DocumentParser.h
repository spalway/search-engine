#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

// rapidjson headers needed for parsing
#include <string>
#include <vector>
#include <map>
#include <set>

#include "AvlTree.h"
#include "document.h"
#include "hash.h"
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

using namespace std;
using namespace rapidjson;

class DocumentParser {
private:
    int documentCount = 0;  // keeps track of the document number
public:
    void readJsonFile(const string &path, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree);
    void fileSystem(const string &directoryPath, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree);
    std::vector<string> tokenize(const string &tweet);
    AvlTree<string, string> &readStopWords(AvlTree<string, string> &);

    int getDocumentCount() {
        return documentCount;
    };
};
#endif //DOCUMENTPARSER_H
