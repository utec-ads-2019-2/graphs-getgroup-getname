#include <iostream>
#include "Clases/Graph.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"
#include "Clases/Tester_class/Heuristic_Parser.h"
#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#endif



void TestPrim(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());


    vector<Edge*> PrimResult, PrimExpected=Grafo__no_dirigido->Prim("A");


    PrimResult.push_back( new Edge("A", "C"));
    PrimResult.push_back( new Edge("A", "H"));
    PrimResult.push_back( new Edge("D", "H"));
    PrimResult.push_back( new Edge("C", "F"));
    PrimResult.push_back( new Edge("F", "I"));
    PrimResult.push_back( new Edge("A", "E"));
    PrimResult.push_back( new Edge("E", "G"));
    PrimResult.push_back( new Edge("B", "G"));
    PrimResult.push_back( new Edge("H", "J"));


    for(size_t i=0;i<PrimExpected.size();i++){
        ASSERT(PrimExpected[i]->getParId()==PrimResult[i]->getParId(),"Error en Prim");
    }

    ASSERT(Grafo_dirigido->Prim().empty(),"Error en Prim");
    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestKruskal(){
    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    vector<Edge*> KruskalResult, KruskalExpected=Grafo__no_dirigido->Kruskal();

    KruskalResult.push_back( new Edge("B", "G"));
    KruskalResult.push_back( new Edge("E", "G"));
    KruskalResult.push_back( new Edge("A", "C"));
    KruskalResult.push_back( new Edge("A", "H"));
    KruskalResult.push_back( new Edge("D", "H"));
    KruskalResult.push_back( new Edge("F", "I"));
    KruskalResult.push_back( new Edge("C", "F"));
    KruskalResult.push_back( new Edge("A", "E"));
    KruskalResult.push_back( new Edge("B", "J"));

    //Grafo__no_dirigido->PrintKruskal();

    for(size_t i=0;i<KruskalExpected.size();i++){
        ASSERT(KruskalExpected[i]->getParId()==KruskalResult[i]->getParId(),"Error en Kruskal");

    }

    ASSERT(Grafo_dirigido->Kruskal().empty(),"Error en Kruskal");


    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestDFS(){    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo_dirigido->DFS("6");
    Grafo__no_dirigido->DFS("J");

}
void TestBFS(){
    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo_dirigido->BFS("1");
    Grafo__no_dirigido->BFS("J");
    Grafo__no_dirigido->BFS();

}
void TestBellmanFord(){}
void TestFloydWarshall(){}
void TestDijkstra(){
    Basic_Parser Parser_2("../json_files/tester_Dijkstra.json");
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo__no_dirigido->Dijkstra("A");
    cout<<endl;
}
void TestAStar(){
    Heuristic_Parser nuevoGrafo1("../json_files/tester1_A.json");
    auto grafoHeuristic1 = new Graph<Heuristic_class>(nuevoGrafo1.Generate_Graph());
    grafoHeuristic1->Astar("A","G");
    cout<<endl;

    Heuristic_Parser nuevoGrafo2("../json_files/tester2_A.json");
    auto grafoHeuristic2 = new Graph<Heuristic_class>(nuevoGrafo2.Generate_Graph());
    grafoHeuristic2->Astar("A","D");
    cout<<endl;
}

int main() {

    ///TEST DE LOS ALGORITMOS DE LA SEGUNDA ENTREGA

    TestDFS();

    TestBFS();

    TestBellmanFord();

    TestFloydWarshall();

    TestDijkstra();

    TestAStar();

    return EXIT_SUCCESS;
}