#include "Query.h"
#include <sstream>
#include <algorithm>

Query::Query() {
    // Constructor implementation (if needed)
}

vector<pair<string, int>> Query::parseQuery(const std::string& query, 
                       AvlTree<std::string, map<string, int>>& wordTree,
                        AvlTree<string, set<string>>& people,
                       AvlTree<string, set<string>>& orgs,
                       AvlTree<string, string>& stopWords) {
    // Reset finalDocs for new query
    map<string, int> finalMap;
    set<string> exclusionSet;

    // Split query into words
    istringstream queryStream(query);
    string word;
    while (queryStream >> word) {
        for(size_t i = 0; i < word.length();i++){
            word[i]=tolower(word[i]);
        }
        // Check for special operators ORG and PERSON
        if (word.find("org:") == 0) {
            parseAndProcessOrgs(word.substr(4), orgs, finalMap);
        } else if (word.find("person:") == 0) {
            parseAndProcessPeople(word.substr(7), people, finalMap);
        } else if (word.empty() == false && word[0] != '-') {
            parseAndProcessTerms(word, wordTree, finalMap);
        } else if (word.empty() == false){
            exclusionSet.insert(word.substr(1));
        }
    }
    excludeTerms(exclusionSet, finalMap);
    return rankResults(finalMap);
}

void Query::parseAndProcessTerms(const std::string& term, 
                                 AvlTree<std::string, map<string, int>>& wordTree,
                                 map<string, int>& finalMap) {
    // Implement the logic to parse and process terms
    if (wordTree.contains(term)) {
        map<string, int> docs = wordTree.getValues(term);
        if(finalMap.empty()){
            finalMap=docs;
            return;
        }
        auto iter = finalMap.begin();
        while(iter != finalMap.end()){
            if(docs.count(iter->first)==false){
                iter = finalMap.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

void Query::parseAndProcessOrgs(const std::string& org, 
                                 AvlTree<string, set<string>>& orgs,
                                map<string, int>& finalMap) {
    // Implement the logic to parse and process organization names
    // todo: later
    if (orgs.contains(org)) {
        set<string> docs = orgs.getValues(org);
        if(finalMap.empty()){
            for (auto& uuid: docs) {
                finalMap.emplace(uuid, 1);
            }
            return;
        }
        auto iter = finalMap.begin();
        while(iter != finalMap.end()){
            if(docs.count(iter->first)==false){
                iter = finalMap.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

void Query::parseAndProcessPeople(const std::string& person, 
                                   AvlTree<string, set<string>>& people,
                                  map<string, int>& finalMap) {
    // Implement the logic to parse and process people names
    // todo: later
    if (people.contains(person)) {
        set<string> docs = people.getValues(person);
        if(finalMap.empty()){
            for (auto& uuid: docs) {
                finalMap.emplace(uuid, 1);
            }
            return;
        }
        auto iter = finalMap.begin();
        while(iter != finalMap.end()){
            if(docs.count(iter->first)==false){
                iter = finalMap.erase(iter);
            } else {
                iter++;
            }
        }
    }
}



void Query::excludeTerms(const set<std::string>& terms, 
                         map<string, int>& finalMap) {
    // Implement the logic to exclude certain terms
    for (auto& term: terms) {
        finalMap.erase(term);
    }
}

vector<pair<string, int>> Query::rankResults(map<string, int>& finalMap) {
    // Implement the ranking algorithm (e.g., TF-IDF)
    vector<pair<string, int>> finalResults(finalMap.begin(), finalMap.end());
    sort(finalResults.begin(), finalResults.end(), 
         [](const pair<string, int> &a, const pair<string, int> &b) { return a.second > b.second; });
    return finalResults;
}
