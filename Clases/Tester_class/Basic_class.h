#ifndef GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
#define GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
#include <utility>


class String_class{
private:
    string Name;
public:
    explicit String_class(string name) : Name(std::move(name)) {}

    const string &getName() const {
        return Name;
    }

    static bool is_Directed(){
        return false;
    };

    ~String_class()= default;

};


#endif //GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
