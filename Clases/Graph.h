#ifndef GRAPHS_GETGROUP_GETNAME_Graph_H
#define GRAPHS_GETGROUP_GETNAME_Graph_H
#include <map>
#include <queue>
#include "Vertex.h"
#include <set>
#include <algorithm>
//#include "Algorithm_Astart.h"
#include "Edge.h"
#include "DisjoinSet.h"
#include <cfloat>
#include <stack>
#include <queue>
#include <unordered_map>

#define MAX 2.14748e+09
using namespace std;

template<typename Node_type>
class Graph{
private:

    typedef pair<Edge,double> my_pair;

    map<string,Vertex<Node_type>*> Self;

    bool IsDirected;

    void PrintEdge(const pair<string,string>& parID){
        cout<<"{ "<<parID.first<<" , "<<parID.second<<" } ";
    }

    bool SetEmpty(vector<string>* setUnitario){
        return (*setUnitario)[0].empty();
    }

    void RestartVector(vector<string>*& setUnitario,int n){
        setUnitario->clear();
        delete setUnitario;
        setUnitario = new vector<string>(n);
    }

    bool findEdgeInternal(const vector<Edge*>& allEdges, Edge* edge){
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

    vector<Edge*> AlgorithmPrim(const string& verticeArbitrario){
        //throw runtime_error("Prim no puede ser aplicado en grafos dirigidos");
        vector<Edge*> resultEdges;

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
                cout<<"Vertex no encontrado"<<endl;
            }
            else{
                multimap<double,Edge*> aristasPosibles;

                set<string> verticesInMST;
                verticesInMST.insert((*it).first); //Vertex Arbitrario

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
        map<string,Vertex<Node_type>*> Map_for_graph;

        for (auto vertex : Self){
            Map_for_graph[vertex.first] = new Vertex<Node_type>(Vertex<Node_type>(*vertex.second->getSelf()));
        }

        for (auto vertex : Self) {
            for (auto edge : vertex.second->Lista_de_adyacencia) {
                Map_for_graph[edge->getIdEnd()]->Lista_de_adyacencia.push_back(edge);
                Map_for_graph[edge->getIdBegin()]->Lista_de_adyacencia.push_back(edge);
            }
        }
        return new Graph(Map_for_graph,false);
    }

    void RefillEdges(vector<Edge*>& allEdges){
        for(auto it= Self.begin(); it!=Self.end(); ++it){
            auto ListaAdy = (*it).second->Lista_de_adyacencia;
            for(auto itr = ListaAdy.begin(); itr!=ListaAdy.end(); ++itr) {
                if(!findEdgeInternal(allEdges,*itr)) allEdges.push_back(*itr);
            }
        }
    }

    multimap<double,Edge*> InOrderEdges(vector<Edge*>& allEdges){
        multimap<double,Edge*> inOrder;
        for(auto item : allEdges){
            inOrder.emplace(item->getWeight(),item);
        }
        return inOrder;
    }

    Edge* FindedEdge(string id_1,const string& id_2){
        vector<Edge*> possibles_edges=Self[id_1]->getLista();
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
            Edge* Edge_to_remove=FindedEdge(Id_1,Id_2);
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
            for(Edge* arista: i.second->getLista())
                RemoveEdge(arista->getIdBegin(), arista->getIdEnd());
    }

    void DFSUtil(const string& v, map<string,bool> & visited) {
        visited[v] = true;
        vector<Edge*> ListaAdy = Self[v]->Lista_de_adyacencia;

        for (auto i : ListaAdy) {
            string visit = (i->getIdEnd() == v) ?
                           i->getIdBegin() : i->getIdEnd();
            if (!visited[visit]) {
                DFSUtil(visit, visited);
            }
        }
    }

    Graph* getTranspose() {
        map<string,Vertex<Node_type>*> Map_for_graph;

        for (auto vertex : Self)
            Map_for_graph[vertex.first] = new Vertex<Node_type>(Vertex<Node_type>(*vertex.second->getSelf()));

        for (auto vertex : Self)
            for (auto edge : vertex.second->Lista_de_adyacencia)
                Map_for_graph[edge->getIdEnd()]->Lista_de_adyacencia.push_back(edge);

        return new Graph (Map_for_graph,true);
    }

public:
    explicit Graph( map<string,Vertex<Node_type>*> self, bool IsDirected) : Self(self),IsDirected(IsDirected) {}
    explicit Graph(bool IsDirected): IsDirected(IsDirected){}


    map<string, Vertex<Node_type>*>&getSelf() {
        return Self;
    }

    double Distance(string A, string B){
        if (A == B) return 0;
        for (auto e : Self[A]->Lista_de_adyacencia) {
            if (e->getIdEnd() == B) return e->getWeight();
        }
        return INT32_MAX;
    }

    void AddVertex(const string& ID,Node_type Nodo){
        auto vertice1= new Vertex<Node_type>(Nodo);
        Self[ID]= vertice1;
    }

    void AddEdge(const string& ID_1,const string& ID_2, double weight){
        if( Self.find(ID_1)==Self.end() or Self.find(ID_2)==Self.end()){
            cout<<"No se pudo insertar la arista, revise los vértices\n";
        }
        else{
            auto arista=new Edge(ID_1,ID_2,weight);
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

        vector<Edge*> possibles_edges=Self[first_id]->getLista();
        for(auto i:possibles_edges){
            if(CompareMap(i->getPair(),pair<string,string>(first_id,second_id)))
                return true;
        }
        return false;
    }

    bool FindVertex(string Id_vertex){
        return (Self.find(Id_vertex)!=Self.end());
    }

    vector<Edge*> Prim(const string& verticeArbitrario){
        return AlgorithmPrim(verticeArbitrario);
    }
    vector<Edge*> Prim(){
        auto it = Self.begin();
        return AlgorithmPrim((*it).first);
    }
    vector<Edge*> Kruskal(){
        //throw runtime_error("Kruskal no puede ser aplicado en grafos dirigidos");
        vector<Edge*> resultEdges;
        if(IsDirected){
            cout<<"El algoritmo no puede ser aplicado en grafos dirigidos\n";
        }

        else{
            vector<Edge*> allEdges;
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
            PrintEdge(item->getPair());
        }
        cout<<endl;
    }
    void PrintPrim(string verticeArbitrario){
        auto resultEdges = Prim(verticeArbitrario);
        for (auto & item : resultEdges) {
            PrintEdge(item->getPair());
        }
        cout<<endl;
    }
    void PrintPrim(){
        auto resultEdges = Prim();
        for (auto & item : resultEdges) {
            PrintEdge(item->getPair());
        }
        cout<<endl;
    }

    float GetDensity(){
        int numero_de_vertices=Self.size();

        if(numero_de_vertices<=1)
            return 0;

        vector<Edge*> no_rep_edges;
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
                    vector<Edge*> possibles_edges=i.second->Lista_de_adyacencia;
                    for(Edge* arista: possibles_edges){
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

    bool GetIsDirected(){
        return IsDirected;
    }

    unsigned long long int getNumVertex(){
        return Self.size();
    }

    void addQueueDijkstra(vector<my_pair>& qp, string IDbegin, string IDend, double weight, double dist){
        for ( auto& item : qp) {
            if(IDend == item.first.getIdEnd()){
                item.first = Edge(IDbegin,IDend,weight);
                item.second = dist;
                return;
            }
        }
        qp.emplace_back(Edge(IDbegin,IDend,weight),dist);
    }

    string nextVertex(Graph<Node_type>& grafo, Edge& e){
        if(!grafo.FindVertex(e.getIdBegin())) return e.getIdBegin();
        return e.getIdEnd();
    }

/*
    Graph Dijkstra(string startVertex){
        Graph<Node_type> arbolMinimosRecorridos(this->GetIsDirected());

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

            IDvertex = startVertex;

            while(arbolMinimosRecorridos.getNumVertex() != this->getNumVertex()){

                verticesVisitados[IDvertex] = true;
                auto listaAdy = Self[IDvertex]->getLista();

                for(int i = 0; i < listaAdy.size(); ++i){
                    IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);

                    if(!verticesVisitados[IDvertexAdy]){
                        if (verticesDistancias[IDvertexAdy] > verticesDistancias[IDvertex] + listaAdy[i]->getWeight()){
                            verticesDistancias[IDvertexAdy] = verticesDistancias[IDvertex] + listaAdy[i]->getWeight();
                            addQueueDijkstra(queuePriority,IDvertex, IDvertexAdy, listaAdy[i]->getWeight(),verticesDistancias[IDvertexAdy]);
                        }
                    }

                }
                sort(queuePriority.begin(),queuePriority.end(),cmpPair);

                IDvertex = nextVertex(arbolMinimosRecorridos,queuePriority.begin()->first);

                arbolMinimosRecorridos.AddVertex(IDvertex,*(Self[IDvertex]->getSelf()));
                arbolMinimosRecorridos.AddEdge(queuePriority.begin()->first.getIdBegin(),queuePriority.begin()->first.getIdEnd(),queuePriority.begin()->first.getWeight());
                PrintEdge(queuePriority.begin()->first.getPair()); //OPCIONAL

                queuePriority.erase(queuePriority.begin());
            }
        }
        return arbolMinimosRecorridos;
    }
*/
    bool findIDvector(const vector<string>& allEdges, string ID){
        for (auto & item : allEdges) {
            if(item == ID) return true;
        }
        return false;
    }

    string nextVertex(vector<string> vertex, Edge& e){
        if(findIDvector(vertex,e.getIdBegin())) return e.getIdEnd();
        return e.getIdEnd();
    }

    Graph DijkstraGraph(string startVertex){
        Graph<Node_type> arbolMinimosRecorridos(this->GetIsDirected());

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

            IDvertex = startVertex;

            while(arbolMinimosRecorridos.getNumVertex() != this->getNumVertex()){

                verticesVisitados[IDvertex] = true;
                auto listaAdy = Self[IDvertex]->getLista();

                for(int i = 0; i < listaAdy.size(); ++i){
                    IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);

                    if(!verticesVisitados[IDvertexAdy]){
                        if (verticesDistancias[IDvertexAdy] > verticesDistancias[IDvertex] + listaAdy[i]->getWeight()){
                            verticesDistancias[IDvertexAdy] = verticesDistancias[IDvertex] + listaAdy[i]->getWeight();
                            addQueueDijkstra(queuePriority,IDvertex, IDvertexAdy, listaAdy[i]->getWeight(),verticesDistancias[IDvertexAdy]);
                        }
                    }

                }
                sort(queuePriority.begin(),queuePriority.end(),cmpPair);

                IDvertex = nextVertex(arbolMinimosRecorridos,queuePriority.begin()->first);

                arbolMinimosRecorridos.AddVertex(IDvertex,*(Self[IDvertex]->getSelf()));
                arbolMinimosRecorridos.AddEdge(queuePriority.begin()->first.getIdBegin(),queuePriority.begin()->first.getIdEnd(),queuePriority.begin()->first.getWeight());
                PrintEdge(queuePriority.begin()->first.getPair()); //OPCIONAL

                queuePriority.erase(queuePriority.begin());
            }
        }
        return arbolMinimosRecorridos;
    }

    vector<vector<string>> DijkstraPaths(string startVertex){
        map<string,string> parent;

        if(!IsConnected()) cout <<"No es posible aplicarlo en grafos no conexos"<<endl;

        else {
            auto cmpPair =[](const my_pair& A,const my_pair& B){ return A.second < B.second; };

            string IDvertex;
            string IDvertexAdy;
            vector<string> vertexs;
            vector<my_pair> queuePriority;
            map<string, bool> verticesVisitados;
            map<string, double> verticesDistancias;

            for (auto it = Self.cbegin(); it != Self.cend(); ++it) {
                verticesDistancias.emplace(it->first, DBL_MAX);
                verticesVisitados.emplace(it->first,false);
                //parent[]
            }
            verticesDistancias[startVertex] = 0;
            parent[startVertex] = startVertex;
            vertexs.push_back(startVertex);

            IDvertex = startVertex;

            while(vertexs.size() != Self.size()){

                verticesVisitados[IDvertex] = true;
                auto listaAdy = Self[IDvertex]->getLista();

                for(int i = 0; i < listaAdy.size(); ++i){
                    IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);

                    if(!verticesVisitados[IDvertexAdy]){
                        if (verticesDistancias[IDvertexAdy] > verticesDistancias[IDvertex] + listaAdy[i]->getWeight()){
                            parent[IDvertexAdy] = IDvertex;
                            verticesDistancias[IDvertexAdy] = verticesDistancias[IDvertex] + listaAdy[i]->getWeight();
                            addQueueDijkstra(queuePriority,IDvertex, IDvertexAdy, listaAdy[i]->getWeight(),verticesDistancias[IDvertexAdy]);
                        }
                    }

                }
                sort(queuePriority.begin(),queuePriority.end(),cmpPair);

                IDvertex = nextVertex(vertexs,queuePriority.begin()->first);
                vertexs.insert(vertexs.begin(),IDvertex);

                //PrintEdge(queuePriority.begin()->first.getPair()); //OPCIONAL

                queuePriority.erase(queuePriority.begin());
            }
        }

        vector<vector<string>> Paths;
        string ID;
        for (auto vertex  = Self.cbegin(); vertex != Self.cend(); vertex++) {
            ID = vertex->first;
            vector<string> path; path.push_back(ID);
            while(startVertex != parent[ID]){
                path.insert(path.begin()+1,parent[ID]);
                ID = parent[ID];
            }
            Paths.push_back(path);
        }

        return Paths;
    }


    void PrintDijkstraPaths(string startVertex){
        auto Paths = DijkstraPaths(startVertex);
        for (int i = 0; i < Paths.size(); ++i) {
            cout<<"Camino "<< startVertex<<" "<< Paths[i][0]<<": ";
            for (int j = 1; j < Paths[i].size(); ++j) {
                cout<<Paths[i][j]<<" - ";
            }
            cout<<Paths[i][0]<<endl;
        }
    }



    Graph Astar(string startVertex, string endVertex){
        Graph<Node_type> ArbolMinimoRecorrido(this->GetIsDirected());
        ArbolMinimoRecorrido.AddVertex(startVertex,*(Self[startVertex]->getSelf()));

        double total_dist;
        double distance;

        string IDvertex;
        string IDvertexAdy;

        auto cmpPair =[](const pair<double,string>& A,const pair<double,string>& B){ return A.first < B.first; };

        map<string, bool> visited;
        map<string, string> parent;
        vector<pair<double,string>> distAcum;

        map<string, double> dist;
        for (auto it = Self.cbegin(); it != Self.cend(); ++it){
            dist.emplace(it->first,DBL_MAX);
            visited.emplace(it->first,false);
        }
        dist[startVertex] = 0;
        parent[startVertex] = startVertex;
        distAcum.emplace_back(0,startVertex);

        while(!distAcum.empty()){
            IDvertex = distAcum.begin()->second;
            visited[IDvertex] = true;
            distAcum.erase(distAcum.begin());

            if(IDvertex == endVertex) break;

            auto listaAdy = Self[IDvertex]->getLista();

            for (int i = 0; i < listaAdy.size(); ++i) {
                IDvertexAdy = listaAdy[i]->vertexAdy(IDvertex);
                if(!visited[IDvertexAdy]){
                    distance = dist[IDvertex] + listaAdy[i]->getWeight();

                    if(dist[IDvertexAdy] > distance){
                        dist[IDvertexAdy] = distance;
                        parent[IDvertexAdy] = IDvertex;

                        total_dist = distance + Node_type::Calculate_weight(*Self[IDvertexAdy]->self,*Self[endVertex]->self);
                        distAcum.emplace_back(total_dist,IDvertexAdy);
                    }

                }
            }
            sort(distAcum.begin(),distAcum.end(),cmpPair);
        }

        if(parent.find(endVertex) != parent.end()){
            string ID = endVertex;
            ArbolMinimoRecorrido.AddVertex(ID,*Self[ID]->self);

            vector<string> vertices;
            vertices.insert(vertices.begin(),ID);

            while(ID != parent[ID]){
                ArbolMinimoRecorrido.AddVertex(ID,*Self[ID]->self);
                vertices.insert(vertices.begin(),parent[ID]);

                ID = parent[ID];
            }

            for (int i = 0; i < vertices.size() - 1; ++i) {
                auto edge = FindedEdge(vertices[i],vertices[i+1]);
                ArbolMinimoRecorrido.AddEdge(vertices[i],vertices[i+1],edge->getWeight());
                PrintEdge(edge->getPair()); //OPCIONAL
            }

        }else{
            cout<<"No se encontro camino"<<endl;
        }
        return ArbolMinimoRecorrido;
    }
    ~Graph(){
        ClearEdges();
        ClearVertexes();
    }

    vector<Vertex<Node_type>*> GetNodes(){
        vector<Vertex<Node_type>*> MyNodes;
        for(auto i:Self)
            MyNodes.push_back(i.second);
        return MyNodes;
    }

    vector<Edge*> BFS(const string& RootID){
        if(!FindVertex(RootID))
            throw out_of_range("Elige un Root valido");
        if(!IsConnected())
            throw out_of_range("El grafo no es conexo");
        if(IsDirected and Self[RootID]->getLista().size()==0)
            throw out_of_range("Elige un Root valido");


        queue<string> Process;
        map<string,bool> CheckList;
        for(auto iterator:Self)
            CheckList[iterator.first]=false;

        Process.push(RootID); CheckList[RootID]=true;
        vector<Edge*> toBuild;
        while(!Process.empty()){
            string temp=Process.front(); Process.pop();
            for(auto iterator:Self[temp]->getLista()){
                string other=iterator->getOtherId(temp);
                if(!CheckList[other]){
                    CheckList[other]=true;
                    Process.push(other);
                    toBuild.push_back(iterator);
                }
            }
        }
        return toBuild;
    }
    vector<Edge*> BFS(){
        auto it = Self.begin();
        return BFS((*it).first);
    }

    void printBFS(string Id){
        for(auto item:BFS(Id))
            PrintEdge(item->getPair());
        cout<<endl;
    }
    void printBFS(){
        for(auto item:BFS())
            PrintEdge(item->getPair());
        cout<<endl;

    }

    vector<Edge*> DFS(const string& RootID){
        if(!FindVertex(RootID))
            throw out_of_range("Elige un Root valido");
        if(!IsConnected())
            throw out_of_range("El grafo no es conexo");
        if(IsDirected and Self[RootID]->getLista().size()==0)
            throw out_of_range("Elige un Root valido");

        map<string,bool> CheckList;
        for (auto v : Self)
            CheckList[v.first] = false;

        vector<Edge*> toBuild; stack<string> Process; Process.push(RootID);

        while(!Process.empty()){
            string temp = Process.top();
            CheckList[temp] = true;
            int contador=0;
            for(auto iterator:Self[temp]->getLista()){
                string other=iterator->getOtherId(temp);
                if(!CheckList[other]){
                    Process.push(other);
                    toBuild.push_back(iterator);
                    contador++;
                    break;
                }
            }
            if(contador==0)
                Process.pop();
        }
        return toBuild;
    }
    vector<Edge*> DFS(){
        auto it = Self.begin();
        return DFS((*it).first); }

    void printDFS(string Id){
        for(auto item:DFS(Id))
            PrintEdge(item->getPair());
        cout<<endl;
    }
    void printDFS(){
        for(auto item:DFS())
            PrintEdge(item->getPair());
        cout<<endl;

    }


    pair<vector<vector<string>>,vector<vector<double>>> FloydWarshall(){
        if (!IsDirected)
            throw std::invalid_argument("El algoritmo solo puede ser aplicado en grafos dirigidos");

        vector<string> keys;
        for (auto s : Self)
            keys.push_back(s.first);

        vector<vector<double>> dist;
        vector<vector<string>> path;
        int n = Self.size();
        for (int i = 0; i < n; ++i) {
            vector<double> row;
            vector<string> pr;
            dist.push_back(row);
            path.push_back(pr);
            for (int j = 0; j < n; ++j) {
                double value = Distance(keys[i],keys[j]);
                dist[i].push_back(value);
                if (value != INT32_MAX){
                    path[i].emplace_back(keys[j]);
                } else {
                    path[i].emplace_back("N");
                }
            }
        }

        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = keys[k];
                    }
                }

