#pragma once
#include "Person.h"
#include <string>
#include <sstream>
using namespace std;

class Librarian : public Person {
private:
    string employeeId_;
public:
    Librarian(const string& first, const string& last,
              const string& employeeId)
        : Person(first, last), employeeId_(employeeId) {}

    string typeName() const override { return "Librarian"; }

    string serializeAttributes() const override {
        ostringstream oss;
        oss << "\"firstname\": \"" << firstName() << "\",\n"
            << "\"lastname\": \"" << lastName() << "\",\n"
            << "\"employeeId\": \"" << employeeId_ << "\"";
        return oss.str();
    }

    string describe() const override {
        ostringstream oss;
        oss << "Librarian " << firstName_ << " " << lastName_
            << " [empId=" << employeeId_ << "]";
        return oss.str();
    }

    void OrganizeBooks() {}
    const string& employeeId() const { return employeeId_; }
};
