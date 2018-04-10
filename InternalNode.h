#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "Node.h"
using namespace std;

class InternalNode : public Node
{
public:
    explicit InternalNode(int Order);
    explicit InternalNode(int Order, Node* Parent);
    ~InternalNode() override;
    using MappingType = pair<KeyType, Node*>;
    bool isLeaf() const override;
    int size() const override;
    int minSize() const override;
    int maxSize() const override;
    KeyType keyAt(int aIndex) const;
    void setKeyAt(int aIndex, KeyType aKey);
    Node* firstChild() const;
    void populateNewRoot(Node* aOldNode, KeyType aNewKey, Node* aNewNode);
    int insertNodeAfter(Node* aOldNode, KeyType aNewKey, Node* aNewNode);
    void remove(int aIndex);
    Node* removeAndReturnOnlyChild();
    KeyType replaceAndReturnFirstKey();
    void moveHalfTo(InternalNode* aRecipient);
    void moveAllTo(InternalNode* aRecipient, int aIndexInParent);
    void moveFirstToEndOf(InternalNode* aRecipient);
    void moveLastToFrontOf(InternalNode* aRecipient, int aParentIndex);
    Node* lookup(KeyType aKey) const;
    int nodeIndex(Node* aNode) const;
    Node* neighbor(int aIndex) const;
    string toString() const override;
    void queueUpChildren(queue<Node*>* aQueue);
private:
    void copyHalfFrom(vector<MappingType>& aMappings);
    void copyAllFrom(vector<MappingType>& aMappings);
    void copyLastFrom(MappingType aPair);
    void copyFirstFrom(MappingType aPair, int aParentIndex);
    vector<MappingType> fMappings;
};
