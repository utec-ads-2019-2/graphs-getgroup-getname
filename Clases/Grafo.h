#ifndef GRAPHS_GETGROUP_GETNAME_Graph_H
#define GRAPHS_GETGROUP_GETNAME_Graph_H
#include <map>
#include <queue>
#include "Vertice.h"
#include <set>
#include <algorithm>
#include "Arista.h"
#include "DisjoinSet.h"
#include <cfloat>
#include <algorithm>
using namespace std;



template<typename Node_type>
class Graph{

private:

    typedef pair<Arista,double> my_pair;

    map<string,Vertice<Node_type>*> Self;

    bool IsDirected;

    void PrintEdge(const set<string>& parID){
        auto Itr = parID.begin();
        cout<<"{ "<<(*Itr)<<" , ";
        ++Itr;
        cout<<(*Itr)<<" } ";
    }

    bool SetEmpty(vector<string>* setUnitario){
        return (*setUnitario)[0].empty();
    }

    void RestartVector(vector<string>*& setUnitario,int n){
        setUnitario->clear();
        delete setUnitario;
        setUnitario = new vector<string>(n);
    }

    bool findEdgeInternal(const vector<Arista*>& allEdges, Arista* edge){
        for (auto & allEdge : allEdges) {
            if(*allEdge == (*edge)) return true;
        }
        return false;
    }

    bool CompareMap(const pair<string,string>& pair1,const pair<string,string>& pair2){
        bool result;
        if(pair1.first== pair2.first and pair1.second==pair2.second)
            return true;
        else
            return pair1.first == pair2.second and pair1.second == pair2.first;
    }

    vector<Arista*> AlgorithmPrim(const string& verticeArbitrario){
        //throw runtime_error("Prim no puede ser aplicado en grafos dirigidos");
        vector<Arista*> resultEdges;

        if(!IsConnected()){
            cout<<"El algoritmo no puede ser aplicado en grafos no conexos\n";
            return resultEdges;
        }

        if(IsDirected){
            cout<<"El algoritmo no puede ser aplicado en grafos dirigidos\n";
        }

        else{
            auto it = Self.find(verticeArbitrario);
            if(it==Self.end()){
                cout<<"Vertice no encontrado"<<endl;
            }
            else{
                multimap<double,Arista*> aristasPosibles;

                set<string> verticesInMST;
                verticesInMST.insert((*it).first); //Vertice Arbitrario

                set<string> verticesEgde; //Vertices de la arista

                auto setUnitario = new vector<string>(1);


                while(Self.size() != verticesInMST.size()) {

                    for (auto& item: (*it).second->Lista_de_adyacencia) {

                        if(!findEdgeInternal(resultEdges,item)) aristasPosibles.emplace(item->getWeight(),item);
                    }

                    do {
                        verticesEgde = (*aristasPosibles.begin()).second->getParId();

                        set_difference(verticesEgde.begin(), verticesEgde.end(), verticesInMST.begin(),
                                       verticesInMST.end(), setUnitario->begin());

                        if(!SetEmpty(setUnitario)) break;
                        else aristasPosibles.erase(aristasPosibles.begin());

                    }while(true);

                    it = Self.find((*setUnitario)[0]);
                    RestartVector(setUnitario,1);

                    resultEdges.push_back((*aristasPosibles.begin()).second);
                    verticesInMST.insert(verticesEgde.begin(),verticesEgde.end());

                    aristasPosibles.erase(aristasPosibles.begin());
                }
            }
            return resultEdges;
        }
        return resultEdges;
    }

    Graph* GetNoDirecGraph() {
        if (!IsDirected) return this;
        map<string,Vertice<Node_type>*> Map_for_graph;

        for (auto vertex : Self){
            Map_for_graph[vertex.first] = new Vertice<Node_type>(Vertice<Node_type>(*vertex.second->getSelf()));
        }

        for (auto vertex : Self) {
            for (auto edge : vertex.second->Lista_de_adyacencia) {
                Map_for_graph[edge->getIdEnd()]->Lista_de_adyacencia.push_back(edge);
                Map_for_graph[edge->getIdBegin()]->Lista_de_adyacencia.push_back(edge);
            }
        }
        return new Graph(Map_for_graph,false);
    }

    void RefillEdges(vector<Arista*>& allEdges){
        for(auto it= Self.begin(); it!=Self.end(); ++it){
            auto ListaAdy = (*it).second->Lista_de_adyacencia;
            for(auto itr = ListaAdy.begin(); itr!=ListaAdy.end(); ++itr) {
                if(!findEdgeInternal(allEdges,*itr)) allEdges.push_back(*itr);
            }
        }
    }

