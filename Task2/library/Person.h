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
    
    // Виртуальные методы для полиморфизма
    virtual void printInfo() const;
    virtual void readFromInput();
    
    // Геттеры
    std::string getName() const;
    int getAge() const;
    
    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    friend std::istream& operator>>(std::istream& is, Person& person);
};
