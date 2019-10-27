#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include "Vertice.h"
#include "Aristas/Arista_dirigida.h"
using namespace std;



template<typename Node_type>
class Grafo{
public:
    typedef typename Node_type::Edge_type Edge_type;


private:
    map<string,Vertice<Node_type>*> Self;

public:
    explicit Grafo( map<string,Vertice<Node_type>*> self) : Self(self) {
    }

    map<string, Vertice<Node_type>*>&getSelf() {
        return Self;
    }

    void Prim(){
        if(typeid(Edge_type)== typeid(Arista_dirigida))
            throw runtime_error("El algoritmo no puede ser aplicado en Grafos dirigidos");
        else{

        }
    }


};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
