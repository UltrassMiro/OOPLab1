#pragma once
#include "Person.h"
#include <string>
#include <sstream>
using namespace std;

class Librarian : public Person {
private:
    string employeeId_;
    string skills_;
public:
    // Конструктор бібліотекаря
    Librarian(const string& first, const string& last,
              const string& employeeId,
                    string skills)
        : Person(first, last), employeeId_(employeeId), skills_(skills) {}

    string typeName() const override { return "Librarian"; }

    // Підготовка до збереження у файл
    string serializeAttributes() const override {
        ostringstream oss;
        oss << "\"firstname\": \"" << firstName() << "\",\n"
            << "\"lastname\": \"" << lastName() << "\",\n"
            << "\"employeeId\": \"" << employeeId_ << "\", \n"
            << "\"skills\": \"" << skills_ << "\"";
        return oss.str();
    }
    // Спрощення інфи для виводу в консоль
    string describe() const override {
        ostringstream oss;
        oss << "Librarian " << firstName_ << " " << lastName_
            << " [Id=" << employeeId_
            << ", S=" << skills_ << "]";
        return oss.str();
    }

    void OrganizeBooks() {}
    const string& employeeId() const { return employeeId_; }
};
