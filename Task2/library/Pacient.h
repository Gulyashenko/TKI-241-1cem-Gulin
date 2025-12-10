#include "Person.h"
#include <iostream>

class Patient : public Person {
private:
    int patientId;
    static int nextId;
    int roomNumber;
    
public:
    Patient();
    Patient(const std::string& name, int age, int roomNumber);
    
    void printInfo() const override;
    void readFromInput() override;
    
    int getId() const;
    int getRoomNumber() const;

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
    friend std::istream& operator>>(std::istream& is, Patient& patient);
};