    multimap<double,Arista*> InOrderEdges(vector<Arista*>& allEdges){
        multimap<double,Arista*> inOrder;
        for(auto item : allEdges){
            inOrder.emplace(item->getWeight(),item);
        }
        return inOrder;
    }

    Arista* FindedEdge(string id_1,const string& id_2){
        vector<Arista*> possibles_edges=Self[id_1]->getLista();
        for(auto i:possibles_edges){
            if(CompareMap(i->getPair(),pair<string,string>(id_1,id_2)))
                return i;
        }
        return nullptr;
    }

    bool RemoveEdgeLogic(const string& Id_1,const string& Id_2, bool want_to_check){
        if(want_to_check and !FindEdge(Id_1,Id_2))
            return false;
        else{
            Arista* Edge_to_remove=FindedEdge(Id_1,Id_2);
            long i=0;

            while(i<Self[Id_1]->getLista().size() and Self[Id_1]->getLista()[i]!=Edge_to_remove)
                i++;

            Self[Id_1]->Lista_de_adyacencia.erase(Self[Id_1]->Lista_de_adyacencia.begin()+i);

            if(!IsDirected){
                i=0;
                while(i<Self[Id_2]->getLista().size() and Self[Id_2]->getLista()[i]!=Edge_to_remove)
                    i++;

                Self[Id_2]->Lista_de_adyacencia.erase(Self[Id_2]->Lista_de_adyacencia.begin()+i);
            }

            delete Edge_to_remove;
            return true;
        }
    }

    void ClearVertexes(){
        for(auto i:Self)
            delete i.second;
        Self.clear();
    }

    void ClearEdges() {
        for(auto i:Self)
            for(Arista* arista: i.second->getLista())
                RemoveEdge(arista->getIdBegin(), arista->getIdEnd());
    }

    void DFSUtil(const string& v, map<string,bool> & visited) {
        visited[v] = true;
        vector<Arista*> ListaAdy = Self[v]->Lista_de_adyacencia;

        for (auto i : ListaAdy) {
            string visit = (i->getIdEnd() == v) ?
                           i->getIdBegin() : i->getIdEnd();
            if (!visited[visit]) {
                DFSUtil(visit, visited);
            }
        }
    }

    Graph* getTranspose() {
        map<string,Vertice<Node_type>*> Map_for_graph;

        for (auto vertex : Self)
            Map_for_graph[vertex.first] = new Vertice<Node_type>(Vertice<Node_type>(*vertex.second->getSelf()));

        for (auto vertex : Self)
            for (auto edge : vertex.second->Lista_de_adyacencia)
                Map_for_graph[edge->getIdEnd()]->Lista_de_adyacencia.push_back(edge);

        return new Graph (Map_for_graph,true);
    }

public:
    explicit Graph( map<string,Vertice<Node_type>*> self, bool IsDirected) : Self(self),IsDirected(IsDirected) {}
    explicit Graph(bool IsDirected): IsDirected(IsDirected){}

    map<string, Vertice<Node_type>*>&getSelf() {
        return Self;
    }

    void AddVertex(const string& ID,Node_type Nodo){
        auto vertice1= new Vertice<Node_type>(Nodo);
        Self[ID]= vertice1;
    }

