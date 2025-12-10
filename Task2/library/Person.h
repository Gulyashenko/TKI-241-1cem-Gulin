#include <iostream>
#include <string>
#include <memory>

class Person {
protected:
    std::string name;
    int age;
    
public:
    Person() = default;
    Person(const std::string& name, int age);
    virtual ~Person() = default;
    
    virtual void printInfo() const;
    virtual void readFromInput();
    
    std::string getName() const;
    int getAge() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    friend std::istream& operator>>(std::istream& is, Person& person);
};
