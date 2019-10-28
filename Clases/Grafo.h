#ifndef GRAPHS_GETGROUP_GETNAME_GRAFO_H
#define GRAPHS_GETGROUP_GETNAME_GRAFO_H
#include <map>
#include "Vertice.h"
#include <set>
#include <algorithm>
#include "Arista.h"
#include "DisjoinSet.h"
using namespace std;



template<typename Node_type>
class Grafo{

private:
    map<string,Vertice<Node_type>*> Self;

    bool is_directed;

    void printEdge(const set<string>& parID){
        auto Itr = parID.begin();
        cout<<"{ "<<(*Itr)<<" , ";
        ++Itr;
        cout<<(*Itr)<<" } ";
    }

    bool setEmpty(vector<string>* setUnitario){
        return (*setUnitario)[0].empty();
    }
    void restartVector(vector<string>*& setUnitario,int n){
        setUnitario->clear();
        delete setUnitario;
        setUnitario = new vector<string>(n);
    }

    bool findEdge(const vector<Arista*>& allEdges, Arista* edge){
        for (auto & allEdge : allEdges) {
            if(*allEdge == (*edge)) return true;
        }
        return false;
    }

    bool compare_map(const pair<string,string>& pair1,const pair<string,string>& pair2){
        bool result;
        if(pair1.first== pair2.first and pair1.second==pair2.second)
            result=true;
        else result = pair1.first == pair2.second and pair1.second == pair2.first;
        return result;
    }

    void algorithmPrim(const string& verticeArbitrario){
        //throw runtime_error("Prim no puede ser aplicado en Grafos dirigidos");
        if(is_directed)
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
            vector<Arista*> ListaAdy;
            auto setUnitario = new vector<string>(1);
            verticesInMST.insert((*it).first);
            while(Self.size() != verticesInMST.size()) {
                ListaAdy = (*it).second->Lista_de_adyacencia;

                for (auto & i : ListaAdy) {
                    aristasPosibles.emplace(i->getParId(), i->getWeight());
                }
                if(pesoMim != aristasPosibles.end()) aristasPosibles.erase(pesoMim);
                do {
                    pesoMim = aristasPosibles.begin();
                    for (auto item = aristasPosibles.begin(); item != aristasPosibles.end(); ++item) {
                        if ((*item).second < (*pesoMim).second) pesoMim = item;
                    }

                    set_difference((*pesoMim).first.begin(), (*pesoMim).first.end(), verticesInMST.begin(),
                                   verticesInMST.end(), setUnitario->begin());
                    if(!setEmpty(setUnitario)) break;
                    else aristasPosibles.erase(pesoMim);
                }while(true);

                printEdge((*pesoMim).first);

                it = Self.find((*setUnitario)[0]);
                restartVector(setUnitario,1);

                verticesInMST.insert((*pesoMim).first.begin(), (*pesoMim).first.end());
            }

        }
    }

    void refillEdges(vector<Arista*>& allEdges){
        for(auto it= Self.begin(); it!=Self.end(); ++it){
            auto ListaAdy = (*it).second->Lista_de_adyacencia;
            for(auto itr = ListaAdy.begin(); itr!=ListaAdy.end(); ++itr) {
                if(!findEdge(allEdges,*itr)) allEdges.push_back(*itr);
            }
        }
    }

    multimap<double,Arista*> inOrderEdges(vector<Arista*>& allEdges){
        multimap<double,Arista*> inOrder;
        for(auto item : allEdges){
            inOrder.emplace(item->getWeight(),item);
        }

        return inOrder;
    }

public:
    explicit Grafo( map<string,Vertice<Node_type>*> self, bool is_directed) : Self(self),is_directed(is_directed) {
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
            auto arista=new Arista(ID_1,ID_2,weight);
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            if(!is_directed)
                getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista);
        }
    }

    void Agregar_Arista(const string& ID_1,const string& ID_2){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto Self_1=Self[ID_1]->getSelf(); auto Self_2=Self[ID_2]->getSelf();

            auto arista=new Arista(ID_1,ID_2,Node_type::Calculate_weight(*Self_1,*Self_2));
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            if(!is_directed)
                getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista);  }
    }

    bool Find_edge(string first_id, const string&  second_id){
        if( Self.find(first_id)==Self.end() or Self.find(second_id)==Self.end())
            return false;

        vector<Arista*> possibles_edges=Self[first_id]->getLista();
        for(auto i:possibles_edges){
            if(compare_map(i->getPair(),pair<string,string>(first_id,second_id)))
                return true;
        }
        return false;
    }

    bool Find_Vertex(string Id_vertex){
        return (Self.find(Id_vertex)!=Self.end());
    }

    void Prim(const string& verticeArbitrario){
        algorithmPrim(verticeArbitrario);
    }

    void Prim(){
        auto it = Self.begin();
        algorithmPrim((*it).first);
    }

    void Kruskal(){
        //throw runtime_error("Kruskal no puede ser aplicado en Grafos dirigidos");
        if(is_directed)
            cout<<"El algoritmo no puede ser aplicado en Grafos dirigidos\n";
        else{
            vector<Arista*> allEdges;
            refillEdges(allEdges);
            auto OrderEdges = inOrderEdges(allEdges);
            allEdges.clear();

            DisjointSet<string> ds;

            for(auto vertice : Self){
                ds.makeSet(vertice.first);
            }

            vector<Arista*> resultEdges;
            string parentA;
            string parentB;
            for(auto item : OrderEdges){
                parentA = ds.findSet(item.second->getPair().first);
                parentB = ds.findSet(item.second->getPair().second);

                if(parentA != parentB){
                    resultEdges.push_back(item.second);
                    ds.unionSet(item.second->getPair().first,item.second->getPair().second);
                }

                if(resultEdges.size() == Self.size()-1) break;
            }
            for (auto & resultEdge : resultEdges) {
                printEdge(resultEdge->getParId());
            }
        }
    }



};


#endif //GRAPHS_GETGROUP_GETNAME_GRAFO_H