#include "MedicalWorker.h"
#include <iostream>
#include <memory>

class Hospital {
private:
    std::unique_ptr<MedicalWorker[]> workers;  // Массив медицинских работников
    int workerCount;
    int workerCapacity;
    
    void resizeWorkers();
    
public:
    Hospital();
    ~Hospital() = default;
    
    Hospital(const Hospital& other);
    Hospital& operator=(const Hospital& other);
    Hospital(Hospital&& other) noexcept;
    Hospital& operator=(Hospital&& other) noexcept;
    
    int getWorkerCount() const;
    const MedicalWorker* getWorkers() const;
    
    void addWorker(const MedicalWorker& worker);
    void removeWorker(int index);
    
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
