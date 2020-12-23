#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
using namespace std;

struct Address {
    string street,city;
    int suite;
    Address(const string &street, const string &city, int suite)
        :street(street), city(city), suite(suite) {}
    Address(const Address& address)
        :street{address.street}, city{address.city}, suite{address.suite} {}
    friend ostream &operator<<(ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact {
    string name;
    Address* address;
    Contact(const string &name, Address *address)
        :name(name), address(address) {}
    Contact(const Contact& other)
        :name{other.name}, address{new Address{*other.address}} {}
    friend ostream &operator<<(ostream &os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;
        return os;
    }
};

int main()
{
    Contact john{"John", new Address{"201 Nguyen Xi", "THPCM", 123}};
//    contact Jane{"Jane Smith", Address{"201 Nguyen Xi", "THPCM", 113}};
    Contact jane{john};//shallow copy
    jane.name="Jane Smith";
    jane.address->suite=113;
    cout << john << endl << jane << endl;
    return 0;
}
