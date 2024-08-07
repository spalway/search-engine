#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "document.h"

using namespace std;

template <typename Key, typename Value>
class AvlTree {
   private:
    struct AvlNode {
        Key k;           // key of the node
        Value v;         // value associated with the key
        AvlNode *left;   // pointer to the left child
        AvlNode *right;  // pointer to the right child
        int height;      // height of the node in the AVL tree

        //constructors for creating nodes
        AvlNode(const Key &k, Value &v, AvlNode *lt, AvlNode *rt, int h = 0)
            : k{k}, v{v}, left{lt}, right{rt}, height{h} {}

        AvlNode(const Key &k, AvlNode *lt, AvlNode *rt, int h = 0)
            : k{k}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root; //pointer to the top of the node

   public:
    AvlTree() : root{nullptr} {};
    AvlTree(const AvlTree &rhs);
    ~AvlTree();
    AvlTree &operator=(const AvlTree &rhs);
    bool contains(const Key &k) const;
    bool isEmpty() const;
    void printTree() const;
    void prettyPrintTree() const;
    void makeEmpty();
    void insert(const Key &k);
    void remove(const Key &k);
    Value &getValues(Key K);
    Value &operator[](const Key &K);
    void check_balance();
    vector<Key> getKeys();
    int size();
    void writeIndex(string &, AvlTree<string, map<string,int>> &);
    void writeIndex(string &, AvlTree<string, set<string>> &);
    void writeIndex(string &, AvlTree<string, document> &);

   private:
    int size(AvlNode *node);
    int check_balance(AvlNode *node);
    Value &getValues(Key K, AvlNode *t);
    Value &bracketHelper(Key x, AvlNode *&t);
    void insert(const Key &x, AvlNode *&t);
    void remove(const Key &x, AvlNode *&t);
    AvlNode *removeMin(AvlNode *&t);
    AvlNode *findMin(AvlNode *t) const;
    bool contains(const Key &x, AvlNode *t) const;
    void makeEmpty(AvlNode *&t);
    AvlNode *clone(AvlNode *t) const;
    void prettyPrintTree(const string &prefix, const AvlNode *node, bool isRight) const;
    int height(AvlNode *t) const;
    static const int ALLOWED_IMBALANCE = 1;  // 1 is the default; more will make balancing cheaper but the search less efficient!!!
    void balance(AvlNode *&t);
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(AvlNode *&k2);
    void rotateWithRightChild(AvlNode *&k1);
    void doubleWithLeftChild(AvlNode *&k3);
    void doubleWithRightChild(AvlNode *&k1);
    void getKeys(vector<Key> &, AvlNode *node, int level);

