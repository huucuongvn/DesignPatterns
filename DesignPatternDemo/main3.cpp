#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

struct Document;
//struct Imachine{
//    virtual void print(Document &doc) = 0;
//    virtual void scan(Document &doc) = 0;
//    virtual void fax(Document &doc) = 0;
//};
//struct MFP : Imachine{
//    void print(Document &doc) override {
//    }
//    void scan(Document &doc) override {
//    }
//    void fax(Document &doc) override {
//    }
//};
//struct scanner : Imachine {
//    void print(Document &doc) override {
//    }
//    void scan(Document &doc) override {
//    }
//    void fax(Document &doc) override {
//    }
//};
struct Iprinter{
    virtual void print(Document &doc) = 0;
};
struct Iscanner{
    virtual void scan(Document &doc) = 0;
};
struct Ifax{
    virtual void fax(Document &doc) = 0;
};
struct Printer : Iprinter {
    void print(Document  &doc) override {
    }
};
struct Scanner : Iscanner {
    void scan(Document  &doc) override {
    }
};
struct Imachine : Iprinter, Iscanner {};
struct Machine : Imachine {
    Iprinter &printer;
    Iscanner &scanner;
    Machine(Iprinter &printer, Iscanner &scanner)
        :printer(printer), scanner(scanner) {}
    void print(Document &doc) override {
        printer.print(doc);
    }
    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};

int main()
{

    return 0;
}
