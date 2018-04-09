#pragma once

#include <string>
#include "Definitions.h"
using namespace std;

// Key used where only the entry's pointer has meaning.
const KeyType DUMMY_KEY{-1};

// Abstract class.
class Node
{
public:
    explicit Node(int aOrder);
    explicit Node(int aOrder, Node* aParent);
    virtual ~Node();
    int order() const;
    Node* parent() const;
    void setParent(Node* aParent);
    bool isRoot() const;
    virtual bool isLeaf() const = 0;
    virtual int size() const = 0;
    virtual int minSize() const = 0;
    virtual int maxSize() const = 0;
    virtual string toString(bool aVerbose = false) const = 0;
private:
    const int fOrder;
    Node* fParent;
};