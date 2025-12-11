#include "Hospital.h"
#include <iostream>
#include <utility>
#include <random>

Hospital::Hospital() : workerCount(0), workerCapacity(2) {
    workers = std::make_unique<MedicalWorker[]>(workerCapacity);
    pacients = std::make_unique<Patient[]>(pacientCapacity);
}

Hospital::Hospital(const Hospital& other) 
    : workerCount(other.workerCount), workerCapacity(other.workerCapacity) {
    workers = std::make_unique<MedicalWorker[]>(workerCapacity);
    for (size_t i = 0; i < workerCount; i++) {
        workers[i] = other.workers[i];
    }
}

Hospital& Hospital::operator=(const Hospital& other) {
    if (this != &other) {
        workerCount = other.workerCount;
        workerCapacity = other.workerCapacity;
        
        workers = std::make_unique<MedicalWorker[]>(workerCapacity);
        for (size_t i = 0; i < workerCount; i++) {
            workers[i] = other.workers[i];
        }
    }
    return *this;
}

Hospital::Hospital(Hospital&& other) noexcept
    : workers(std::move(other.workers)),
      workerCount(other.workerCount),
      workerCapacity(other.workerCapacity) {
    other.workerCount = 0;
    other.workerCapacity = 0;
}

Hospital& Hospital::operator=(Hospital&& other) noexcept {
    if (this != &other) {
        workers = std::move(other.workers);
        workerCount = other.workerCount;
        workerCapacity = other.workerCapacity;
        
        other.workerCount = 0;
        other.workerCapacity = 0;
    }
    return *this;
}

void Hospital::resizeWorkers() {
    if (workerCount >= workerCapacity) {
        workerCapacity *= 2;
        auto newWorkers = std::make_unique<MedicalWorker[]>(workerCapacity);
        for (size_t i = 0; i < workerCount; i++) {
            newWorkers[i] = std::move(workers[i]);
        }
        workers = std::move(newWorkers);
    }
}

void Hospital::resizePacients() {
    if (pacientCount >= pacientCapacity) {
        pacientCapacity *= 2;
        auto newPacients = std::make_unique<Patient[]>(pacientCapacity);
        for (size_t i = 0; i < pacientCount; i++) {
            newPacients[i] = std::move(pacients[i]);
        }
        pacients = std::move(newPacients);
    }
}

int Hospital::getWorkerCount() const {
    return workerCount;
}

const MedicalWorker* Hospital::getWorkers() const {
    return workers.get();
}

int Hospital::getPacientCount() const {
    return pacientCount;
}

const Pacient* Hospital::getPacients() const {
    return pacients.get();
}

void Hospital::addWorker(const MedicalWorker& worker) {
    resizeWorkers();
    workers[workerCount++] = worker;
}

void Hospital::removeWorker(int index) {
    if (index >= 0 && index < workerCount) {
        for (size_t i = index; i < workerCount - 1; i++) {
            workers[i] = std::move(workers[i + 1]);
        }
        workerCount--;
    }
}

void Hospital::addPatient(const Patient& patient) {
    resizePacients();
    pacients[pacientCount++] = patient;
}

void Hospital::removePatient(int index) {
    if (index >= 0 && index < pacientCount) {
        for (size_t i = index; i < pacientCount - 1; i++) {
            pacients[i] = std::move(pacients[i + 1]);
        }
        pacientCount--;
    }
}

MedicalWorker* Hospital::findWorkerByName(const std::string& name) const {
    for (size_t i = 0; i < workerCount; i++) {
        if (workers[i].getName() == name) {
            return &workers[i];
        }
    }
    return nullptr;
}

MedicalWorker* Hospital::findWorkerByPatientName(const std::string& patientName) const {
    for (size_t i = 0; i < workerCount; i++) {
        if (workers[i].hasPatient(patientName)) {
            return &workers[i];
        }
    }
    return nullptr;
}

void Hospital::printAllWorkers() const {
    std::cout << "\n=== All Medical Workers ===\n";
    for (size_t i = 0; i < workerCount; i++) {
        std::cout << workers[i] << "\n";
    }
}

void Hospital::printPatientsOfWorker(const std::string& workerName) const {
    std::cout << "\n=== Patients of " << workerName << " ===\n";
    MedicalWorker* worker = findWorkerByName(workerName);
    if (worker) {
        std::cout << *worker;
    } else {
        std::cout << "Worker not found.\n";
    }
}

void Hospital::printAllPatients() const {
    std::cout << "\n=== All Patients ===\n";
    for (size_t i = 0; i < workerCount; i++) {
        const Patient* patients = workers[i].getPatients();
        int patientCount = workers[i].getPatientCount();
        for (size_t j = 0; j < patientCount; j++) {
            std::cout << patients[j] << " (Doctor: " << workers[i].getName() << ")\n";
        }
    }
}

void Hospital::printWorkerByPatientName(const std::string& patientName) const {
    std::cout << "\n=== Worker for patient " << patientName << " ===\n";
    MedicalWorker* worker = findWorkerByPatientName(patientName);
    if (worker) {
        std::cout << "Doctor: " << worker->getName() 
                  << " (Specialization: " << worker->getSpecialization() << ")\n";
    } else {
        std::cout << "Patient not found or has no assigned doctor.\n";
    }
}

void Hospital::printPatientsByRoom() const {
    std::cout << "\n=== Patients by 'Room' (simplified - by doctor) ===\n";
    for (size_t i = 0; i < workerCount; i++) {
        std::cout << "\nDoctor: " << workers[i].getName() << "\n";
        const Patient* patients = workers[i].getPatients();
        int patientCount = workers[i].getPatientCount();
        
        if (patientCount == 0) {
            std::cout << "  No patients\n";
        } else {
            for (size_t j = 0; j < patientCount; j++) {
                std::cout << "  Room " << (j + 1) << ": " << patients[j] << "\n";
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "=== HOSPITAL STATUS ===\n";
    os << "Total workers: " << hospital.workerCount << "\n";
    
    int totalPatients = 0;
    for (size_t i = 0; i < hospital.workerCount; i++) {
        totalPatients += hospital.workers[i].getPatientCount();
    }
    os << "Total patients: " << totalPatients << "\n\n";
    
    for (int i = 0; i < hospital.workerCount; i++) {
        os << hospital.workers[i] << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Hospital& hospital) {
    int numWorkers = 0;
    std::cout << "Enter number of medical workers: ";
    is >> numWorkers;
    is.ignore();
    
    for (size_t i = 0; i < numWorkers; i++) {
        std::cout << "\nMedical Worker #" << (i + 1) << ":\n";
        MedicalWorker worker;
        is >> worker; 
        
        hospital.addWorker(worker);
    }

     int numPacient = 0;
    std::cout << "Enter number of pacients: ";
    is >> numPacient;
    is.ignore();
    
    for (size_t i = 0; i < numPacient; i++) {
        std::cout << "\n Pacient#" << (i + 1) << ":\n";
        Pacient pacient;
        is >> worker;
                
        hospital.addPacient(pacient);
        std::unique_ptr<MedicalWorker[]> worker = hospital.getWorkers()[i];
        int workerCount = hospital.getWorkerCount();
        int workerIndex = rand() % workerCount;
        pacient.setAssignedWorker(worker[workerIndex]);
    }
    return is;
}
