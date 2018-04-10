#pragma once

#include <iostream>
#include <tuple>
#include <vector>

#include "Printer.h"
using namespace std;
using KeyType = int64_t;
using ValueType = int64_t;

class InternalNode;
class LeafNode;
class Node;

// Main class for B+ Tree.
class BPlusTree
{
public:

    /// B+ Tree constructor.  Accepts an optional order for the B+ Tree.
    explicit BPlusTree(int aOrder = 4);
    
    /// The type used in the API for inserting a new key-value pair
    /// into the tree.  The third item is the type of the Node into
    /// which the key will be inserted.
    using EntryType = tuple<KeyType, ValueType, LeafNode*>;
    
    /// Check if the B+ tree has no keys or values, true if tree is empty, false otherwise.
    bool isEmpty() const;
    
    /// Insert a key-value pair into the B+ tree.
    void insert(KeyType aKey, ValueType aValue);
    
    /// Remove a key-value pair from the B+ tree.
    void remove(KeyType aKey);
    
    /// Print the B+ tree to stdout using a simple command-line
    void print();

    /// Remove all elements from the B+ tree. You can then build
    /// it up again by inserting new elements into it.
    void destroyTree();
private:
    void startNewTree(KeyType aKey, ValueType aValue);
    void insertIntoLeaf(KeyType aKey, ValueType aValue);
    void insertIntoParent(Node* aOldNode, KeyType aKey, Node* aNewNode);
    template <typename T> T* split(T* aNode);
    void removeFromLeaf(KeyType aKey);
    template <typename N> void coalesceOrRedistribute(N* aNode);
    template <typename N> void coalesce(N* aNeighborNode, N* aNode, InternalNode* aParent, int aIndex);
    template <typename N> void redistribute(N* aNeighborNode, N* aNode, InternalNode* aParent, int aIndex);
    void adjustRoot();
    LeafNode* findLeafNode(KeyType aKey, bool aPrinting = false);
    vector<EntryType> range(KeyType aStart, KeyType aEnd);
    const int fOrder;
    Node* fRoot;
    Printer fPrinter;
};
