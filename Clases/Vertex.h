#ifndef GRAPHS_GETGROUP_GETNAME_VERTICE_H
#define GRAPHS_GETGROUP_GETNAME_VERTICE_H
#include <utility>
#include <vector>
#include "Edge.h"
using namespace std;
template<typename Node_type>
class Vertex {
public:
    Node_type* self;
    vector<Edge*> Lista_de_adyacencia;
public:
    Node_type *getSelf() const {
        return self;
    }
    vector<Edge*>getLista() const {
        return Lista_de_adyacencia;
    }

    unsigned long long int GetNumberOfEdgesVertex(){
        return Lista_de_adyacencia.size();
    }

    explicit Vertex(Node_type *self,vector<Edge*> Adyacencia) : self(self),Lista_de_adyacencia(std::move(Adyacencia)) {}
    explicit Vertex(Node_type *self) : self(self){}
    explicit Vertex(Node_type yy)  {
       self =new Node_type(yy);
    }
    Vertex(){
        self=nullptr;
    };

    ~Vertex(){
        delete self;
    }
};


#endif //GRAPHS_GETGROUP_GETNAME_VERTICE_H
