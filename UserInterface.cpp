#include "UserInterface.h"

using namespace std;

void UserInterface::displayMenu() {
    while (true) {
        cout << "Welcome to Super Search!" << endl;
        cout << "Enter 1 to create index from documents" << endl;
        cout << "Enter 2 to write the index to a file" << endl;
        cout << "Enter 3 to read an index from a file" << endl;
        cout << "Enter 4 to enter a query" << endl;
        cout << "Enter 5 to output statistics" << endl;
        cout << "Enter 0 to exit" << endl;

        string answer;
        cin >> answer;
        int answerInt = stoi(answer);
        switch (answerInt) {
            case 1: {
                cout << "Please enter path for documents" << endl;
                string path;
                cin >> path;
                createIndex(path);
                break;
            }
            case 2:
                writeIndex();
                break;
            case 3:
                readIndex();
                break;
            case 4:{
                cout << "Enter query: ";
                string choice;
                cin.ignore();
                cin.clear();
                getline(cin, choice);
                enterQuery(choice, true);
                break;
            }
            case 5:
                outputStatistics();
                break;
            case 0:
                return;
            default:
                cout << "Please enter a valid number" << endl;
                break;
        }
    }
}
void UserInterface::createIndex(string path) {
    auto start = high_resolution_clock::now();
    cout << "Creating index..." << endl;
    DocumentParser parser;

    parser.fileSystem(path, wordTree, people, orgs, stopWords, docTree);
    numDocs = parser.getDocumentCount();

    auto stop = high_resolution_clock::now();
    time = duration_cast<microseconds>(stop - start);
}
void UserInterface::writeIndex() {
    cout << "Writing index to file..." << endl;
    Index index;
    index.makeWordPersist(wordTree, "../wordsPersist.txt");
    index.makeNamePersist(people, "../peoplePersist.txt");
    index.makeNamePersist(orgs, "../orgPersist.txt");
    index.makeDocTreePersist(docTree, "../docsPersist.txt");
    return;
}
void UserInterface::readIndex() {
    cout << "Reading index from persistence..." << endl;
    Index index;
    index.readWordPersist(wordTree, "../wordsPersist.txt");
    index.readNamePersist(people, "../peoplePersist.txt");
    index.readNamePersist(orgs, "../orgPersist.txt");
    index.readDocTreePersist(docTree, "../docsPersist.txt");
    return;
}
void UserInterface::enterQuery(string choice, bool letOpen) {
    Query query;
    finalDocs = query.parseQuery(choice, wordTree, people, orgs, stopWords);
    if (finalDocs.empty()) {
        cout << "No results found" << endl;
    } else {
        int i = 0;
        for (auto &d : finalDocs) {
            document doc = docTree.getValues(d.first);
            cout << i + 1 << endl;
            cout << "Title: " << doc.title << endl;
            cout << "UUID: " << doc.identifier << endl;
            cout << "Author: " << doc.authorName << endl;
            cout << "Published: " << doc.publicationDate << endl;
            cout << endl;
            i++;
            if (i >= 15)
                break;
        }
        while (letOpen) {
            cout << "Enter the document number you want to view. Enter to 0 to return to menu" << endl;
            string num;
            cin >> num;
            int numInt = stoi(num);
            if (numInt < 0 || numInt > finalDocs.size()) {
                cout << "Please enter a valid document number" << endl;
                continue;
            }
            if (numInt == 0) {
                break;
            }
            cout << "Text: " << docTree.getValues(finalDocs.at(numInt - 1).first).content << endl;
        }
    }

    return;
}
void UserInterface::outputStatistics() {
    cout << "Statistics:" << endl;
    cout << "Time taken to index: " << time.count() << " microseconds" << endl;
    cout << "Total Number of Unique words: " << wordTree.size() << endl;
    cout << "Total Number of Documents: " << numDocs << endl;
    cout << "Total Number of People: " << people.size() << endl;
    cout << "Total Number of Orgs: " << orgs.size() << endl;

    wordTree.makeEmpty();

    return;
}
