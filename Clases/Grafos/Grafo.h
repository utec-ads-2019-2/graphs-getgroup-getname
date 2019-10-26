#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include "../Vertices/Vertice.h"
using namespace std;



template<typename Node_type, typename weight_type>
class Grafo{
public:
    typedef typename Node_type::Edge_type Edge_type;
private:
    map<int, Vertice<Node_type,Edge_type>> Self;
};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
