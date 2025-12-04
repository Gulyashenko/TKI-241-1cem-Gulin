#include "Patient.h"
#include <iostream>

Patient::Patient(const std::string& name, int age, int patientId, int roomNumber, int doctorId)
    : Person(name, age), patientId(patientId), roomNumber(roomNumber), doctorId(doctorId) {}

void Patient::printInfo() const {
    Person::printInfo();
    std::cout << ", Patient ID: " << patientId 
              << ", Room: " << roomNumber 
              << ", Doctor ID: " << doctorId << std::endl;
}

int Patient::getDoctorId() const {
    return doctorId;
}

int Patient::getRoomNumber() const {
    return roomNumber;
}
