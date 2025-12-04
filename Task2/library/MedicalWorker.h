#include "Person.h"
#include "Patient.h"
#include <iostream>
#include <memory>

class MedicalWorker : public Person {
private:
    std::string specialization;
    std::unique_ptr<Patient[]> patients;  // Массив пациентов
    int patientCount;
    int patientCapacity;
    
    void resizePatients();
    
public:
    MedicalWorker();
    MedicalWorker(const std::string& name, int age, const std::string& specialization);
    ~MedicalWorker() = default;
    
    // Правило пяти
    MedicalWorker(const MedicalWorker& other);
    MedicalWorker& operator=(const MedicalWorker& other);
    MedicalWorker(MedicalWorker&& other) noexcept;
    MedicalWorker& operator=(MedicalWorker&& other) noexcept;
    
    // Переопределение виртуальных методов
    void printInfo() const override;
    void readFromInput() override;
    
    // Специфичные методы для MedicalWorker
    std::string getSpecialization() const;
    int getPatientCount() const;
    const Patient* getPatients() const;
    
    void addPatient(const Patient& patient);
    void removePatient(int index);
    bool hasPatient(const std::string& patientName) const;
    
    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const MedicalWorker& worker);
    friend std::istream& operator>>(std::istream& is, MedicalWorker& worker);
};

#endif
