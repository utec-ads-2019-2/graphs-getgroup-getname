#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include "../Vertices/Vertice.h"
using namespace std;



template<typename Node_type>
class Grafo{
public:
    typedef typename Node_type::Edge_type Edge_type;


private:
    map<int,Vertice<Node_type,Edge_type>> Self;
public:
    explicit Grafo( map<int,Vertice<Node_type,Edge_type>>self) : Self(self) {}
};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
