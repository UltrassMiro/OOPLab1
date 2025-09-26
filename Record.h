#pragma once
#include <string>
using namespace std;

class Record {
public:
    virtual ~Record() = default; // Деструктор для правильної роботи функцій видалення
    virtual string typeName() const = 0; // Тип об'єкта
    virtual string objectName() const = 0; // Ім'я фамілія
    virtual string serializeAttributes() const = 0; // Збереження у файл
    virtual string describe() const = 0; // Скорочений вивід інфи в консоль
};

