#include "MedicalWorker.h"
#include <iostream>
#include <memory>
#include <vector>

class Hospital {
private:
    std::unique_ptr<MedicalWorker[]> workers;  // Массив медицинских работников
    int workerCount;
    int workerCapacity;
    int pacientCapacity;
    std::vector<Patient> patients;
    
    void resizeWorkers();
    void resizePacient();

public:
    Hospital();
    ~Hospital() = default;
    
    Hospital(const Hospital& other);
    Hospital& operator=(const Hospital& other);
    Hospital(Hospital&& other) noexcept;
    Hospital& operator=(Hospital&& other) noexcept;
    
    int getWorkerCount() const;
    const MedicalWorker* getWorkers() const;

    int getPacientCount() const;
    const Pacient* getPacients() const;
    
    void addWorker(const MedicalWorker& worker);
    void removeWorker(int index);

    void addPacient(const Patient& patient);
    void removePacient(int index);
    
    MedicalWorker* findWorkerByName(const std::string& name) const;
    MedicalWorker* findWorkerByPatientName(const std::string& patientName) const;
    
    void printAllWorkers() const;
    void printPatientsOfWorker(const std::string& workerName) const;
    void printAllPatients() const;
    void printWorkerByPatientName(const std::string& patientName) const;
    void printPatientsByRoom() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
    friend std::istream& operator>>(std::istream& is, Hospital& hospital);
};
