#include <iostream>
#include "Clases/Graph.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"
#include "Clases/Tester_class/Basic_Parser_D.h"
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



void TestDFS(){    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo_dirigido->DFS("6");
    Grafo__no_dirigido->DFS("J");
    Grafo__no_dirigido->printDFS("J");

}

void TestBFS(){
    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo_dirigido->BFS("1");
    Grafo__no_dirigido->BFS("J");
    Grafo__no_dirigido->printBFS("J");

}

void TestBellmanFord(){
    AirportParser Parser_2("../json_files/airports.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_2.Generate_Graph());
    Grafo_dirigido->PrintBellmanFord("1818");
}

void TestFloydWarshall(){
    Basic_Parser_D Parser_2("../json_files/FW2.json");
    auto Grafo_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    Grafo_dirigido->PrintFloydWarshall();
}

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