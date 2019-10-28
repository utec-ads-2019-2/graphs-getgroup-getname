#include <utility>
#include <set>
#ifndef GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
#define GRAPHS_GETGROUP_GETNAME_ARISTA_DIRIGIDA_H
using namespace std;

class Arista{
    string Id_begin;
    string Id_End;
    double weight;
public:
    Arista(string idBegin, string idEnd) : Id_begin(std::move(idBegin)), Id_End(std::move(idEnd)), weight(0) {}
    Arista(string idBegin, string idEnd, double weight) : Id_begin(std::move(idBegin)), Id_End(std::move(idEnd)), weight(weight) {}

    bool operator ==(Arista toCompare){
        return toCompare.getParId() == getParId();
    }

    string getIdBegin() const {
        return Id_begin;
    }

    void setIdBegin(string idBegin) {
        Id_begin = std::move(idBegin);
    }

    set<string> getParId(){
        set<string> parID;
        parID.insert(Id_begin);
        parID.insert(Id_End);
        return parID;
    }

    pair<string,string> getPair(){
        pair<string,string> parID;
        parID.first=(Id_begin);
        parID.second=(Id_End);
        return parID;
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
