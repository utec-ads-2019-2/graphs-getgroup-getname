#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include <set>
#include <algorithm>
#include "Vertice.h"
using namespace std;



template<typename Node_type>
class Grafo{
public:
    typedef typename Node_type::Edge_type Edge_type;


private:
    map<string,Vertice<Node_type>> Self;

public:
    explicit Grafo( map<string,Vertice<Node_type>> self) : Self(self) {}

    map<string, Vertice<Node_type>>&getSelf() {
        return Self;
    }
    void printEdge(set<string> parID){
        auto Itr = parID.begin();
        cout<<"{ "<<(*Itr)<<" , ";
        ++Itr;
        cout<<(*Itr)<<" } ";
    }

    bool setEmpty(vector<string>* setUnitario){
        return (*setUnitario)[0].empty();
    }

    void restartVector(vector<string>*& setUnitario){
        setUnitario->clear();
        delete setUnitario;
        setUnitario = new vector<string>(1);
    }


    void Prim(){
        string verticeArbitrario;

        cout << "Insertar Vertice arbitrario: ";
        cin >> verticeArbitrario;

        auto it = Self.find(verticeArbitrario);

        if (it != Self.end()){
            map<set<string>,double> aristasPosibles;
            auto pesoMim = aristasPosibles.end();

            set<string> verticesInMST;
            verticesInMST.insert((*it).first);
            vector<string>* setUnitario = new vector<string>(1);

            vector<Edge_type*> ListaAdy;

            while(Self.size() != verticesInMST.size()) {
                ListaAdy = (*it).second.Lista_de_adyacencia;

                for (int i = 0; i < ListaAdy.size(); ++i) {
                    aristasPosibles.emplace(ListaAdy[i]->getParId(), ListaAdy[i]->getWeight());
                }
                if(pesoMim != aristasPosibles.end()) aristasPosibles.erase(pesoMim);

                do {
                    pesoMim = aristasPosibles.begin();
                    for (auto item = aristasPosibles.begin(); item != aristasPosibles.end(); ++item) {
                        if ((*item).second < (*pesoMim).second) pesoMim = item;
                    }

                     set_difference((*pesoMim).first.begin(), (*pesoMim).first.end(),
                             verticesInMST.begin(),verticesInMST.end(), setUnitario->begin());
                    if(!setEmpty(setUnitario)) break;
                    else aristasPosibles.erase(pesoMim);
                }while(true);

                printEdge((*pesoMim).first);

                it = Self.find((*setUnitario)[0]);

                restartVector(setUnitario);

                verticesInMST.insert((*pesoMim).first.begin(), (*pesoMim).first.end());
                }

            }
        else
            cout<<"Vertice no encontrado"<<endl;

    }
};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H