        return make_pair(path,dist);
    }
    void PrintFloydWarshall() {
        auto FWmtx = FloydWarshall().first;
        auto FWmtx2 = FloydWarshall().second;
        cout << "\\ \t";
        vector<string> keys;
        for (auto s : Self) {
            keys.push_back(s.first);
            cout << "(" << s.first << ")\t";
        }
        cout << endl;
        int n = Self.size();
        for (int i = 0; i < n; ++i) {
            cout << "(" << keys[i] << ")\t";
            for (int j = 0; j < n; ++j) {
                cout << FWmtx[i][j] << "\t";
            } cout << endl;
        }
        cout<<"\n\n";

        for (auto s : Self) {
            keys.push_back(s.first);
            cout << "(" << s.first << ")\t";
        }
        cout << endl;
        for (int i = 0; i < n; ++i) {
            cout << "(" << keys[i] << ")\t";
            for (int j = 0; j < n; ++j) {
                if (FWmtx2[i][j] >= INT32_MAX or FWmtx2[i][j]>= MAX) cout << "INF\t";
                else
                    cout << FWmtx2[i][j] << "\t";
            } cout << endl;
        }
        cout << endl<<endl;
    }

    unordered_map <string,double> BellmanFord(const string& origen) {
        if (!IsDirected)
            throw std::invalid_argument("El algoritmo solo puede ser aplicado en grafos dirigidos");

        unordered_map <string,double> dist;
        for (auto v : Self)
            dist[v.first] = INT32_MAX;
        dist[origen] = 0;



        for (int i = 0; i < Self.size()-1; ++i)
            for (auto s : Self)
                for (auto e : Self[s.first]->Lista_de_adyacencia) {
                    string u = e->getIdBegin(), v = e->getIdEnd();
                    double w = e->getWeight();
                    if (dist[u] != INT32_MAX && dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }

        for (auto s : Self)
            for (auto e : Self[s.first]->Lista_de_adyacencia) {
                string u = e->getIdBegin(), v = e->getIdEnd();
                double w = e->getWeight();
                if (dist[u] != INT32_MAX && dist[u] + w < dist[v])
                    throw std::invalid_argument("El grafo contiene un ciclo de peso negativo");
            }
        return dist;
    }

    void PrintBellmanFord(const string& origen) {
        auto dist = this->BellmanFord(origen);
        cout << "Vertex\t Distance from Source\n";
        for (auto v : Self)
            cout << v.first << "\t\t" << dist[v.first] << endl;
    }

    unordered_map <string,double> BellmanFord_Optimized(const string& origen) {
        if (!IsDirected)
            throw std::invalid_argument("El algoritmo solo puede ser aplicado en grafos dirigidos");

        string u;
        string v;

        unordered_map<string, double> dist;
        unordered_map<string, bool> en_cola;

        queue<string> qp;
        for (auto v : Self) {
            dist[v.first] = INT32_MAX;
            en_cola[v.first] = false;
        }
        dist[origen] = 0;
        qp.push(origen);
        en_cola[origen] = true;

        while(!qp.empty()){
            u = qp.front();
            qp.pop();
            en_cola[u] = false;
            for(auto edge : Self[u]->Lista_de_adyacencia) {
                v = edge->getIdEnd();
                if(dist[v] > dist[u] + edge->getWeight()){
                    dist[v] = dist[u] + edge->getWeight();
                    if (!en_cola[v]){
                        qp.push(v);
                        en_cola[v] = true;
                    }
                }
            }
        }
        return dist;
    }


    void PrintBellmanFord_Optimized(const string& origen) {
        auto dist = this->BellmanFord_Optimized(origen);
        cout << "Vertex\t Distance from Source\n";
        for (auto v : Self){
            if(dist[v.first]!=MAX)
                cout << v.first << "\t\t" << dist[v.first] << endl;
            else
                cout << v.first << "\t\t" << "INF" << endl;
        }
    }


};

#endif //GRAPHS_GETGROUP_GETNAME_Graph_H