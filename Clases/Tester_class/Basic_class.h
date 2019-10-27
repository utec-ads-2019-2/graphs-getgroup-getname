#ifndef GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
#define GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
#include <utility>

#include "../Aristas/Arista_no_dirigida.h"

class String_class{
    string Name;

public:
    typedef Arista_no_dirigida Edge_type;
    explicit String_class(string name) : Name(std::move(name)) {}

    const string &getName() const {
        return Name;
    }
};


#endif //GRAPHS_GETGROUP_GETNAME_BASIC_CLASS_H
