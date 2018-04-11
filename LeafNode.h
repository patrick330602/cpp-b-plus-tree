#pragma once

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include "Node.h"
#include "Record.h"
using namespace std;

class LeafNode : public Node
{
public:
    explicit LeafNode(int aOrder);
    explicit LeafNode(int aOrder, Node* aParent);
    ~LeafNode() override;
    using MappingType = pair<KeyType, Record*>;
    using EntryType = tuple<KeyType, ValueType, LeafNode*>;
    bool isLeaf() const override;
    LeafNode* next() const;
    void setNext(LeafNode* aNext);
    int size() const override;
    int minSize() const override;
    int maxSize() const override;
    int createAndInsertRecord(KeyType aKey, ValueType aValue);
    void insert(KeyType aKey, Record* aRecord);
    Record* lookup(KeyType aKey) const;
    int removeAndDeleteRecord(KeyType aKey);
    KeyType firstKey() const;
    KeyType lastKey() const;
    void moveHalfTo(LeafNode* aRecipient);
    void moveAllTo(LeafNode* aRecipient, int /* Unused */);
    void moveFirstToEndOf(LeafNode* aRecipient);
    void moveLastToFrontOf(LeafNode* aRecipient, int aParentIndex);
    string toString() const override;
private:
    void copyHalfFrom(vector<MappingType>& aMappings);
    void copyAllFrom(vector<MappingType>& aMappings);
    void copyLastFrom(MappingType aPair);
    void copyFirstFrom(MappingType aPair, int aParentIndex);
    vector<MappingType> fMappings;
    LeafNode* fNext;
};