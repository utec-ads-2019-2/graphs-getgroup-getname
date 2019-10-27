#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include "Vertice.h"
#include <set>
#include <algorithm>
#include "Aristas/Arista_dirigida.h"
using namespace std;



template<typename Node_type>
class Grafo{
public:
    typedef typename Node_type::Edge_type Edge_type;


private:
    map<string,Vertice<Node_type>*> Self;
    void printEdge(const set<string>& parID){
        auto Itr = parID.begin();
        cout<<"{ "<<(*Itr)<<" , ";
        ++Itr;
        cout<<(*Itr)<<" } ";
    }


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
            if(typeid(Edge_type)!= typeid(Arista_dirigida))
                getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista);
        }
    }

    void Agregar_Arista(const string& ID_1,const string& ID_2){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto Self_1=Self[ID_1]->getSelf(); auto Self_2=Self[ID_2]->getSelf();

            auto arista=new Edge_type(ID_1,ID_2,Node_type::Calculate_weight(*Self_1,*Self_2));
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            if(typeid(Edge_type)!= typeid(Arista_dirigida))
                getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista);  }
    }


    bool Find_edge(string first_id, string  second_id){

    }

    bool Find_Vertex(string Id_vertex){
        return (Self.find(Id_vertex)!=Self.end());
    }



    void Prim(const string& verticeArbitrario){

        if(typeid(Edge_type)== typeid(Arista_dirigida))
            //throw runtime_error("Prim no puede ser aplicado en Grafos dirigidos");
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{
            auto it = Self.find(verticeArbitrario);
            if(it==Self.end()){
                cout<<"Vertice no encontrado"<<endl;
                return;
            }

            map<set<string>,double> aristasPosibles;
            auto pesoMim = aristasPosibles.end();
            set<string> verticesInMST;
            vector<Edge_type*> ListaAdy;
            auto setUnitario = new vector<string>(1);
            verticesInMST.insert((*it).first);
            while(Self.size() != verticesInMST.size()) {
                ListaAdy = (*it).second->Lista_de_adyacencia;

                for (int i = 0; i < ListaAdy.size(); ++i) {
                    aristasPosibles.emplace(ListaAdy[i]->getParId(), ListaAdy[i]->getWeight());
                }
                if(pesoMim != aristasPosibles.end()) aristasPosibles.erase(pesoMim);
                //First Edge
                do {
                    pesoMim = aristasPosibles.begin();
                    for (auto item = aristasPosibles.begin(); item != aristasPosibles.end(); ++item) {
                        if ((*item).second < (*pesoMim).second) pesoMim = item;
                    }

                    set_difference((*pesoMim).first.begin(), (*pesoMim).first.end(), verticesInMST.begin(),
                                   verticesInMST.end(), setUnitario->begin());
                    if(!(*setUnitario)[0].empty()) break;
                    else aristasPosibles.erase(pesoMim);
                }while(true);

                printEdge((*pesoMim).first);

                it = Self.find((*setUnitario)[0]);
                setUnitario->clear();
                delete setUnitario;
                setUnitario = new vector<string>(1);

                verticesInMST.insert((*pesoMim).first.begin(), (*pesoMim).first.end());
            }

            cout<<"exito"<<endl;


     }
    }
    void Prim(){

        if(typeid(Edge_type)== typeid(Arista_dirigida))
            //throw runtime_error("Prim no puede ser aplicado en Grafos dirigidos");
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{
            auto it = Self.begin();
            map<set<string>,double> aristasPosibles;
            auto pesoMim = aristasPosibles.end();
            set<string> verticesInMST;
            vector<Edge_type*> ListaAdy;
            auto setUnitario = new vector<string>(1);
            verticesInMST.insert((*it).first);
            while(Self.size() != verticesInMST.size()) {
                ListaAdy = (*it).second->Lista_de_adyacencia;

                for (int i = 0; i < ListaAdy.size(); ++i) {
                    aristasPosibles.emplace(ListaAdy[i]->getParId(), ListaAdy[i]->getWeight());
                }
                if(pesoMim != aristasPosibles.end()) aristasPosibles.erase(pesoMim);
                //First Edge
                do {
                    pesoMim = aristasPosibles.begin();
                    for (auto item = aristasPosibles.begin(); item != aristasPosibles.end(); ++item) {
                        if ((*item).second < (*pesoMim).second) pesoMim = item;
                    }

                    set_difference((*pesoMim).first.begin(), (*pesoMim).first.end(), verticesInMST.begin(),
                                   verticesInMST.end(), setUnitario->begin());
                    if(!(*setUnitario)[0].empty()) break;
                    else aristasPosibles.erase(pesoMim);
                }while(true);

                printEdge((*pesoMim).first);

                it = Self.find((*setUnitario)[0]);
                setUnitario->clear();
                delete setUnitario;
                setUnitario = new vector<string>(1);

                verticesInMST.insert((*pesoMim).first.begin(), (*pesoMim).first.end());
            }

            cout<<"exito"<<endl;


        }
    }




    void Kruskal(){
        if(typeid(Edge_type)== typeid(Arista_dirigida))
            //throw runtime_error("Kruskal no puede ser aplicado en Grafos dirigidos");
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{

        }
    }



};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
