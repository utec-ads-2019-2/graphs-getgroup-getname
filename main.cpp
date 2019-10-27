#include <iostream>
#include "Clases/Grafos/Grafo.h"
#include "Clases/Airports/AirportParser.h"

int main() {
    AirportParser Parser_1("../json_files/airports_mini.json");
    auto Grafo_1=Parser_1.Generate_Graph();
    return 0;
}