    void writeIndex(ostream &, AvlTree<string, map<string,int>> &, AvlNode *);
    void writeIndex(ostream &, AvlTree<string, set<string>> &, AvlNode *);
    void writeIndex(ostream &, AvlTree<string, document> &, AvlNode *);
};

//copy constructor
template <typename Key, typename Value>
AvlTree<Key, Value>::AvlTree(const AvlTree<Key, Value> &rhs) : root{nullptr} {
    root = clone(rhs.root);
}

// destructor
template <typename Key, typename Value>
AvlTree<Key, Value>::~AvlTree()  
{
    makeEmpty();
}

//assignment operator
template <typename Key, typename Value>
AvlTree<Key, Value> &AvlTree<Key, Value>::operator=(const AvlTree<Key, Value> &rhs) {
    makeEmpty();
    root = clone(rhs.root);
    return *this;
}

//returns true if x is found in the tree.
template <typename Key, typename Value>
bool AvlTree<Key, Value>::contains(const Key &k) const {
    return contains(k, root);
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <typename Key, typename Value>
bool AvlTree<Key, Value>::isEmpty() const {
    return root == nullptr;
}

//Print the tree contents in sorted order.
template <typename Key, typename Value>
void AvlTree<Key, Value>::printTree() const {
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

//print the tree structure
template <typename Key, typename Value>
void AvlTree<Key, Value>::prettyPrintTree() const {
    prettyPrintTree("", root, false);
}

//empty the tree
template <typename Key, typename Value>
void AvlTree<Key, Value>::makeEmpty() {
    makeEmpty(root);
}

//insert x into the tree; duplicates are ignored.
template <typename Key, typename Value>
void AvlTree<Key, Value>::insert(const Key &k) {
    insert(k, root);
}

//remove x from the tree. Nothing is done if x is not found.
template <typename Key, typename Value>
void AvlTree<Key, Value>::remove(const Key &k) {
    remove(k, root);
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(string & filePath, AvlTree<string, map<string,int>> & tree){
    ofstream file(filePath);
    if(file.is_open()==false){
        cerr<<"could not open file!"<<endl;
    }
    writeIndex(file, tree, tree.root);
    file.close();
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(string & filePath, AvlTree<string, set<string>> & tree) {
    ofstream file(filePath);
    if(file.is_open()==false){
        cerr<<"could not open file!"<<endl;
    }
    writeIndex(file, tree, tree.root);
    file.close();
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(string & filePath, AvlTree<string, document> & tree) {
    ofstream file(filePath);
    if(file.is_open()==false){
        cerr<<"could not open file!"<<endl;
    }
    writeIndex(file, tree, tree.root);
    file.close();
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::insert(const Key &x, AvlNode *&t) {
    if (t == nullptr) {
        t = new AvlNode{x, nullptr, nullptr, 0};
        return;  // single node is always balanced
    }

    if (x < t->k)
        insert(x, t->left);
    else if (t->k < x)
        insert(x, t->right);
    else {
    }  // Duplicate; do nothing

    // This will call balance on the way back up the tree. It will only balance once where the tree got imbalanced.
    balance(t);
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Key, typename Value>
void AvlTree<Key, Value>::remove(const Key &x, AvlNode *&t) {
    // recursively find the node to delete using binary search

    if (t == nullptr)
        return;  // Item not found; do nothing

    // must be in left subtree
    if (x < t->k)
        return remove(x, t->left);

    // must be in right subtree
    if (t->k < x)
        return remove(x, t->right);

    // we get here only for t->element == x

    // Cases:
    // A. No children: Just remove the node.
    if (t->left == nullptr && t->right == nullptr) {
        delete t;
        t = nullptr;
        return;
    }

    // C. Two children case: replace element with the smallest element in the right subtree.
    if (t->left != nullptr && t->right != nullptr) {
        AvlNode *replacement = removeMin(t->right);
        replacement->right = t->right;
        replacement->left = t->left;

        delete t;
        t = replacement;
        return;
    }

    // B. One child case: replace the node with the only child.
    AvlNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;

    balance(t);
}

//Internal method to find, remove and return the smallest item in a subtree t.

template <class Key, class Value>
typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::removeMin(AvlTree<Key, Value>::AvlNode *&t) {
    // recursive implementation
    // special case: no root node
    if (t == nullptr)
        return nullptr;

    // special case: root is the minimum
    if (t->left == nullptr) {
        AvlNode *min = t;
        t = t->right;
        return min;
    }

    // traverse down left to the leaf
    if (t->left->left == nullptr) {
        AvlNode *min = t->left;
        t->left = min->right;
        return min;
    }

    return removeMin(t->left);
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::findMin(AvlTree<Key, Value>::AvlNode *t) const {
    if (t == nullptr)
        return nullptr;

    if (t->left == nullptr)
        return t;

    return findMin(t->left);
}

/**
 * Internal method to test if an item is in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 */
template <typename Key, typename Value>
bool AvlTree<Key, Value>::contains(const Key &x, AvlNode *t) const {
    if (t == nullptr)
        return false;

    else if (x < t->k)
        return contains(x, t->left);
    else if (t->k < x)
        return contains(x, t->right);
    else
        return true;  // if match
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::makeEmpty(AvlNode *&t) {
    if (t == nullptr)
        return;

    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = nullptr;
}

//internal method to clone subtree
template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::clone(AvlTree<Key, Value>::AvlNode *t) const {
    if (t == nullptr)
        return nullptr;

    return new AvlNode{t->k, t->v, clone(t->left), clone(t->right), t->height};
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::prettyPrintTree(const string &prefix, const AvlNode *node, bool isRight) const {
    if (node == nullptr)
        return;

    cout << prefix;
    cout << (isRight ? "├──" : "└──");
    // print the key of the node
    cout << node->k << endl;

    // enter the next tree level - left and right branch
    prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
    prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
}

//return the height of node t or -1 if nullptr.
template <typename Key, typename Value>
int AvlTree<Key, Value>::height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}

//assume t is balanced or within one of being balanced since we check this after each manipulation
template <typename Key, typename Value>
void AvlTree<Key, Value>::balance(AvlNode *&t) {
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
    {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);  // case 1 (outside)
        else
            doubleWithLeftChild(t);                                     // case 2 (inside)
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // unbalancing insertion was right
    {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);  // case 4 (outside)
        else
            doubleWithRightChild(t);  // case 3 (inside)
    }

    // update height
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <typename Key, typename Value>
int AvlTree<Key, Value>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::rotateWithLeftChild(AvlNode *&k2) {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::rotateWithRightChild(AvlNode *&k1) {
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::doubleWithLeftChild(AvlNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::doubleWithRightChild(AvlNode *&k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::check_balance() {
    check_balance(root);
}

template <typename Key, typename Value>
int AvlTree<Key, Value>::check_balance(AvlNode *node) {
    if (node == nullptr) {
        return -1;
    }

    int lHeight = check_balance(node->left) + 1;
    int rHeight = check_balance(node->right) + 1;

    if (lHeight - rHeight > 1) {
        throw invalid_argument("tree is not balance.");
    }

    int trueNodeHeight = std::max(lHeight, rHeight);

    if (trueNodeHeight != node->height) {
        throw invalid_argument("node does not have correct height value.");
    }

    return trueNodeHeight;
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::getValues(Key K) {
    return getValues(K, root);
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::operator[](const Key &K) {
    return bracketHelper(K, root);
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::getValues(Key x, AvlNode *t) {
    if (t == nullptr) {
        throw runtime_error("Tree is empty");
    }

    if (x < t->k)
        return getValues(x, t->left);
    else if (t->k < x)
        return getValues(x, t->right);
    else
        return t->v;  // if match
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::bracketHelper(Key x, AvlNode *&t) {
    if (t == nullptr) {
        t = new AvlNode{x, nullptr, nullptr, 0};
        return t->v;  // single node is always balanced
    }
    if (x < t->k)
        return bracketHelper(x, t->left);
    else if (t->k < x)
        return bracketHelper(x, t->right);
    else
        return t->v;  // if match
}

template <typename Key, typename Value>
vector<Key> AvlTree<Key, Value>::getKeys() {
    vector<Key> keys;
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        getKeys(keys, root, i);
    }
    return keys;
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::getKeys(vector<Key> &keys, AvlNode *node, int level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
        keys.emplace_back(node->k);
    } else if (level > 1) {
        getKeys(keys, node->left, level - 1);
        getKeys(keys, node->right, level - 1);
    }
}

template <typename Key, typename Value>
int AvlTree<Key, Value>::size() {
    return size(root);
}

template <typename Key, typename Value>
int AvlTree<Key, Value>::size(AvlNode *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return (size(node->left) + 1 + size(node->right));
    }
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(ostream & file, AvlTree<string, map<string,int>> & tree, AvlNode * t){
    if(t == nullptr){
        return;
    }
    //print current node
    file<< t->k <<" ";
    for(auto &p: t->v){
        file<<p.first<<" ";
        file<<p.second<<" ";
    }
    file<<"; ";

    writeIndex(file,tree,t->left);
    writeIndex(file,tree,t->right);

}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(ostream & file, AvlTree<string, set<string>> & tree, AvlNode * t){
    if(t == nullptr){
        return;
    }
    //print current node
    file<< t->k <<" ";
    for(auto &p: t->v){
        file<<p<<" ";
    }
    file<<"; ";

    writeIndex(file,tree,t->left);
    writeIndex(file,tree,t->right);
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::writeIndex(ostream & file, AvlTree<string, document> & tree, AvlNode * t){
    if(t == nullptr){
        return;
    }
    //print current node
    file<< t->k <<" ";
    file<< t->v.title << endl;
    file<< t->v.identifier << ' ';
    file<< t->v.publicationDate << ' ';
    file<< t->v.authorName << endl;

    for (auto& ch :t->v.content) {
        if (isspace(ch)) {
            ch = ' ';
        }
    }

    file<< t->v.content << endl;

    writeIndex(file,tree,t->left);
    writeIndex(file,tree,t->right);
}


#endif