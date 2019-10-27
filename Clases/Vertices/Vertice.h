#ifndef GRAPHS_GETGROUP_GETNAME_VERTICE_H
#define GRAPHS_GETGROUP_GETNAME_VERTICE_H
#include <vector>
using namespace std;
template<typename Node_type, typename Edge_type>

class Vertice {
    Node_type* self;
    vector<Edge_type*> Lista_de_adyacencia;
public:
    Node_type *getSelf() const {
        return self;
    }
    vector<Edge_type*>getLista() const {
        return Lista_de_adyacencia;
    }

    explicit Vertice(Node_type *self,vector<Edge_type*> Adyacencia) : self(self),Lista_de_adyacencia(Adyacencia) {}
    Vertice(){
        self=nullptr;
    };
};


#endif //GRAPHS_GETGROUP_GETNAME_VERTICE_H
