#include "Person.h"
#include <string>
#include <vector>

class MedicalWorker : public Person {
private:
    std::string specialization;
    std::vector<int> patientIds; // ID пациентов
public:
    MedicalWorker(const std::string& name, int age, const std::string& specialization);
    void addPatient(int patientId);
    void printInfo() const override;
    const std::vector<int>& getPatientIds() const;
};


