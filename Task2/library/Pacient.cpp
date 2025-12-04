#include "Patient.h"

// Инициализация статической переменной
int Patient::nextId = 1000;

Patient::Patient() : Person(), patientId(nextId++) {}

Patient::Patient(const std::string& name, int age) 
    : Person(name, age), patientId(nextId++) {}

void Patient::printInfo() const {
    std::cout << "Patient [ID: " << patientId << "] ";
    Person::printInfo();
}

void Patient::readFromInput() {
    Person::readFromInput();
    // ID генерируется автоматически
}

int Patient::getId() const {
    return patientId;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    patient.printInfo();
    return os;
}

std::istream& operator>>(std::istream& is, Patient& patient) {
    patient.readFromInput();
    return is;
}
