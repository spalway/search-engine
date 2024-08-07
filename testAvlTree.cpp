#define CATCH_CONFIG_MAIN
#include <string>
#include "catch_setup.h"
#include "catch.hpp"
#include "AvlTree.h"
#include <unordered_map>

using namespace std;

TEST_CASE("Check that AVLTree works", "[AVLTree]")
{
    AvlTree<string, map<string, int>> tree;
    REQUIRE(tree.isEmpty() == true);

    //insert elemets to the AVL tree
    tree.insert("hello");
    tree.insert("world");
    tree.insert("foo");
    tree.insert("chicken");
    tree.insert("dog");

    // Add an element to the unordered_map associated with the "dog" key.
    tree["dog"]["23243256"] = 2;

    // Check that the tree is not empty after insertions.
    REQUIRE(tree.isEmpty() == false);

    // Check that specific elements are present in the tree.
    REQUIRE(tree.contains("hello") == true);
    REQUIRE(tree.contains("world") == true);
    REQUIRE(tree.contains("foo") == true);
    REQUIRE(tree.contains("chicken") == true);
    REQUIRE(tree.contains("dog") == true);

    // Check the value associated with a specific key in the tree.
    REQUIRE(tree["dog"]["23243256"] == 2);

    // Check that a specific key is not present in the tree.
    REQUIRE(tree.contains("cat") == false);

    //remove element from the tree
    tree.remove("chicken");
    REQUIRE(tree.contains("chicken") == false);

    //create a copy of the tree to check if it contains the same elements.
    AvlTree<string, map<string, int>> treeCopy;
    treeCopy = tree;
    REQUIRE(treeCopy.contains("hello") == true);
    REQUIRE(treeCopy.contains("world") == true);
    REQUIRE(treeCopy.contains("foo") == true);
    REQUIRE(treeCopy.contains("dog") == true);
    REQUIRE(treeCopy["dog"]["23243256"] == 2);

    //check to see a key that is not present
    REQUIRE(treeCopy.contains("cat") == false);
    //check if the copied tree is empty
    treeCopy.makeEmpty();

    // Test exception handling when trying to get values for a key in an empty tree.
    bool errorFound = false;
    try{
        treeCopy.getValues("hello");
    }
    catch(const runtime_error& e){
        errorFound = true;
    }
    REQUIRE(errorFound);

    // test AVLTree balancing
    tree.insert("elephant");
    tree.insert("giraffe");

    // check if the tree is balanced after insertions
    tree.check_balance();  //  will throw an exception if the tree is not balanced

    // test AVLTree remove operation
    tree.remove("foo");
    REQUIRE(tree.contains("foo") == false);
}
