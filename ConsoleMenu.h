#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include <iostream>
#include "FileS.h"

using namespace std;

class ConsoleMenu {
private:
    FileRepository &repository;

public:
    ConsoleMenu(FileRepository &repo) : repository(repo) {}

    void Show() {
        int choice;
        do {
            cout << "\n====== Menu ======\n";
            cout << "1. Add Student\n";
            cout << "2. Add Librarian\n";
            cout << "3. Add Software Developer\n";
            cout << "4. Search by surname\n";
            cout << "5. Save to file\n";
            cout << "6. Read file\n";
            cout << "7. Search students with ideal weight\n";
            cout << "8. Delete by surname\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: \n";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:      // Починає цикл для створення студента
                    AddStudent();
                    break;
                case 2:      // Починає цикл для створення бібліотекаря
                    AddLibrarian();
                    break;
                case 3:      // Починає цикл для створення програміста
                    AddSoftwareDeveloper();
                    break;
                case 4: {    // Завантажує дані з файлу і починає пошук всієї інфи за прізвищем
                    repository.LoadAll("database.txt");
                    string surname;
                    cout << "Enter surname to search: ";
                    getline(cin, surname);
                    repository.SearchBySurname(surname);
                    break;
                }
                case 5:      // Зберігає всю інфу у файл
                    repository.SaveAll("database.txt");
                    cout << "Saving data.\n";
                    break;
                case 6:      // Зчитує інфу з файлу і виводить її в консоль
                    repository.LoadAll("database.txt");
                    repository.PrintAll();
                    break;
                case 7: {    // Виводить інфу про студентів з ідеальною вагою
                    repository.LoadAll("database.txt");
                    repository.PrintIdealWeightStudents();
                    break;
                }
                case 8: {    // Шукає прізвище в файлі і видаляє всю інфу про нього
                    repository.LoadAll("database.txt");
                    string surname;
                    cout << "Enter surname to delete: ";
                    getline(cin, surname);
                    repository.DeleteBySurname(surname);
                    repository.SaveAll("database.txt");
                    break;
                }
                case 0:      // Вихід
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Wrong choice!\n";
            }
        } while (choice != 0);
    }

    // Виводить блок тексту і дозволяє вводити інфу при створенні студента
    void AddStudent() {
        string fname, lname, studentId, passport, skills;
        int height, weight;

        cout << "Enter name: ";
        getline(cin, fname);
        cout << "Enter surname: ";
        getline(cin, lname);
        cout << "Enter height: ";
        cin >> height;
        cout << "Enter weight: ";
        cin >> weight;
        cin.ignore();
        cout << "Enter student id: ";
        getline(cin, studentId);
        cout << "Enter id: ";
        getline(cin, passport);
        cout << "Enter additional skills: ";
        getline(cin, skills);

        repository.Add(new Student(fname, lname, height, weight, studentId, passport, skills));
        cout << "Student has been added.\n";
    }

    // Виводить блок тексту і дозволяє вводити інфу при створенні бібліотекаря
    void AddLibrarian() {
        string fname, lname, employeeId, skills;

        cout << "Enter name: ";
        getline(cin, fname);
        cout << "Enter surname: ";
        getline(cin, lname);
        cout << "Enter employee Id: ";
        getline(cin, employeeId);
        cout << "Enter additional skills: ";
        getline(cin, skills);

        repository.Add(new Librarian(fname, lname, employeeId, skills));
        cout << "Librarian has been added.\n";
    }

    // Виводить блок тексту і дозволяє вводити інфу при створенні програміста
    void AddSoftwareDeveloper() {
        string fname, lname, devId, lang, skills;

        cout << "Enter name: ";
        getline(cin, fname);
        cout << "Enter surname: ";
        getline(cin, lname);
        cout << "Enter developer's Id: ";
        getline(cin, devId);
        cout << "Enter programming language: ";
        getline(cin, lang);
        cout << "Enter additional skills: ";
        getline(cin, skills);

        repository.Add(new SoftwareDeveloper(fname, lname, devId, lang, skills));
        cout << "Software developer has been added.\n";
    }
};

#endif
