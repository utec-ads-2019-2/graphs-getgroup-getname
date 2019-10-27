#include <utility>

#ifndef GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
#define GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H


class Arista_dirigida{
    string Id_begin;
    string Id_End;
    double weight;
public:
    Arista_dirigida(string idBegin, string idEnd) : Id_begin(std::move(idBegin)), Id_End(std::move(idEnd)), weight(0) {}
    Arista_dirigida(string idBegin, string idEnd, double weight) : Id_begin(std::move(idBegin)), Id_End(std::move(idEnd)), weight(weight) {}

    string getIdBegin() const {
        return Id_begin;
    }

    void setIdBegin(string idBegin) {
        Id_begin = std::move(idBegin);
    }

    string getIdEnd() const {
        return Id_End;
    }

    void setIdEnd(string idEnd) {
        Id_End = std::move(idEnd);
    }

    double getWeight() const {
        return weight;
    }

    void setWeight(double d) {
        weight = d;
    }
};


#endif //GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
