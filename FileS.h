#pragma once
#include "Record.h"
#include "Student.h"
#include "Librarian.h"
#include "SoftwareDev.h"
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
using namespace std;

class FileRepository {
private:
    Record* records_[100] = { nullptr };
    int count_ = 0;

public:

    bool Add(Record* r) {
        if (count_ >= 100) return false;
        records_[count_++] = r;
        return true;
    }

    // Виводить всю інфу з файлу
    void PrintAll() const {
        for (int i = 0; i < count_; ++i) {
            cout << records_[i]->describe() << endl;
        }
    }

    // Пошук по фамілії
    void SearchBySurname(const string& surname) const {
        bool found = false;
        for (int i = 0; i < count_; ++i) {
            string lname;
            if (Student* s = dynamic_cast<Student*>(records_[i])) lname = s->lastName();
            else if (Librarian* l = dynamic_cast<Librarian*>(records_[i])) lname = l->lastName();
            else if (SoftwareDeveloper* d = dynamic_cast<SoftwareDeveloper*>(records_[i])) lname = d->lastName();

            if (lname == surname) {
                cout << records_[i]->describe() << endl;
                found = true;
            }
        }
        if (!found) cout << "No person found with surname " << surname << endl;
    }

    // Шукає та виводить інфу про студентів з ідеальною вагою
    void PrintIdealWeightStudents() const {
        bool found = false;
        cout << "Students with ideal weight:" << endl;
        for (int i = 0; i < count_; ++i) {
            if (Student* s = dynamic_cast<Student*>(records_[i])) {
                if (s->isIdealWeight()) {
                    cout << s->describe() << endl;
                    found = true;
                }
            }
        }
        if (!found) cout << "No students with ideal weight found." << endl;
    }

    // Видалення інфи за фамілією
    void DeleteBySurname(const string& surname) {
        int newCount = 0;
        for (int i = 0; i < count_; ++i) {
            string lname;
            if (Student* s = dynamic_cast<Student*>(records_[i])) lname = s->lastName();
            else if (Librarian* l = dynamic_cast<Librarian*>(records_[i])) lname = l->lastName();
            else if (SoftwareDeveloper* d = dynamic_cast<SoftwareDeveloper*>(records_[i])) lname = d->lastName();

            if (lname != surname) {
                records_[newCount++] = records_[i];
            } else {
                delete records_[i];
            }
        }
        count_ = newCount;
    }

    // Зберігає всі введені дані в файл
    bool SaveAll(const string& filename) {
        ofstream ofs(filename, ios::out | ios::trunc);
        if (!ofs.is_open()) return false;

        for (int i = 0; i < count_; ++i) {
            Record* r = records_[i];
            if (!r) continue;
            ofs << r->typeName() << " " << r->objectName() << "\n";
            ofs << "{\n";
            ofs << r->serializeAttributes() << "\n";
            ofs << "};\n\n";
        }
        ofs.close();
        return true;
    }

    // Функція для завантаження інфи до масиву
    int LoadAll(const string& filename) {
        ifstream ifs(filename);
        if (!ifs.is_open()) return 0;

        string line;
        count_ = 0;
        while (count_ < 100 && getline(ifs, line)) { // Читає всі рядки по порядку з лімітом в 100
            if (line.find_first_not_of(" \t\r\n") == string::npos) continue;

            // Регулювання для заголовку (ім'я фамілія персони)
            smatch m;
            regex headerRx(R"(^\s*([A-Za-z]+)\s+([A-Za-z0-9_]+)\s*$)");
            if (!regex_match(line, m, headerRx)) continue;
            string type = m[1];
            string objName = m[2];

            string block;
            while (getline(ifs, line)) {
                block += line + "\n";
                if (line.find('}') != string::npos) break;
            }

            // регулювання "key": "value"
            regex kv("\"([^\"]+)\":\\s*\"([^\"]*)\"");
            sregex_iterator it(block.begin(), block.end(), kv);
            sregex_iterator end;

            string firstname, lastname;
            string heightStr, weightStr, studentId, passport, skills;
            string employeeId, devId, lang;

            // Парсер для "key": "value", заповнює атрибути інфою
            for (; it != end; ++it) {
                string key = (*it)[1];
                string val = (*it)[2];
                if (key == "firstname") firstname = val;
                else if (key == "lastname") lastname = val;
                else if (key == "height") heightStr = val;
                else if (key == "weight") weightStr = val;
                else if (key == "studentId") studentId = val;
                else if (key == "passport") passport = val;
                else if (key == "skills") skills = val;
                else if (key == "employeeId") employeeId = val;
                else if (key == "devId") devId = val;
                else if (key == "language") lang = val;
            }

            if (type == "Student") {
                int h = heightStr.empty() ? 0 : stoi(heightStr); // Якщо висота або вага відсутні, виставляє 0
                int w = weightStr.empty() ? 0 : stoi(weightStr);

                // Створює об'єкт, конструктор приймає дані і записує їх в масив
                records_[count_++] = new Student(firstname, lastname, h, w, studentId, passport, skills);
            } else if (type == "Librarian") {
                records_[count_++] = new Librarian(firstname, lastname, employeeId, skills);
            } else if (type == "SoftwareDeveloper") {
                records_[count_++] = new SoftwareDeveloper(firstname, lastname, devId, lang, skills);
            }
        }

        ifs.close();
        return count_;
    }
};
