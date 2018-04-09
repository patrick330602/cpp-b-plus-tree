#include <string>
#include <sstream>
#include "Definitions.h"
#include "Record.h"

Record::Record(ValueType aValue)
: fValue(aValue)
{}

ValueType Record::value() const
{
    return fValue;
}

string Record::toString() const
{
    ostringstream oss;
    oss << fValue;
    return oss.str();
}
