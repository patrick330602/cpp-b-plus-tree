#pragma once

#include "Definitions.h"
using namespace std;

class Record
{
public:
    explicit Record(ValueType aValue);
    ValueType value() const;
    std::string toString() const;
private:
    Record() : fValue(0) {}
    ValueType fValue;
};
