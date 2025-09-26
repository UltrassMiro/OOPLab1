#pragma once
#include "Person.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Student : public Person {
private:
    int heightCm_;
    int weightKg_;
    string studentId_;
    string passport_;

public:
    Student(const string& first, const string& last,
            int height, int weight,
            const string& studentId,
            const string& passport)
        : Person(first, last),
          heightCm_(height),
          weightKg_(weight),
          studentId_(studentId),
          passport_(passport) {}

    string typeName() const override {
        return "Student";
    }

    string serializeAttributes() const override {
        ostringstream oss;
        oss << "\"firstname\": \"" << firstName() << "\",\n"
            << "\"lastname\": \"" << lastName() << "\",\n"
            << "\"height\": \"" << heightCm_ << "\",\n"
            << "\"weight\": \"" << weightKg_ << "\",\n"
            << "\"studentId\": \"" << studentId_ << "\",\n"
            << "\"passport\": \"" << passport_ << "\"";
        return oss.str();
    }

    string describe() const override {
        ostringstream oss;
        oss << "Student " << firstName() << " " << lastName()
            << " [ID=" << studentId_
            << ", H=" << heightCm_ << "cm"
            << ", W=" << weightKg_ << "kg"
            << ", P=" << passport_ << "]";
        return oss.str();
    }

    void Study() {
    }

    bool isIdealWeight() const {
        return (heightCm_ - 110) == weightKg_;
    }

    const string& studentId() const {
        return studentId_;
    }
};
