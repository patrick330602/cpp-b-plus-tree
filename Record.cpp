#include <string>
#include <sstream>

#include "Record.h"

Record::Record(ValueType value)
: Value(value)
{}

ValueType Record::value() const
{
    return Value;
}

string Record::toString() const
{
    ostringstream oss;
    oss << Value;
    return oss.str();
}
