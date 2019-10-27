#include <iostream>
#include "Clases/Grafo.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"

int main() {
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");



    auto Grafo_1=Parser_1.Generate_Graph();
    Grafo_1.Prim();
    Grafo_1.Agregar_Vertice("F", Airport("Lima","Respect Airport","Peru",-59.785278,54.910278,3123));
    Grafo_1.Agregar_Arista("F","2");



    auto Grafo_2=Parser_2.Generate_Graph();
    Grafo_2.Prim();
    Grafo_2.Agregar_Vertice("F",String_class("F"));
    Grafo_2.Agregar_Arista("A","B",500);
    return 0;
}