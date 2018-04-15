#pragma once

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include "Node.h"
#include "Record.h"
using namespace std;

class LeafNode : public Node
{
  public:
	/* Types */
	using MappingType = pair<KeyType, Record *>;
	using EntryType = tuple<KeyType, ValueType, LeafNode *>;

	/// construct leaf node with order 'order'
	explicit LeafNode(int order);

	/// construct leaf node with order 'order' and its parent 'parent'
	explicit LeafNode(int order, Node *parent);

	/// destructor
	~LeafNode() override;

	/// inherit from Node class; which will always return true.
	bool isLeaf() const override;

	/// return the next leaf node.
	LeafNode *next() const;

	/// set the next leaf node for the leaf node.
	void setNext(LeafNode *next);

	/// inherit from Node class.
	int size() const override;

	/// inherit from Node class.
	int minSize() const override;

	/// inherit from Node class.
	int maxSize() const override;

	/// insert record and return the current size of the node set of the mappings.
	int createAndInsertRecord(KeyType key, ValueType aValue);

	/// insert the kay-value pair into the node.
	void insert(KeyType key, Record *record);

	/// find whether the key existed in the program. it will return its value when found, return nullptr when not found.
	Record *lookup(KeyType key) const;

	/// delete record and return the current size of the node set of the mappings.
	int removeAndDeleteRecord(KeyType key);

	/// return the first key of the node.
	KeyType firstKey() const;

	/// return the last key of the node.
	KeyType lastKey() const;

	/// move half of the node -1 to an new node.
	void moveHalfTo(LeafNode *recipient);

	/// move all of the node to an new node.
	void moveAllTo(LeafNode *recipient, int /* Unused */);

	/// move the first node to the end of a node 'recipient'
	void moveFirstToEndOf(LeafNode *recipient);

	/// move the last node to the end of a node 'recipient'
	void moveLastToFrontOf(LeafNode *recipient, int parentIndex);

	/// inherit from Node class.
	string toString() const override;

  private:
	void copyHalfFrom(vector<MappingType> &mappings);
	void copyAllFrom(vector<MappingType> &mappings);
	void copyLastFrom(MappingType Pair);
	void copyFirstFrom(MappingType Pair, int parentIndex);
	vector<MappingType> Mappings;
	LeafNode *Next;
};