#include "MedicalWorker.h"
#include <algorithm>
#include <utility>

MedicalWorker::MedicalWorker() 
    : Person(), specialization(""), patientCount(0), patientCapacity(2) {
    patients = std::make_unique<Patient[]>(patientCapacity);
}

MedicalWorker::MedicalWorker(const std::string& name, const int age, const std::string& specialization) 
    : Person(name, age), specialization(specialization), patientCount(0), patientCapacity(2) {
    patients = std::make_unique<Patient[]>(patientCapacity);
}

MedicalWorker::MedicalWorker(const MedicalWorker& other) 
    : Person(other), specialization(other.specialization), 
      patientCount(other.patientCount), patientCapacity(other.patientCapacity) {
    patients = std::make_unique<Patient[]>(patientCapacity);
    for (int i = 0; i < patientCount; i++) {
        patients[i] = other.patients[i];
    }
}

MedicalWorker& MedicalWorker::operator=(const MedicalWorker& other) {
    if (this != &other) {
        Person::operator=(other);
        specialization = other.specialization;
        patientCount = other.patientCount;
        patientCapacity = other.patientCapacity;
        
        patients = std::make_unique<Patient[]>(patientCapacity);
        for (int i = 0; i < patientCount; i++) {
            patients[i] = other.patients[i];
        }
    }
    return *this;
}

MedicalWorker::MedicalWorker(MedicalWorker&& other) noexcept
    : Person(std::move(other)), 
      specialization(std::move(other.specialization)),
      patients(std::move(other.patients)),
      patientCount(other.patientCount),
      patientCapacity(other.patientCapacity) {
    other.patientCount = 0;
    other.patientCapacity = 0;
}

MedicalWorker& MedicalWorker::operator=(MedicalWorker&& other) noexcept {
    if (this != &other) {
        Person::operator=(std::move(other));
        specialization = std::move(other.specialization);
        patients = std::move(other.patients);
        patientCount = other.patientCount;
        patientCapacity = other.patientCapacity;
        
        other.patientCount = 0;
        other.patientCapacity = 0;
    }
    return *this;
}

void MedicalWorker::resizePatients() {
    if (patientCount >= patientCapacity) {
        patientCapacity *= 2;
        auto newPatients = std::make_unique<Patient[]>(patientCapacity);
        for (size_t i = 0; i < patientCount; i++) {
            newPatients[i] = std::move(patients[i]);
        }
        patients = std::move(newPatients);
    }
}

void MedicalWorker::printInfo() const {
    std::cout << "Medical Worker: ";
    Person::printInfo();
    std::cout << ", Specialization: " << specialization 
              << ", Patients: " << patientCount << "\n";
    
    for (size_t i = 0; i < patientCount; i++) {
        std::cout << "  " << (i + 1) << ". " << patients[i] << "\n";
    }
}

void MedicalWorker::readFromInput() {
    Person::readFromInput();
    std::cout << "Enter specialization: ";
    std::getline(std::cin, specialization);
}

std::string MedicalWorker::getSpecialization() const {
    return specialization;
}

int MedicalWorker::getPatientCount() const {
    return patientCount;
}

const Patient* MedicalWorker::getPatients() const {
    return patients.get();
}

void MedicalWorker::addPatient(const Patient& patient) {
    resizePatients();
    patients[patientCount++] = patient;
}

void MedicalWorker::removePatient(int index) {
    if (index >= 0 && index < patientCount) {
        for (int i = index; i < patientCount - 1; i++) {
            patients[i] = std::move(patients[i + 1]);
        }
        patientCount--;
    }
}

bool MedicalWorker::hasPatient(const std::string& patientName) const {
    for (size_t i = 0; i < patientCount; i++) {
        if (patients[i].getName() == patientName) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const MedicalWorker& worker) {
    worker.printInfo();
    return os;
}

std::istream& operator>>(std::istream& is, MedicalWorker& worker) {
    worker.readFromInput();
    return is;
}
