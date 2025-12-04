#include "Person.h"
#include <iostream>

class Patient : public Person {
private:
    int patientId;
    static int nextId;  // Статическая переменная для генерации ID
    
public:
    Patient();
    Patient(const std::string& name, int age);
    
    // Переопределение виртуальных методов
    void printInfo() const override;
    void readFromInput() override;
    
    int getId() const;
    
    // Операторы ввода/вывода (скрывают родительские)
    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
    friend std::istream& operator>>(std::istream& is, Patient& patient);
};
