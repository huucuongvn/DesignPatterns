#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

using namespace std;

class HtmlElement {
    friend class HtmlBuider;
    string name, text;
    vector<HtmlElement> elements;
    const size_t indent_size=2;

    HtmlElement() {}
    HtmlElement(const string &name, const string &text)
        :name(name), text(text) {}
public:
    string str(int indent=0) const {
        ostringstream oss;
        string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if(text.size()>0)
            oss << string(indent_size*(indent+1), ' ') << text <<endl;
        for(const auto &e : elements)
            oss << e.str(indent+1);
        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
    static HtmlBuider create(string root_name) {
        return {root_name};
    }
};

class HtmlBuider {
    HtmlElement root;
public:
    HtmlBuider(string root_name) {
        root.name=root_name;
    }
    HtmlBuider& add_child(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }
    HtmlBuider* add_child2(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }
    HtmlElement build() { return root;}
    string str() const { return root.str(); }
    operator HtmlElement() const {
        return root;
    }
};

int main()
{
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    cout << output << endl;

    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for(auto w : words)
        oss << " <li>" << w << "</li>";
    oss << "<ul>";
    cout << oss.str() << endl;

    HtmlBuider builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    cout << builder.str() << endl;

    HtmlElement elem = HtmlElement::create("ul").add_child("","");

    return 0;
}
