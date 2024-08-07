#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Index.h"
#include "AvlTree.h"
#include <string>
#include <map>
#include <set>

using namespace std;

TEST_CASE("AVL Tree Population and Size Verification", "[Index]") {
    Index index;
    AvlTree<string, map<string, int>> wordTree;
    AvlTree<string, set<string>> nameTree;
    AvlTree<string, document> docTree;

    //check for word tree
    SECTION("Check Word Tree Insertion") {
        wordTree.insert("word1");
        wordTree.insert("word2");
        REQUIRE(wordTree.size() == 2);
    }
    //check for name tree
    SECTION("Check Name Tree Insertion") {
        nameTree.insert("Name1");
        nameTree.insert("Name2");
        REQUIRE(nameTree.size() == 2);
    }
    //check for document tree
    SECTION("Check Document Tree Insertion") {
        docTree.insert("doc1");
        docTree.insert("doc2");
        REQUIRE(docTree.size() == 2);
    }
}