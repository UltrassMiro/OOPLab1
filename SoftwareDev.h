#pragma once
#include "Person.h"
#include <string>
#include <sstream>
using namespace std;

class SoftwareDeveloper : public Person {
private:
    string devId_;
    string primaryLanguage_;
public:
    SoftwareDeveloper(const string& first, const string& last,
                      const string& devId,
                      const string& lang)
        : Person(first, last), devId_(devId), primaryLanguage_(lang) {}

    string typeName() const override { return "SoftwareDeveloper"; }

    string serializeAttributes() const override {
        ostringstream oss;
        oss << "\"firstname\": \"" << firstName() << "\",\n"
            << "\"lastname\": \"" << lastName() << "\",\n"
            << "\"devId\": \"" << devId_ << "\",\n"
            << "\"language\": \"" << primaryLanguage_ << "\"";
        return oss.str();
    }

    string describe() const override {
        ostringstream oss;
        oss << "SoftwareDeveloper " << firstName_ << " " << lastName_
            << " [devId=" << devId_ << ", lang=" << primaryLanguage_ << "]";
        return oss.str();
    }

    void Develop() {}
    const string& devId() const { return devId_; }
};
