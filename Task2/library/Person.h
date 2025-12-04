#include <string>

class Person {
protected:
    std::string name;
    int age;
public:
    Person(const std::string& name, int age);
    virtual ~Person() = default;
    virtual void printInfo() const;
};
