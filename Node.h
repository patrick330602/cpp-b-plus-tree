#pragma once

#include <string>

using KeyType = int64_t;
using ValueType = int64_t;
using namespace std;

// Key used where only the entry's pointer has meaning.
const KeyType DUMMY_KEY{-1};

// Abstract Node class.
class Node
{
  public:
	///Construct Node with Order 'order'
	explicit Node(int order);

	///Construct Node with Order 'order' and its parent 'parent'
	explicit Node(int order, Node *parent);

	///Destructor
	virtual ~Node();

	///return Node Order
	int order() const;

	///return Node parent
	Node *parent() const;

	///Set a parent for the Node
	void setParent(Node *parent);

	/// return whether the node is root
	bool isRoot() const;

	/// return whether the node is leaf, virtual
	virtual bool isLeaf() const = 0;

	/// return size of the node set, virtual
	virtual int size() const = 0;

	/// return minimum size of the node set, virtual
	virtual int minSize() const = 0;

	///return maximum size of the node set, virtual
	virtual int maxSize() const = 0;

	///return the value in string format, virtual
	virtual string toString() const = 0;

  private:
	const int fOrder;
	Node *fParent;
};