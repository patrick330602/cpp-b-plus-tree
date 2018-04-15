#include "Node.h"

Node::Node(int order) : fOrder{order}, fParent{nullptr} {}

Node::Node(int order, Node *parent) : fOrder{order}, fParent{parent} {}

Node::~Node() {}

int Node::order() const
{
	return fOrder;
}

Node *Node::parent() const
{
	return fParent;
}

void Node::setParent(Node *parent)
{
	fParent = parent;
}

bool Node::isRoot() const
{
	return !fParent;
}
