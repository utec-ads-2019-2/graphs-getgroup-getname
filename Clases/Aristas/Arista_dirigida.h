#ifndef GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
#define GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H


class Arista_dirigida{
    int Id_begin;
    int Id_End;
    double weight;
public:
    Arista_dirigida(int idBegin, int idEnd) : Id_begin(idBegin), Id_End(idEnd), weight(0) {}

    int getIdBegin() const {
        return Id_begin;
    }

    void setIdBegin(int idBegin) {
        Id_begin = idBegin;
    }

    int getIdEnd() const {
        return Id_End;
    }

    void setIdEnd(int idEnd) {
        Id_End = idEnd;
    }

    double getWeight() const {
        return weight;
    }

    void setWeight(double d) {
        weight = d;
    }
};


#endif //GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
