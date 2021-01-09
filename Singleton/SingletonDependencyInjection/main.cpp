#define _USE_MATH_DEFINES
#define _HAS_AUTO_PTR_ETC 1
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>
#include <boost/lexical_cast.hpp>
#define GTEST_LANG_CXX11 1

using namespace std;
using namespace boost;

class Database {
public:
    virtual int get_population(const string& name) = 0;

};

class SingletonDatabase : public Database {
    SingletonDatabase() {
        cout << "Initializing database\n";
        ifstream ifs("capitals.txt");
        string s,s2;
        while(getline(ifs,s)) {
            getline(ifs,s2);
            int pop = lexical_cast<int>(s2);
            capitals[s]=pop;
        }
    }
    map<string, int> capitals;
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }
    int get_population(const string& name) {
        return capitals[name];
    }
};
class DummyDatabase : public Database {
    map<string, int> capitals;
public:
    DummyDatabase() {
        capitals["alpha"]=1;
        capitals["beta"]=2;
        capitals["gamma"]=3;
    }
    int get_population(const string &name) override {
        return capitals[name];
    }
};

struct SingletonrecordFinder {
    int total_population(vector<string> names) {
        int result{0};
        for(auto& name:names)
            result+=SingletonDatabase::get().get_population(name);
        return result;
    }
};
struct ConfigurableRecordFinder {
    Database& db;
    ConfigurableRecordFinder(Database &db) : db(db) {}
    int total_population(vector<string> names) {
        int result{0};
        for(auto& name:names)
            result+=db.get_population(name);
        return result;
    }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest) {
    SingletonrecordFinder rf;
    vector<string> names{"Seoul", "Mexico City"};
    int tp = rf.total_population(names);
    EXPECT_EQ(17500000+17400000, tp);
}
TEST(RecordFinderTests, DependantTotalPopulationTest) {
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};
    EXPECT_EQ(4, rf.total_population(vector<string>{"alpha", "gamma"}));

}

int main()
{
    string city="Tokyo";
    cout << city << " has population " << SingletonDatabase::get().get_population(city) << endl;

    return 0;
}
