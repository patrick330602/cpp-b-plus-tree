#include <sstream>
#include "InternalNode.h"
#include "LeafNode.h"

LeafNode::LeafNode(int aOrder) : fNext{nullptr}, Node(aOrder) {}

LeafNode::LeafNode(int aOrder, Node* aParent) : fNext{nullptr}, Node(aOrder, aParent) {}

LeafNode::~LeafNode()
{
    for (auto mapping : fMappings) {
        delete mapping.second;
    }
}

bool LeafNode::isLeaf() const
{
    return true;
}

LeafNode* LeafNode::next() const
{
    return fNext;
}

void LeafNode::setNext(LeafNode* aNext)
{
    fNext = aNext;
}

int LeafNode::size() const
{
    return static_cast<int>(fMappings.size());
}

int LeafNode::minSize() const
{
    return order()/2;
}

int LeafNode::maxSize() const
{
    return order() - 1;
}

string LeafNode::toString(bool aVerbose) const
{
    ostringstream keyToTextConverter;
    if (aVerbose) {
        keyToTextConverter << "[" << hex << this << dec << "]<" << fMappings.size() << "> ";
    }
    bool first = true;
    for (auto mapping : fMappings) {
        if (first) {
            first = false;
        } else {
            keyToTextConverter << " ";
        }
        keyToTextConverter << mapping.first;
    }
    if (aVerbose) {
        keyToTextConverter << "[" << hex << fNext << ">";
    }
    return keyToTextConverter.str();
}

int LeafNode::createAndInsertRecord(KeyType aKey, ValueType aValue)
{
    Record* existingRecord = lookup(aKey);
    if (!existingRecord) {
        Record* newRecord = new Record(aValue);
        insert(aKey, newRecord);
    }
    return static_cast<int>(fMappings.size());
}

void LeafNode::insert(KeyType aKey, Record* aRecord)
{
    auto insertionPoint = fMappings.begin();
    auto end = fMappings.end();
    while (insertionPoint != end && insertionPoint->first < aKey) {
        ++insertionPoint;
    }
    fMappings.insert(insertionPoint, MappingType(aKey, aRecord));
}

Record* LeafNode::lookup(KeyType aKey) const
{
    for (auto mapping : fMappings) {
        if (mapping.first == aKey) {
            return mapping.second;
        }
    }
    return nullptr;
}

void LeafNode::copyRangeStartingFrom(KeyType aKey, vector<EntryType>& aVector)
{
    bool found = false;
    for (auto mapping : fMappings) {
        if (mapping.first == aKey) {
            found = true;
        }
        if (found) {
            aVector.push_back(make_tuple(mapping.first, mapping.second->value(), this));
        }
    }
}

void LeafNode::copyRangeUntil(KeyType aKey, vector<EntryType>& aVector)
{
    bool found = false;
    for (auto mapping : fMappings) {
        if (!found) {
            aVector.push_back(make_tuple(mapping.first, mapping.second->value(), this));
        }
        if (mapping.first == aKey) {
            found = true;
        }
    }
}

void LeafNode::copyRange(vector<EntryType>& aVector)
{
    for (auto mapping : fMappings) {
        aVector.push_back(make_tuple(mapping.first, mapping.second->value(), this));
    }
}


int LeafNode::removeAndDeleteRecord(KeyType aKey)
{
    auto removalPoint = fMappings.begin();
    auto end = fMappings.end();
    while (removalPoint != end && removalPoint->first != aKey) {
        ++removalPoint;
    }
    if (removalPoint == end) {
		cout << "RecordNotFound: " << aKey << endl;
        throw;
    }
    auto record = *removalPoint;
    fMappings.erase(removalPoint);
    delete record.second;
    return static_cast<int>(fMappings.size());
}

KeyType LeafNode::firstKey() const
{
    return fMappings[0].first;
}

void LeafNode::moveHalfTo(LeafNode *aRecipient)
{
    aRecipient->copyHalfFrom(fMappings);
    size_t size = fMappings.size();
    for (size_t i = minSize()+1; i < size; ++i) {
        fMappings.pop_back();
    }
}

void LeafNode::copyHalfFrom(vector<pair<KeyType, Record*> > &aMappings)
{
    for (size_t i = minSize()+1; i < aMappings.size(); ++i) {
        fMappings.push_back(aMappings[i]);
    }
}

void LeafNode::moveAllTo(LeafNode *aRecipient, int)
{
    aRecipient->copyAllFrom(fMappings);
    fMappings.clear();
    aRecipient->setNext(next());
}

void LeafNode::copyAllFrom(vector<pair<KeyType, Record*> > &aMappings)
{
    for (auto mapping : aMappings) {
        fMappings.push_back(mapping);
    }
}

void LeafNode::moveFirstToEndOf(LeafNode* aRecipient)
{
    aRecipient->copyLastFrom(fMappings.front());
    fMappings.erase(fMappings.begin());
    static_cast<InternalNode*>(parent())->setKeyAt(1, fMappings.front().first);
}

void LeafNode::copyLastFrom(MappingType aPair)
{
    fMappings.push_back(aPair);
}

void LeafNode::moveLastToFrontOf(LeafNode *aRecipient, int aParentIndex)
{
    aRecipient->copyFirstFrom(fMappings.back(), aParentIndex);
    fMappings.pop_back();
}

void LeafNode::copyFirstFrom(MappingType aPair, int aParentIndex)
{
    fMappings.insert(fMappings.begin(), aPair);
    static_cast<InternalNode*>(parent())->setKeyAt(aParentIndex, fMappings.front().first);
}