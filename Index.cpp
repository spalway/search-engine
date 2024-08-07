#include "Index.h"

void Index::makeWordPersist(AvlTree<string, map<string, int>> &wordTree, string filepath){
    wordTree.writeIndex(filepath, wordTree);
}

void Index::makeNamePersist(AvlTree<string, set<string>> &nameMap, string filepath){
    nameMap.writeIndex(filepath, nameMap);
}

void Index::readWordPersist(AvlTree <string, map<string, int>> &tree, string filepath){
    ifstream file(filepath);
    if(file.is_open()==false){
        cerr<<"the file cannot open!"<<endl;
    }

    while(file.eof()==false){
        string key;
        string uuid;
        int frequency;
        map<string, int> currentMap;
        file>>key;
        while(file.eof()==false){
            file>>uuid;
            if(uuid==";"){
                break;
            }
            file>>frequency;
            currentMap.emplace(uuid, frequency);
        }
        if (currentMap.empty() == false){
            tree[key] = currentMap;
        }
    }
}

void Index::readNamePersist(AvlTree<string, set<string>> &tree, string filepath){
    ifstream file(filepath);
    if(file.is_open()==false){
        cerr<<"the file cannot open!"<<endl;
    }
    
    while(file.eof()==false){
        string key;
        string uuid;
        set<string> currentSet;
        file>>key;
        while(file.eof()==false && uuid != ";"){
            file>>uuid;
        }
        currentSet.emplace(uuid);
        if (currentSet.empty() == false){
            tree[key] = currentSet;
        }
    }
}

void Index::makeDocTreePersist(AvlTree<string, document> &docTree, string filepath){
    docTree.writeIndex(filepath, docTree);
}

void Index::readDocTreePersist(AvlTree<string, document> &docTree, string filepath){
    ifstream file(filepath);
    if(file.is_open()==false){
        cerr<<"the file cannot open!"<<endl;
    }
    
    while(file.eof()==false){
        string uuid;
        file>>uuid;

        document doc;
        string title;
        string identifier;
        string publicationDate;
        string authorName;
        string content;
        getline(file, title);
        doc.title = title;
        file >> identifier;
        doc.identifier = identifier;
        file >> publicationDate;
        doc.publicationDate = publicationDate;
        getline(file, authorName);
        doc.authorName = authorName;
        getline(file, content);
        doc.content = content;
        docTree[uuid] = doc;
    }
}

