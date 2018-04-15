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
class Tree
{
  public:
	/// B+ Tree constructor.  Accepts an optional order for the B+ Tree.
	explicit Tree(int iOrder = 4);

	/// The type used in the API for inserting a new key-value pair
	/// into the tree.  The third item is the type of the Node into
	/// which the key will be inserted.
	using EntryType = tuple<KeyType, ValueType, LeafNode *>;

	/// Check if the B+ tree has no keys or values, true if tree is empty, false otherwise.
	bool isEmpty() const;

	/// Insert a key-value pair into the B+ tree.
	void insert(KeyType iKey, ValueType iValue);

	/// Remove a key-value pair from the B+ tree.
	void remove(KeyType iKey);

	/// Print the B+ tree to stdout using a simple command-line
	void print();

	/// Remove all elements from the B+ tree. You can then build
	/// it up again by inserting new elements into it.
	void destroyTree();

  private:
	/*-- Insertion --*/
	void startNewTree(KeyType iKey, ValueType iValue);
	void insertIntoLeaf(KeyType iKey, ValueType iValue);
	void insertIntoParent(Node *oldNode, KeyType iKey, Node *newNode);
	template <typename T>
	T *split(T *node);
	/*-- Deletion --*/
	void removeFromLeaf(KeyType iKey);
	template <typename N>
	void coalesceOrRedistribute(N *node);
	template <typename N>
	void coalesce(N *neighborNode, N *node, InternalNode *parent, int index);
	template <typename N>
	void redistribute(N *neighborNode, N *node, InternalNode *parent, int index);
	void adjustRoot();
	/*-- Other functions --*/
	LeafNode *findLeafNode(KeyType iKey, bool isPrinting = false);
	const int tOrder;
	Node *tRoot;
	Printer printer;
};
