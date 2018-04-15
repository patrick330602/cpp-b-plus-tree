#pragma once

using KeyType = int64_t;
using ValueType = int64_t;
using namespace std;

/// Class for record, the place for storing value from Leaf Node.
class Record
{
public:
    explicit Record(ValueType value);
    ValueType value() const;
    string toString() const;
private:
    Record() : Value(0) {}
    ValueType Value;
};
