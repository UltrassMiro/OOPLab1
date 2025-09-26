#pragma once
#include "Record.h"
#include <string>
using namespace std;

class Person : public Record {
protected:
    string firstName_;
    string lastName_;
public:
    Person(const string& first, const string& last)
        : firstName_(first), lastName_(last) {}
    virtual ~Person() = default;

    const string& firstName() const { return firstName_; }
    const string& lastName() const { return lastName_; }

    string objectName() const override {
        return firstName_ + lastName_;
    }
};
