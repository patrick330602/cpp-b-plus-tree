#include <fstream>
#include <string>
#include "Tree.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include "Node.h"

Tree::Tree(int iOrder) : tOrder{iOrder}, tRoot{nullptr} {}

bool Tree::isEmpty() const
{
	return !tRoot;
}

/*-- Insertion --*/

void Tree::insert(KeyType iKey, ValueType iValue)
{
	if (isEmpty())
	{
		startNewTree(iKey, iValue);
	}
	else
	{
		insertIntoLeaf(iKey, iValue);
	}
}

void Tree::startNewTree(KeyType iKey, ValueType iValue)
{
	LeafNode *newLeafNode = new LeafNode(tOrder);
	newLeafNode->createAndInsertRecord(iKey, iValue);
	tRoot = newLeafNode;
}

void Tree::insertIntoLeaf(KeyType iKey, ValueType iValue)
{
	LeafNode *leafNode = findLeafNode(iKey);
	if (!leafNode)
	{
		cout << "LeafNotFound: " << iKey << endl;
		throw;
	}
	int newSize = leafNode->createAndInsertRecord(iKey, iValue);
	if (newSize > leafNode->maxSize())
	{
		LeafNode *newLeaf = split(leafNode);
		KeyType newKey = leafNode->lastKey();
		newLeaf->setNext(leafNode->next());
		leafNode->setNext(newLeaf);
		insertIntoParent(leafNode, newKey, newLeaf);
	}
}

void Tree::insertIntoParent(Node *oldNode, KeyType iKey, Node *newNode)
{
	InternalNode *parent = static_cast<InternalNode *>(oldNode->parent());
	if (parent == nullptr)
	{
		tRoot = new InternalNode(tOrder);
		parent = static_cast<InternalNode *>(tRoot);
		oldNode->setParent(parent);
		newNode->setParent(parent);
		parent->populateNewRoot(oldNode, iKey, newNode);
	}
	else
	{
		int newSize = parent->insertNodeAfter(oldNode, iKey, newNode);
		if (newSize > parent->maxSize())
		{
			InternalNode *newerPNode = split(parent);
			KeyType newKey = newerPNode->replaceAndReturnFirstKey();
			insertIntoParent(parent, newKey, newerPNode);
		}
	}
}

template <typename T>
T *Tree::split(T *node)
{
	T *newNode = new T(tOrder, node->parent());
	node->moveHalfTo(newNode);
	return newNode;
}

/*-- Deletion --*/

void Tree::remove(KeyType iKey)
{
	if (!isEmpty())removeFromLeaf(iKey);
	return;
}

void Tree::removeFromLeaf(KeyType iKey)
{
	LeafNode *leafNode = findLeafNode(iKey);
	if (!leafNode)return;
	if (!leafNode->lookup(iKey))return;
	int newSize = leafNode->removeAndDeleteRecord(iKey);
	if (newSize < leafNode->minSize())coalesceOrRedistribute(leafNode);
}

template <typename N>
void Tree::coalesceOrRedistribute(N *node)
{
	if (node->isRoot())
	{
		adjustRoot();
		return;
	}
	auto parent = static_cast<InternalNode *>(node->parent());
	int indexOfNodeInParent = parent->nodeIndex(node);
	int neighborIndex = (indexOfNodeInParent == 0) ? 1 : indexOfNodeInParent - 1;
	N *neighborNode = static_cast<N *>(parent->neighbor(neighborIndex));
	if (node->size() + neighborNode->size() <= neighborNode->maxSize())
	{
		coalesce(neighborNode, node, parent, indexOfNodeInParent);
	}
	else
	{
		redistribute(neighborNode, node, parent, indexOfNodeInParent);
	}
}

template <typename N>
void Tree::coalesce(N *neighborNode, N *node, InternalNode *parent, int index)
{
	if (index == 0)
	{
		swap(node, neighborNode);
		index = 1;
	}
	node->moveAllTo(neighborNode, index);
	parent->remove(index);
	if (parent->size() < parent->minSize())
	{
		coalesceOrRedistribute(parent);
	}
	delete node;
}

template <typename N>
void Tree::redistribute(N *neighborNode, N *node, InternalNode *parent, int index)
{
	if (index == 0)
	{
		neighborNode->moveFirstToEndOf(node);
	}
	else
	{
		neighborNode->moveLastToFrontOf(node, index);
	}
}

void Tree::adjustRoot()
{
	if (!tRoot->isLeaf() && tRoot->size() == 1)
	{
		auto discardedNode = static_cast<InternalNode *>(tRoot);
		tRoot = static_cast<InternalNode *>(tRoot)->removeAndReturnOnlyChild();
		tRoot->setParent(nullptr);
		delete discardedNode;
	}
	else if (!tRoot->size())
	{
		delete tRoot;
		tRoot = nullptr;
	}
}

/*-- Other functions --*/

LeafNode *Tree::findLeafNode(KeyType iKey, bool isPrinting)
{
	if (isEmpty())
	{
		if (isPrinting)
		{
			cout << "Not found: empty tree.\n";
		}
		return nullptr;
	}
	auto node = tRoot;
	if (isPrinting)
	{
		cout << "Root: ";
		if (tRoot->isLeaf())
		{
			cout << "\t" << static_cast<LeafNode *>(tRoot)->toString();
		}
		else
		{
			cout << "\t" << static_cast<InternalNode *>(tRoot)->toString();
		}
		cout << endl;
	}
	while (!node->isLeaf())
	{
		auto internalNode = static_cast<InternalNode *>(node);
		if (isPrinting && node != tRoot)
		{
			cout << "\tNode: " << internalNode->toString() << endl;
		}
		node = internalNode->lookup(iKey);
	}
	return static_cast<LeafNode *>(node);
}

void Tree::print()
{
	if (!tRoot)
	{
		cout << "Empty tree.\n";
	}
	else
	{
		queue<Node *> queue0;
		queue<Node *> queue1;
		auto currentRank = &queue0;
		auto nextRank = &queue1;
		currentRank->push(tRoot);
		while (!currentRank->empty())
		{
			printCurrentRank(currentRank, nextRank);
			auto tmp = currentRank;
			currentRank = nextRank;
			nextRank = tmp;
		}
	}
}
void Tree::printCurrentRank(queue<Node *> *currentRank, queue<Node *> *nextRank) const
{
	cout << "|";
	while (!currentRank->empty())
	{
		Node *currentNode = currentRank->front();
		cout << " " << currentNode->toString();
		cout << " |";
		if (!currentNode->isLeaf())
		{
			auto internalNode = static_cast<InternalNode *>(currentNode);
			internalNode->queueUpChildren(nextRank);
		}
		currentRank->pop();
	}
	cout << endl;
}

void Tree::destroyTree()
{
	if (tRoot->isLeaf())
	{
		delete static_cast<LeafNode *>(tRoot);
	}
	else
	{
		delete static_cast<InternalNode *>(tRoot);
	}
	tRoot = nullptr;
}
