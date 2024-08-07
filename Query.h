#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "AvlTree.h"

using namespace std;

class Query {
public:
    Query();

    // Parses the query entered by the user and updates the finalDocs vector with relevant documents
    vector<pair<string, int>> parseQuery(const std::string& query, 
                    AvlTree<std::string, std::map<string, int>>& wordTree,
                    AvlTree<string, set<string>> & people,
                    AvlTree<string, set<string>> & orgs,
                    AvlTree<std::string, std::string>& stopWords);

private:
    // Helper methods for parsing different aspects of the query
    void parseAndProcessTerms(const std::string& query, 
                              AvlTree<std::string, std::map<string, int>>& wordTree,
                              map<string, int>& finalDocs);

    void parseAndProcessOrgs(const std::string& query, 
                              AvlTree<string, set<string>>& orgs,
                             map<string, int>& finalDocs);

    void parseAndProcessPeople(const std::string& query, 
                                AvlTree<string, set<string>>& people,
                               map<string, int>& finalDocs);

    void excludeTerms(const set<std::string>& terms, 
                      map<string, int>& finalDocs);

    // Method for ranking the results based on relevancy
    vector<pair<string, int>> rankResults(map<string, int>& finalDocs);
};

#endif // QUERY_H
