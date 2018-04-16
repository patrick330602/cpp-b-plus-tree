#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include "Node.h"
using namespace std;

class InternalNode : public Node
{
public:
	/* Types */
	using MappingType = pair<KeyType, Node*>;

	/// construct internal node with order 'order'
    explicit InternalNode(int order);

	/// construct internal node with order 'order' and its parent 'parent'
    explicit InternalNode(int order, Node* parent);

	/// destructor
    ~InternalNode() override;
    
	/// inherit from Node class; which will always return false.
    bool isLeaf() const override;

	/// inherit from Node class.
    int size() const override;

	/// inherit from Node class.
    int minSize() const override;

	/// inherit from Node class.
    int maxSize() const override;

	/// return the key value at the node with index 'index'.
    KeyType keyAt(int index) const;

	/// set the key value at the node with index 'index'.
    void setKeyAt(int index, KeyType key);

	/// return the first node.
    Node* firstChild() const;

	/// populate the root node with pointer and DUMMY_KEY.
    void populateNewRoot(Node* oldNode, KeyType newKey, Node* newNode);

	/// insert newNode after oldNode.
    int insertNodeAfter(Node* oldNode, KeyType newKey, Node* newNode);

	/// remove node with index.
    void remove(int index);

	/// remove the node and return its only child.
    Node* removeAndReturnOnlyChild();

	/// replace and return the firstkey of the node.
    KeyType replaceAndReturnFirstKey();

	/// move half of the node -1 to an new node.
    void moveHalfTo(InternalNode* recipient);

	/// move all of the node to an new node.
    void moveAllTo(InternalNode* recipient, int indexInParent);

	/// move the first node to the end of a node 'recipient'
    void moveFirstToEndOf(InternalNode* recipient);

	/// move the last node to the end of a node 'recipient'
    void moveLastToFrontOf(InternalNode* recipient, int parentIndex);

	/// find the node with key and return the Node.
    Node* lookup(KeyType key) const;

	/// return index if the Node is found; throw error otherwise.
    int nodeIndex(Node* node) const;

	///return value with a certain index in neighbor.
    Node* neighbor(int index) const;

	/// return a string from the int value.
    string toString() const override;

	/// push the value down a level.
    void queueUpChildren(queue<Node*>* queue);
private:
    void copyHalfFrom(vector<MappingType>& mappings);
    void copyAllFrom(vector<MappingType>& mappings);
    void copyLastFrom(MappingType pair);
    void copyFirstFrom(MappingType pair, int parentIndex);
    vector<MappingType> Mappings;
};
