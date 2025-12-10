#include "Person.h"
#include "Patient.h"
#include <iostream>
#include <memory>

class MedicalWorker : public Person {
private:
    std::string specialization;
    std::unique_ptr<Patient[]> patients;    
    int patientCount;
    int patientCapacity;
    
    void resizePatients();
    
public:
    MedicalWorker();
    MedicalWorker(const std::string& name, int age, const std::string& specialization);
    ~MedicalWorker() = default;
    
    MedicalWorker(const MedicalWorker& other);
    MedicalWorker& operator=(const MedicalWorker& other);
    MedicalWorker(MedicalWorker&& other) noexcept;
    MedicalWorker& operator=(MedicalWorker&& other) noexcept;
    
    void printInfo() const override;
    void readFromInput() override;
    
    std::string getSpecialization() const;
    int getPatientCount() const;
    const Patient* getPatients() const;
    
    void addPatient(const Patient& patient);
    void removePatient(int index);
    bool hasPatient(const std::string& patientName) const;
    
    friend std::ostream& operator<<(std::ostream& os, const MedicalWorker& worker);
    friend std::istream& operator>>(std::istream& is, MedicalWorker& worker);
};

#endif
