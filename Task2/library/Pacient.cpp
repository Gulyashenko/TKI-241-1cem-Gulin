#include "Patient.h"

// Инициализация статической переменной
int Patient::nextId = 1000;

Patient::Patient() : Person(), patientId(nextId++), roomNumber(0) {}

Patient::Patient(const std::string& name, const int age,const int roomNumber, const MedicalWorker* assignedWorker) 
    : Person(name, age), patientId(nextId++), roomNumber(roomNumber), assignedWorker(assignedWorker) {}

void Patient::printInfo() const {
    std::cout << "Patient [ID: " << patientId << " << Room: " << roomNumber << "] ";
    Person::printInfo();
}

void Patient::readFromInput() {
    Person::readFromInput();
    std::cout << "Enter room number: ";
    std::cin >> roomNumber;
    std::cin.ignore();
}

int Patient::getId() const {
    return patientId;
}

int Patient::getRoomNumber() const {
    return roomNumber;
}

MedicalWorker* Patient::getAssignedWorker() const {
    return assignedWorker;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    patient.printInfo();
    return os;
}

std::istream& operator>>(std::istream& is, Patient& patient) {
    patient.readFromInput();
    return is;
}
