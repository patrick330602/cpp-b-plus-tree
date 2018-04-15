#include <sstream>
#include "InternalNode.h"
#include "LeafNode.h"

LeafNode::LeafNode(int order) : Next{nullptr}, Node(order) {}

LeafNode::LeafNode(int order, Node *parent) : Next{nullptr}, Node(order, parent) {}

LeafNode::~LeafNode()
{
	for (auto mapping : Mappings)
	{
		delete mapping.second;
	}
}

bool LeafNode::isLeaf() const
{
	return true;
}

LeafNode *LeafNode::next() const
{
	return Next;
}

void LeafNode::setNext(LeafNode *next)
{
	Next = next;
}

int LeafNode::size() const
{
	return static_cast<int>(Mappings.size());
}

int LeafNode::minSize() const
{
	return order() / 2;
}

int LeafNode::maxSize() const
{
	return order() - 1;
}

string LeafNode::toString() const
{
	ostringstream keyToTextConverter;
	bool first = true;
	for (auto mapping : Mappings)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			keyToTextConverter << " ";
		}
		keyToTextConverter << mapping.first;
	}
	return keyToTextConverter.str();
}

int LeafNode::createAndInsertRecord(KeyType key, ValueType aValue)
{
	Record *existingRecord = lookup(key);
	if (!existingRecord)
	{
		Record *newRecord = new Record(aValue);
		insert(key, newRecord);
	}
	return static_cast<int>(Mappings.size());
}

void LeafNode::insert(KeyType key, Record *record)
{
	auto insertionPoint = Mappings.begin();
	auto end = Mappings.end();
	while (insertionPoint != end && insertionPoint->first < key)
	{
		++insertionPoint;
	}
	Mappings.insert(insertionPoint, MappingType(key, record));
}

Record *LeafNode::lookup(KeyType key) const
{
	for (auto mapping : Mappings)
	{
		if (mapping.first == key)
		{
			return mapping.second;
		}
	}
	return nullptr;
}

int LeafNode::removeAndDeleteRecord(KeyType key)
{
	auto removalPoint = Mappings.begin();
	auto end = Mappings.end();
	while (removalPoint != end && removalPoint->first != key)
	{
		++removalPoint;
	}
	if (removalPoint == end)
	{
		cout << "RecordNotFound: " << key << endl;
		throw;
	}
	auto record = *removalPoint;
	Mappings.erase(removalPoint);
	delete record.second;
	return static_cast<int>(Mappings.size());
}

KeyType LeafNode::firstKey() const
{
	return Mappings[0].first;
}

KeyType LeafNode::lastKey() const
{
	return Mappings[Mappings.size() - 1].first;
}

void LeafNode::moveHalfTo(LeafNode *recipient)
{
	recipient->copyHalfFrom(Mappings);
	size_t size = Mappings.size();
	for (size_t i = minSize() + 1; i < size; ++i)
	{
		Mappings.pop_back();
	}
}

void LeafNode::copyHalfFrom(vector<pair<KeyType, Record *>> &mappings)
{
	for (size_t i = minSize() + 1; i < mappings.size(); ++i)
	{
		Mappings.push_back(mappings[i]);
	}
}

void LeafNode::moveAllTo(LeafNode *recipient, int)
{
	recipient->copyAllFrom(Mappings);
	Mappings.clear();
	recipient->setNext(next());
}

void LeafNode::copyAllFrom(vector<pair<KeyType, Record *>> &mappings)
{
	for (auto mapping : mappings)
	{
		Mappings.push_back(mapping);
	}
}

void LeafNode::moveFirstToEndOf(LeafNode *recipient)
{
	recipient->copyLastFrom(Mappings.front());
	Mappings.erase(Mappings.begin());
	static_cast<InternalNode *>(parent())->setKeyAt(1, Mappings.front().first);
}

void LeafNode::copyLastFrom(MappingType Pair)
{
	Mappings.push_back(Pair);
}

void LeafNode::moveLastToFrontOf(LeafNode *recipient, int parentIndex)
{
	recipient->copyFirstFrom(Mappings.back(), parentIndex);
	Mappings.pop_back();
}

void LeafNode::copyFirstFrom(MappingType Pair, int parentIndex)
{
	Mappings.insert(Mappings.begin(), Pair);
	static_cast<InternalNode *>(parent())->setKeyAt(parentIndex, Mappings.front().first);
}