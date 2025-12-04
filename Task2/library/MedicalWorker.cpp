#include "MedicalWorker.h"
#include <iostream>

MedicalWorker::MedicalWorker(const std::string& name, int age, const std::string& specialization)
    : Person(name, age), specialization(specialization) {}

void MedicalWorker::addPatient(int patientId) {
    patientIds.push_back(patientId);
}

void MedicalWorker::printInfo() const {
    Person::printInfo();
    std::cout << ", Specialization: " << specialization 
              << ", Patients: " << patientIds.size() << std::endl;
}

const std::vector<int>& MedicalWorker::getPatientIds() const {
    return patientIds;
}
