#include "Person.h"
#include <iostream>

class Patient : public Person {
private:
    int patientId;
    static int nextId;
    int roomNumber;
    MedicalWorker* assignedWorker;
    
public:
    Patient();
    Patient(const std::string& name,const int age,const int roomNumber, const MedicalWorker* assignedWorker);
    
    void printInfo() const override;
    void readFromInput() override;
    
    int getId() const;
    int getRoomNumber() const;
    MedicalWorker* getAssignedWorker() const;

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
    friend std::istream& operator>>(std::istream& is, Patient& patient);
};
