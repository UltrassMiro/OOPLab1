#pragma once
#include <string>
using namespace std;

class Record {
public:
    virtual ~Record() = default;
    virtual string typeName() const = 0;
    virtual string objectName() const = 0;
    virtual string serializeAttributes() const = 0;
    virtual string describe() const = 0;
};

