#include <sstream>
#include "InternalNode.h"

InternalNode::InternalNode(int order) : Node(order) {}

InternalNode::InternalNode(int order, Node* parent) : Node(order, parent) {}

InternalNode::~InternalNode()
{
    for (auto mapping : Mappings) {
        delete mapping.second;
    }
}

bool InternalNode::isLeaf() const
{
    return false;
}

int InternalNode::size() const
{
    return static_cast<int>(Mappings.size());
}

int InternalNode::minSize() const
{
    return order()/2;
}

int InternalNode::maxSize() const
{
    // Includes the first entry, which
    // has key DUMMY_KEY and a value that
    // points to the left of the first positive key k1
    // (i.e., a node whose keys are all < k1).
    return order();
}

KeyType InternalNode::keyAt(int index) const
{
    return Mappings[index].first;
}

void InternalNode::setKeyAt(int index, KeyType key)
{
    Mappings[index].first = key;
}

Node* InternalNode::firstChild() const
{
    return Mappings.front().second;
}

void InternalNode::populateNewRoot(Node *oldNode, KeyType newKey, Node *newNode)
{
    Mappings.push_back(make_pair(DUMMY_KEY, oldNode));
    Mappings.push_back(make_pair(newKey, newNode));
}

int InternalNode::insertNodeAfter(Node *oldNode, KeyType newKey, Node *newNode)
{
    auto iter = Mappings.begin();
    for (; iter != Mappings.end() && iter->second != oldNode; ++iter);
    Mappings.insert(iter + 1, make_pair(newKey, newNode));
    return size();
}

void InternalNode::remove(int index)
{
    Mappings.erase(Mappings.begin() + index);
}

Node* InternalNode::removeAndReturnOnlyChild()
{
    Node* firstChild = Mappings.front().second;
    Mappings.pop_back();
    return firstChild;
}

KeyType InternalNode::replaceAndReturnFirstKey()
{
    KeyType newKey = Mappings[0].first;
    Mappings[0].first = DUMMY_KEY;
    return newKey;
}

void InternalNode::moveHalfTo(InternalNode *recipient)
{
    recipient->copyHalfFrom(Mappings);
    size_t size = Mappings.size();
    for (size_t i = minSize()+1; i < size; ++i) {
        Mappings.pop_back();
    }
}

void InternalNode::copyHalfFrom(vector<MappingType> &mappings)
{
    for (size_t i = minSize()+1; i < mappings.size(); ++i) {
        mappings[i].second->setParent(this);
        Mappings.push_back(mappings[i]);
    }
}

void InternalNode::moveAllTo(InternalNode *recipient, int indexInParent)
{
    Mappings[0].first = static_cast<InternalNode*>(parent())->keyAt(indexInParent);
    recipient->copyAllFrom(Mappings);
    Mappings.clear();
}

void InternalNode::copyAllFrom(vector<MappingType> &mappings)
{
    for (auto mapping : mappings) {
        mapping.second->setParent(this);
        Mappings.push_back(mapping);
    }
}

void InternalNode::moveFirstToEndOf(InternalNode *recipient)
{
    recipient->copyLastFrom(Mappings.front());
    Mappings.erase(Mappings.begin());
    static_cast<InternalNode*>(parent())->setKeyAt(1, Mappings.front().first);
}

void InternalNode::copyLastFrom(MappingType pair)
{
    Mappings.push_back(pair);
    Mappings.back().second->setParent(this);
}

void InternalNode::moveLastToFrontOf(InternalNode *recipient, int parentIndex)
{
    recipient->copyFirstFrom(Mappings.back(), parentIndex);
    Mappings.pop_back();
}

void InternalNode::copyFirstFrom(MappingType pair, int parentIndex)
{
    Mappings.front().first = static_cast<InternalNode*>(parent())->keyAt(parentIndex);
    Mappings.insert(Mappings.begin(), pair);
    Mappings.front().first = DUMMY_KEY;
    Mappings.front().second->setParent(this);
    static_cast<InternalNode*>(parent())->setKeyAt(parentIndex, Mappings.front().first);
}

Node* InternalNode::lookup(KeyType key) const
{
    auto locator = Mappings.begin();
    auto end = Mappings.end();
    while (locator != end && key >= locator->first) {
        ++locator;
    }
    // locator->first is now the least key k such that key < k.
    // One before is the greatest key k such that key >= k.
    --locator;
    return locator->second;
}

int InternalNode::nodeIndex(Node *node) const
{
    for (size_t i = 0; i < size(); ++i) {
        if (Mappings[i].second == node) {
            return static_cast<int>(i);
        }
    }
    cout << "NodeNotFound: {" << node->toString() << ": " << toString() << "}\n";
    throw;
}

Node* InternalNode::neighbor(int index) const
{
    return Mappings[index].second;
}

string InternalNode::toString() const
{
    if (Mappings.empty()) {
        return "";
    }
    ostringstream keyToTextConverter;
    auto entry = Mappings.begin() + 1;
    auto end = Mappings.end();
    bool first = true;
    while (entry != end) {
        if (first) {
            first = false;
        } else {
            keyToTextConverter << " ";
        }
        keyToTextConverter << dec << entry->first;
        ++entry;
    }
    return keyToTextConverter.str();
}

void InternalNode::queueUpChildren(queue<Node *>* queue)
{
    for (auto mapping : Mappings) {
        queue->push(mapping.second);
    }
}