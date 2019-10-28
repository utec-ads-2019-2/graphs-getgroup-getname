#ifndef GRAPHS_GETGROUP_GETNAME_VERTICE_H
#define GRAPHS_GETGROUP_GETNAME_VERTICE_H
#include <utility>
#include <vector>
#include "Arista.h"
using namespace std;
template<typename Node_type>

class Vertice {
public:
    Node_type* self;
    vector<Arista*> Lista_de_adyacencia;
public:
    Node_type *getSelf() const {
        return self;
    }
    vector<Arista*>getLista() const {
        return Lista_de_adyacencia;
    }

    explicit Vertice(Node_type *self,vector<Arista*> Adyacencia) : self(self),Lista_de_adyacencia(std::move(Adyacencia)) {}
    explicit Vertice(Node_type *self) : self(self){}
    explicit Vertice(Node_type self)  {
        Node_type* ptr=&self; this->self=ptr;
    }
    Vertice(){
        self=nullptr;
    };
};


#endif //GRAPHS_GETGROUP_GETNAME_VERTICE_H
