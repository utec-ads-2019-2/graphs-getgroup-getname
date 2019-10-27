#include <utility>

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

};


#endif //GRAPHS_GETGROUP_GETNAME_ARISTA_NO_DIRIGIDA_H
