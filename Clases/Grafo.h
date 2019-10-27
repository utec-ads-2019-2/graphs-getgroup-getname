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

    void Agregar_Vertice(const string& ID,Node_type Nodo){
        auto vertice1= new Vertice<Node_type>(Nodo);
        Self[ID]= vertice1;
    }

    void Agregar_Arista(const string& ID_1,const string& ID_2, double weight){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto arista=new Edge_type(ID_1,ID_2,weight);
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista); }
    }

    void Agregar_Arista(const string& ID_1,const string& ID_2){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto Self_1=Self[ID_1]->getSelf(); auto Self_2=Self[ID_2]->getSelf();

            auto arista=new Edge_type(ID_1,ID_2,Node_type::Calculate_weight(*Self_1,*Self_2));
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista); }
    }





    void Prim(){
        if(typeid(Edge_type)== typeid(Arista_dirigida))
            //throw runtime_error("Prim no puede ser aplicado en Grafos dirigidos");
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{

        }
    }

    void Krukal(){
        if(typeid(Edge_type)== typeid(Arista_dirigida))
            //throw runtime_error("Kruskal no puede ser aplicado en Grafos dirigidos");
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{

        }
    }



};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
