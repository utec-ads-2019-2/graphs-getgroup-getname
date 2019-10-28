#include <iostream>
#include "Clases/Grafo.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"
#include "Clases/DisjoinSet.h"

int main() {



    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");

    auto Grafo_1=Parser_1.Generate_Graph();
    Grafo_1.Prim();
    Grafo_1.Agregar_Vertice("F", Airport("Lima","Respect Airport","Peru",-59.785278,54.910278,3123));
    Grafo_1.Agregar_Arista("F","2");

    cout<<Grafo_1.Find_Vertex("A")<<Grafo_1.Find_Vertex("1")<<
        Grafo_1.Find_edge("2","F")<<Grafo_1.Find_edge("F","2");



    auto Grafo_2=Parser_2.Generate_Graph();
    Grafo_2.Prim();
    cout<<"\n\n\n";
    Grafo_2.Kruskal();
    Grafo_2.Agregar_Vertice("F",String_class("F"));
    Grafo_2.Agregar_Arista("A","B",500);
    cout<<Grafo_2.Find_Vertex("A")<<Grafo_2.Find_Vertex("Z");
    cout<<Grafo_2.Find_edge("A","B")<<Grafo_2.Find_edge("B","A");

    return 0;
}