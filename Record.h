#pragma once

using KeyType = int64_t;
using ValueType = int64_t;
using namespace std;

class Record
{
public:
    explicit Record(ValueType aValue);
    ValueType value() const;
    string toString() const;
private:
    Record() : fValue(0) {}
    ValueType fValue;
};
