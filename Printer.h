#pragma once

#include <iostream>
#include <queue>
using namespace std;

class Node;

class Printer
{
public:
    Printer();
    bool verbose() const;
    void setVerbose(bool aVerbose);
    void printTree(Node* aRoot) const;
    void printLeaves(Node* aRoot);
private:
    void printEmptyTree() const;
    void printNonEmptyTree(Node* aRoot) const;
    void printCurrentRank(queue<Node*>* aCurrentRank, queue<Node*>* aNextRank) const;
    bool fVerbose;
};