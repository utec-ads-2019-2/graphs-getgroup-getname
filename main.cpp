#include <iostream>
#include "Clases/Grafo.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"

int main() {

    AirportParser Parser_1("../json_files/airports.json");
    Basic_Parser Parser_2("../json_files/tester.json");

    auto Graph1 =new Graph<Airport>(Parser_1.Generate_Graph());
    Graph1->AddEdge("1","2");
    delete Graph1;


    auto Graph_2=Parser_2.Generate_Graph();
    Graph_2.RemoveVertex("C");
    return 0;
}