    void AddEdge(const string& ID_1,const string& ID_2, double weight){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto arista=new Arista(ID_1,ID_2,weight);
            getSelf()[ID_1]->Lista_de_adyacencia.push_back(arista);
            if(!IsDirected)
                getSelf()[ID_2]->Lista_de_adyacencia.push_back(arista);
        }
    }

    void AddEdge(const string& ID_1,const string& ID_2){
        if(FindVertex(ID_1) and FindVertex(ID_2))
            AddEdge(ID_1,ID_2,Node_type::Calculate_weight(*Self[ID_1]->getSelf(),*Self[ID_2]->getSelf()));
    }

    bool FindEdge(string first_id, const string&  second_id){
        if( Self.find(first_id)==Self.end() or Self.find(second_id)==Self.end())
            return false;

        vector<Arista*> possibles_edges=Self[first_id]->getLista();
        for(auto i:possibles_edges){
            if(CompareMap(i->getPair(),pair<string,string>(first_id,second_id)))
                return true;
        }
        return false;
    }

    bool FindVertex(string Id_vertex){
        return (Self.find(Id_vertex)!=Self.end());
    }

    vector<Arista*> Prim(const string& verticeArbitrario){
        return AlgorithmPrim(verticeArbitrario);
    }
    vector<Arista*> Prim(){
        auto it = Self.begin();
        return AlgorithmPrim((*it).first);
    }
    vector<Arista*> Kruskal(){
        //throw runtime_error("Kruskal no puede ser aplicado en grafos dirigidos");
        vector<Arista*> resultEdges;
        if(IsDirected){
            cout<<"El algoritmo no puede ser aplicado en grafos dirigidos\n";
        }

        else{
            vector<Arista*> allEdges;
            RefillEdges(allEdges);
            auto OrderEdges = InOrderEdges(allEdges);
            allEdges.clear();

            DisjointSet<string> ds;

            for(auto vertice : Self){
                ds.makeSet(vertice.first);
            }

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
        }
        return resultEdges;
    }
    
    void PrintKruskal(){
        auto resultEdges = Kruskal();
        for(auto& item: resultEdges){
            PrintEdge(item->getParId());
        }
        cout<<endl;
    }
    void PrintPrim(string verticeArbitrario){
        auto resultEdges = Prim(verticeArbitrario);
        for (auto & item : resultEdges) {
            PrintEdge(item->getParId());
        }
        cout<<endl;
    }
    void PrintPrim(){
        auto resultEdges = Prim();
        for (auto & item : resultEdges) {
            PrintEdge(item->getParId());
        }
        cout<<endl;
    }


    float GetDensity(){
        int numero_de_vertices=Self.size();

        if(numero_de_vertices<=1)
            return 0;

        vector<Arista*> no_rep_edges;
        for(auto it=Self.begin();it!=Self.end();it++){
            auto ListaAdy = (*it).second->Lista_de_adyacencia;
            for(auto itr = ListaAdy.begin(); itr!=ListaAdy.end(); ++itr) {
                if(find(no_rep_edges.begin(),no_rep_edges.end(),*itr)==no_rep_edges.end())
                    no_rep_edges.push_back(*itr);
            }
        }
        float density=float(no_rep_edges.size())/
                   float((numero_de_vertices*(numero_de_vertices-1)));
        if(!IsDirected)
            density*=2;

        return density;
    }

    bool IsDense(float Cota){
        return (GetDensity()>=Cota);
    }

    bool RemoveEdge(const string& Id_1,const string& Id_2){
        return RemoveEdgeLogic(Id_1,Id_2, true);
    }

    bool RemoveVertex(string ID){
        if(!FindVertex(ID)){
            return false;
        }
        else{
            while(!Self[ID]->Lista_de_adyacencia.empty()){
                if(ID==Self[ID]->Lista_de_adyacencia[0]->getIdBegin())
                    RemoveEdgeLogic(ID,Self[ID]->Lista_de_adyacencia[0]->getIdEnd(), true);
                else
                    RemoveEdgeLogic(ID,Self[ID]->Lista_de_adyacencia[0]->getIdBegin(),true);
            }

            delete Self[ID];
            Self.erase(Self.find(ID));

            if(IsDirected){
                for(auto i:Self){
                    vector<Arista*> possibles_edges=i.second->Lista_de_adyacencia;
                    for(Arista* arista: possibles_edges){
                        if(arista->getIdEnd()==ID)
                            RemoveEdgeLogic(arista->getIdBegin(),ID, false);
                    }
                }
            }
            return true;
        }
    }

    bool IsConnected() {
        if (IsDirected) {
            auto no_directed = GetNoDirecGraph();
            bool conexo = no_directed->IsConnected();
            return conexo;
        }
        else {
            map<string,bool> visited;
            for (auto v : Self)
                visited[v.first] = false;

            DFSUtil(visited.begin()->first,visited);
            for (const auto& v : visited)
                if (!visited.at(v.first))
                    return false;
            return true;
        }
    }

    bool IsStrongConnected() {
        bool connected = this->IsConnected();

        if (IsDirected && connected) {
            map<string,bool> visited;
            auto gr = this->getTranspose();
            for(auto v : gr->getSelf())
                visited[v.first] = false;
            gr->DFSUtil(visited.begin()->first,visited);
            for (const auto& v : visited)
                if (!visited.at(v.first)){
                    return false;
                }
        }
        return connected;
    }

    bool IsBipartite() {
        map<string,int> colored;
        for (auto node : Self)
            colored[node.first] = -1;

        colored[colored.begin()->first] = 1;
        queue <string> cola;
        cola.push(colored.begin()->first);

        while (!cola.empty()) {
            string U = cola.front();
            cola.pop();

            for (auto edge : Self[U]->Lista_de_adyacencia) {
                string visit = (edge->getIdEnd() == U) ?
                               edge->getIdBegin() : edge->getIdEnd();
                if(colored[visit] == -1) {
                    colored[visit] = 1 - colored[U];
                    cola.push(visit);
                } else
                if (colored[visit] == colored[U])
                    return false;
            }
        }
        return true;
    }

    unsigned int GetNumberOfEdgesGraph(){
        unsigned int num=0;
        for(auto i : Self){
            num+=i.second->GetNumberOfEdgesVertex();
        }
        if(!IsDirected) num/=2;

        return num;
    }

    bool getIsDirected(){
        return IsDirected;
    }

    unsigned long long int getNumVertex(){
        return Self.size();
    }

    void addQueuePriority(vector<my_pair>& qp, string IDbegin, string IDend, double weight, double dist){
        for ( auto& item : qp) {
            if(IDend == item.first.getIdEnd()){
                item.first = Arista(IDbegin,IDend,weight);
                item.second = dist;
                return;
            }
        }
        qp.emplace_back(Arista(IDbegin,IDend,weight),dist);
    }

    void refillqp(string IDvertex, vector<my_pair>& qp, map<string,double>& verticesDistancias){
        auto listaAdy = Self[IDvertex]->getLista();
        string IDvertexAdy;

        auto cmpPair =[](const my_pair& A,const my_pair& B){ return A.second < B.second; };

        for(int i = 0; i < listaAdy.size(); ++i){
            IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);
            verticesDistancias[IDvertexAdy] = verticesDistancias[IDvertex] + listaAdy[i]->getWeight();
            qp.emplace_back(Arista(IDvertex,IDvertexAdy,listaAdy[i]->getWeight()),verticesDistancias[IDvertexAdy]);
        }
        sort(qp.begin(),qp.end(),cmpPair);
    }

    string nextVertex(Graph<Node_type>& grafo, Arista& e){
        if(!grafo.FindVertex(e.getIdBegin())) return e.getIdBegin();
        return e.getIdEnd();
    }

    Graph Dijkstra(string startVertex){
        Graph<Node_type> arbolMinimosRecorridos(this->getIsDirected());

        if(!IsConnected()) cout <<"No es posible aplicarlo en grafos no conexos"<<endl;
        else {
            arbolMinimosRecorridos.AddVertex(startVertex,*(Self[startVertex]->getSelf()));
            auto cmpPair =[](const my_pair& A,const my_pair& B){ return A.second < B.second; };

            string IDvertex;
            string IDvertexAdy;

            vector<my_pair> queuePriority;
            map<string, bool> verticesVisitados;
            map<string, double> verticesDistancias;

            for (auto it = Self.cbegin(); it != Self.cend(); ++it) {
                verticesDistancias.emplace(it->first, DBL_MAX);
                verticesVisitados.emplace(it->first,false);
            }
            verticesDistancias[startVertex] = 0;

            verticesVisitados[startVertex] = true;
            refillqp(startVertex,queuePriority,verticesDistancias);

            while(arbolMinimosRecorridos.getNumVertex() != this->getNumVertex()){

                IDvertex = nextVertex(arbolMinimosRecorridos,queuePriority.begin()->first);

                arbolMinimosRecorridos.AddVertex(IDvertex,*(Self[IDvertex]->getSelf()));
                arbolMinimosRecorridos.AddEdge(queuePriority.begin()->first.getIdBegin(),queuePriority.begin()->first.getIdEnd(),queuePriority.begin()->first.getWeight());
                //PrintEdge(queuePriority.begin()->first.getParId()); OPCIONAL

                queuePriority.erase(queuePriority.begin());

                verticesVisitados[IDvertex] = true;
                auto listaAdy = Self[IDvertex]->getLista();

                for(int i = 0; i < listaAdy.size(); ++i){
                    IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);

                    if(!verticesVisitados[IDvertexAdy]){
                        if (verticesDistancias[IDvertexAdy] > verticesDistancias[IDvertex] + listaAdy[i]->getWeight()){
                            verticesDistancias[IDvertexAdy] = verticesDistancias[IDvertex] + listaAdy[i]->getWeight();
                            addQueuePriority(queuePriority,IDvertex, IDvertexAdy, listaAdy[i]->getWeight(),verticesDistancias[IDvertexAdy]);
                        }
                    }
                }
                sort(queuePriority.begin(),queuePriority.end(),cmpPair);
            }
        }
        return arbolMinimosRecorridos;
    }

    ~Graph(){
        ClearEdges();
        ClearVertexes();
    }
};

#endif //GRAPHS_GETGROUP_GETNAME_Graph_H