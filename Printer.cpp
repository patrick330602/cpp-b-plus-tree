#include <iostream>
#include "InternalNode.h"
#include "LeafNode.h"
#include "Node.h"
#include "Printer.h"
using namespace std;

Printer::Printer() : fVerbose(false) {}

bool Printer::verbose() const
{
    return fVerbose;
}

void Printer::setVerbose(bool aVerbose)
{
    fVerbose = aVerbose;
}

void Printer::printTree(Node *aRoot) const
{
    if (!aRoot) {
        printEmptyTree();
    } else {
        printNonEmptyTree(aRoot);
    }
}

void Printer::printEmptyTree() const
{
    cout << "Empty tree." << endl;
}

void Printer::printNonEmptyTree(Node *aRoot) const
{
    queue<Node*> queue0;
    queue<Node*> queue1;
    auto currentRank = &queue0;
    auto nextRank = &queue1;
    currentRank->push(aRoot);
    while (!currentRank->empty()) {
        printCurrentRank(currentRank, nextRank);
        auto tmp = currentRank;
        currentRank = nextRank;
        nextRank = tmp;
    }
}

void Printer::printCurrentRank(queue<Node*>* aCurrentRank, queue<Node*>* aNextRank) const
{
    cout << "|";
    while(!aCurrentRank->empty()) {
        Node* currentNode = aCurrentRank->front();
        cout << " " << currentNode->toString(verbose());
        cout << " |";
        if (!currentNode->isLeaf()) {
            auto internalNode = static_cast<InternalNode*>(currentNode);
            internalNode->queueUpChildren(aNextRank);
        }
        aCurrentRank->pop();
    }
    cout << endl;
}

void Printer::printLeaves(Node *aRoot)
{
    if (!aRoot) {
        printEmptyTree();
        return;
    }
    auto node = aRoot;
    while (!node->isLeaf()) {
        node = static_cast<InternalNode*>(node)->firstChild();
    }
    auto leafNode = static_cast<LeafNode*>(node);
    while (leafNode) {
        cout << "| ";
        cout << leafNode->toString(fVerbose);
        leafNode = leafNode->next();
    }
    cout << " |" << endl;
}