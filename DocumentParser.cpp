#include "DocumentParser.h"
#include "document.h"
#include <fstream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <set>

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"


void DocumentParser::readJsonFile(const string &path, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree) {
    ifstream input(path);
    if (!input.is_open()) {
        cerr << "cannot open file: " << path << endl;
        return;
    }


    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);

    auto val = d["uuid"].GetString();
    auto words = d["text"].GetString();
    auto author = d["author"].GetString();
    auto title = d["title"].GetString();
    auto published = d["published"].GetString();
    document doc(title, val, published, author, words);
    docTree[val]=doc;

    auto persons = d["entities"]["persons"].GetArray();
    for (auto &p : persons) {
        string peopleName = p["name"].GetString();
        for(size_t i = 0; i<peopleName.length(); i++){
            peopleName[i]=tolower(peopleName[i]);
            if(peopleName[i]==' '){
                peopleName[i]='-';
            }
        }
        peopleMap[peopleName].insert(val);
    }

    auto org = d["entities"]["organizations"].GetArray();
    for (auto &o : org) {
        string orgName = o["name"].GetString();
        for(size_t i = 0; i<orgName.length(); i++){
            orgName[i]=tolower(orgName[i]);
            if(orgName[i]==' '){
                orgName[i]='-';
            }            
        }
        orgsMap[orgName].insert(val);   
    }

    vector<string> content;
    content = tokenize(words); //passes in the text

    for(auto &w : content){
        wordTree[w].emplace(val, 0); // if it is there we put it there with a 0 (default value)
        wordTree[w][val]++;
       
    }

    input.close();
    // wordTree.prettyPrintTree();
}

std::vector<string> DocumentParser::tokenize(const string &tweet) {
    std::vector<string> words;  // Assuming stringList is a class or data structure that can hold string objects
    char currentWord[tweet.length() + 1];
    size_t j = 0;

    for (size_t i = 0; i < tweet.length(); ++i) {
        char currentChar = tweet.at(i);

        // check if the current character is a word character
        if (isalnum(currentChar))  // checks if it is alpha or not
        {
            currentWord[j] = tolower(currentChar);  // Append the character to the current word
            ++j;
        } else if (j != 0 && currentChar != '\'') {
            currentWord[j] = '\0';
            words.push_back((string(currentWord)));  // Add the current word to the list of words
            j = 0;                                                           // reset j
        }
    }
    // add the last word if it exists (not separated by a non-word character)
    if (j != 0) {
        currentWord[j] = '\0';
        words.push_back((string(currentWord)));  // Add the current word to the list of words
    }
    return words;
}

void DocumentParser::fileSystem(const string &directoryPath, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree){
    // used recursive iterator so it will go into subfolders
    auto it = filesystem::recursive_directory_iterator(directoryPath);
    readStopWords(stopWordTree);
    documentCount = 0;
    // loop over all the entries.
    for (const auto &entry : it) {
        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            readJsonFile(entry.path().string(), wordTree, peopleMap, orgsMap, stopWordTree, docTree);
            documentCount++;
            if (documentCount % 10000 == 0) {
                cout << documentCount << " files read" << endl;
            }
        }
    }
    cout << documentCount << " files read" << endl;
}

AvlTree<string, string> &DocumentParser::readStopWords(AvlTree<string, string> &stopWordTree) {
    ifstream input;
    input.open("../stopwords.txt");
    if (!input.is_open()) {
        throw runtime_error("Could not open file");
    }
    string word;
    while (getline(input, word)) {
        stopWordTree.insert(word);
    }
    return stopWordTree;
}