#pragma once
#include "Record.h"
#include "Student.h"
#include "Librarian.h"
#include "SoftwareDev.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileRepository {
private:
    Record* records_[100] = { nullptr };
    int count_ = 0;

public:
    /
    bool Add(Record* r) {
        if (count_ >= 100) return false;
        records_[count_++] = r;
        return true;
    }


    void PrintAll() const {
        for (int i = 0; i < count_; ++i) {
            cout << records_[i]->describe() << endl;
        }
    }


};
