#include <fstream>
#include <string>
#include "BPlusTree.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include "Node.h"

BPlusTree::BPlusTree(int aOrder) : fOrder{aOrder}, fRoot{nullptr} {}

bool BPlusTree::isEmpty() const
{
    return !fRoot;
}

/*-- Insertion --*/

void BPlusTree::insert(KeyType aKey, ValueType aValue)
{
    if (isEmpty()) {
        startNewTree(aKey, aValue);
    } else {
        insertIntoLeaf(aKey, aValue);
    }
}

void BPlusTree::startNewTree(KeyType aKey, ValueType aValue) {
    LeafNode* newLeafNode = new LeafNode(fOrder);
    newLeafNode->createAndInsertRecord(aKey, aValue);
    fRoot = newLeafNode;
}

void BPlusTree::insertIntoLeaf(KeyType aKey, ValueType aValue)
{
    LeafNode* leafNode = findLeafNode(aKey);
    if (!leafNode) {
        cout << "LeafNotFound: " << aKey << endl;
		throw;
    }
    int newSize = leafNode->createAndInsertRecord(aKey, aValue);
    if (newSize > leafNode->maxSize()) {
        LeafNode* newLeaf = split(leafNode);
		KeyType newKey = leafNode->lastKey();
        newLeaf->setNext(leafNode->next());
        leafNode->setNext(newLeaf);
        //KeyType newKey = newLeaf->firstKey();
        insertIntoParent(leafNode, newKey, newLeaf);
    }
}

void BPlusTree::insertIntoParent(Node *aOldNode, KeyType aKey, Node *aNewNode)
{
    InternalNode* parent = static_cast<InternalNode*>(aOldNode->parent());
    if (parent == nullptr) {
        fRoot = new InternalNode(fOrder);
        parent = static_cast<InternalNode*>(fRoot);
        aOldNode->setParent(parent);
        aNewNode->setParent(parent);
        parent->populateNewRoot(aOldNode, aKey, aNewNode);
    } else {
        int newSize = parent->insertNodeAfter(aOldNode, aKey, aNewNode);
        if (newSize > parent->maxSize()) {
            InternalNode* newNode = split(parent);
            KeyType newKey = newNode->replaceAndReturnFirstKey();
            insertIntoParent(parent, newKey, newNode);
        }
    }
}

template <typename T>
T* BPlusTree::split(T* aNode)
{
    T* newNode = new T(fOrder, aNode->parent());
    aNode->moveHalfTo(newNode);
    return newNode;
}

/*-- Deletion --*/

void BPlusTree::remove(KeyType aKey)
{
    if (isEmpty()) {
        return;
    } else {
        removeFromLeaf(aKey);
    }
}

void BPlusTree::removeFromLeaf(KeyType aKey)
{
    LeafNode* leafNode = findLeafNode(aKey);
    if (!leafNode) {
        return;
    }
    if (!leafNode->lookup(aKey)) {
        return;
    }
    int newSize = leafNode->removeAndDeleteRecord(aKey);
    if (newSize < leafNode->minSize()) {
        coalesceOrRedistribute(leafNode);
    }
}

template <typename N>
void BPlusTree::coalesceOrRedistribute(N* aNode)
{
    if (aNode->isRoot()) {
        adjustRoot();
        return;
    }
    auto parent = static_cast<InternalNode*>(aNode->parent());
    int indexOfNodeInParent = parent->nodeIndex(aNode);
    int neighborIndex = (indexOfNodeInParent == 0) ? 1 : indexOfNodeInParent - 1;
    N* neighborNode = static_cast<N*>(parent->neighbor(neighborIndex));
    if (aNode->size() + neighborNode->size() <= neighborNode->maxSize()) {
        coalesce(neighborNode, aNode, parent, indexOfNodeInParent);
    } else {
        redistribute(neighborNode, aNode, parent, indexOfNodeInParent);
    }
}

template <typename N>
void BPlusTree::coalesce(N* aNeighborNode, N* aNode, InternalNode* aParent, int aIndex)
{
    if (aIndex == 0) {
        swap(aNode, aNeighborNode);
        aIndex = 1;
    }
    aNode->moveAllTo(aNeighborNode, aIndex);
    aParent->remove(aIndex);
    if (aParent->size() < aParent->minSize()) {
        coalesceOrRedistribute(aParent);
    }
    delete aNode;
}

template <typename N>
void BPlusTree::redistribute(N* aNeighborNode, N* aNode, InternalNode* aParent, int aIndex)
{
    if (aIndex == 0) {
        aNeighborNode->moveFirstToEndOf(aNode);
    } else {
        aNeighborNode->moveLastToFrontOf(aNode, aIndex);
    }
}

void BPlusTree::adjustRoot()
{
    if (!fRoot->isLeaf() && fRoot->size() == 1) {
        auto discardedNode = static_cast<InternalNode*>(fRoot);
        fRoot = static_cast<InternalNode*>(fRoot)->removeAndReturnOnlyChild();
        fRoot->setParent(nullptr);
        delete discardedNode;
    } else if (!fRoot->size()){
        delete fRoot;
        fRoot = nullptr;
    }
}

/*-- Other functions --*/

LeafNode* BPlusTree::findLeafNode(KeyType aKey, bool aPrinting)
{
    if (isEmpty()) {
        if (aPrinting) {
            cout << "Not found: empty tree.\n";
        }
        return nullptr;
    }
    auto node = fRoot;
    if (aPrinting) {
        cout << "Root: ";
        if (fRoot->isLeaf()) {
            cout << "\t" << static_cast<LeafNode*>(fRoot)->toString();
        } else {
            cout << "\t" << static_cast<InternalNode*>(fRoot)->toString();
        }
        cout << endl;
    }
    while (!node->isLeaf()) {
        auto internalNode = static_cast<InternalNode*>(node);
        if (aPrinting && node != fRoot) {
            cout << "\tNode: " << internalNode->toString() << endl;
        }
        node = internalNode->lookup(aKey);
    }
    return static_cast<LeafNode*>(node);
}

void BPlusTree::print()
{
    fPrinter.printTree(fRoot);
}

void BPlusTree::destroyTree()
{
    if (fRoot->isLeaf()) {
        delete static_cast<LeafNode*>(fRoot);
    } else {
        delete static_cast<InternalNode*>(fRoot);
    }
    fRoot = nullptr;
}



