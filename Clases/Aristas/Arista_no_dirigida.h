#include <utility>
#include <set>
#ifndef GRAPHS_GETGROUP_GETNAME_ARISTA_NO_DIRIGIDA_H
#define GRAPHS_GETGROUP_GETNAME_ARISTA_NO_DIRIGIDA_H

class Arista_no_dirigida{
    string first_id;
    string second_id;
    double weight;
public:
    Arista_no_dirigida(string firstId, string secondId, double weight) : first_id(std::move(firstId)), second_id(std::move(secondId)),
                                                                   weight(weight) {}
    Arista_no_dirigida(string firstId, string secondId) : first_id(std::move(firstId)), second_id(std::move(secondId)),
                                                                   weight(0) {}


    set<string> getParId(){
        set<string> parID;
        parID.insert(first_id);
        parID.insert(second_id);
        return parID;
    }

    const string &getFirstId() const {
        return first_id;
    }

    const string &getSecondId() const {
        return second_id;
    }

    double getWeight() const {
        return weight;
    }

};


#endif //GRAPHS_GETGROUP_GETNAME_ARISTA_NO_DIRIGIDA_H
