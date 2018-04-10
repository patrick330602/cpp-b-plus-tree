#include "InternalNode.h"
#include "LeafNode.h"
#include "Node.h"
#include "Printer.h"

Printer::Printer() {}


void Printer::printTree(Node *aRoot) const
{
    if (!aRoot) {
        printEmptyTree();
    } else {
        printNormalTree(aRoot);
    }
}

void Printer::printEmptyTree() const
{
    cout << "Empty tree.\n";
}

void Printer::printNormalTree(Node *aRoot) const
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
        cout << " " << currentNode->toString();
        cout << " |";
        if (!currentNode->isLeaf()) {
            auto internalNode = static_cast<InternalNode*>(currentNode);
            internalNode->queueUpChildren(aNextRank);
        }
        aCurrentRank->pop();
    }
    cout << endl;
}