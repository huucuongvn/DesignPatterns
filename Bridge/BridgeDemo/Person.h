#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>

class Person
{
public:
    std::string name;
    class PersonImpl;
    PersonImpl* impl;
    Person();
    ~Person();
    void greet();
};

#endif // PERSON_H
