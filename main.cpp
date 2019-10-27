#include <iostream>
#include "Clases/Grafo.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"

int main() {
    //AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    //auto Grafo_1=Parser_1.Generate_Graph();
    auto Grafo_2=Parser_2.Generate_Graph();
    Grafo_2.Prim();
    return 0;
}