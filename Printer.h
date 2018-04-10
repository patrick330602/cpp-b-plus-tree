#pragma once

#include <iostream>
#include <queue>
using namespace std;

class Node;

class Printer
{
public:
    Printer();
    void printTree(Node* aRoot) const;
private:
    void printEmptyTree() const;
    void printNormalTree(Node* aRoot) const;
    void printCurrentRank(queue<Node*>* aCurrentRank, queue<Node*>* aNextRank) const;
};