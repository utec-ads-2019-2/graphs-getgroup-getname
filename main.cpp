#include <iostream>
#include "Clases/Grafo.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"
#include "Clases/DisjoinSet.h"

int main() {

    /*DisjointSet<string> ds;
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(4);
    ds.makeSet(5);
    ds.makeSet(6);
    ds.makeSet(7);

    ds.unionSet(1,2);
    ds.unionSet(2,3);
    ds.unionSet(4,5);
    ds.unionSet(6,7);
    ds.unionSet(5,6);
    ds.unionSet(3,7);

    cout<<ds.findSet(1)<<endl;
    cout<<ds.findSet(2)<<endl;
    cout<<ds.findSet(3)<<endl;
    cout<<ds.findSet(4)<<endl;
    cout<<ds.findSet(5)<<endl;
    cout<<ds.findSet(6)<<endl;
    cout<<ds.findSet(7)<<endl;

    ds.makeSet("A");
    ds.makeSet("B");
    ds.makeSet("C");
    ds.makeSet("D");
    ds.makeSet("E");
    ds.makeSet("F");
    ds.makeSet("G");

    ds.unionSet("A","B");
    ds.unionSet("B","C");
    ds.unionSet("D","E");
    ds.unionSet("F","G");
    ds.unionSet("E","F");
    ds.unionSet("C","F");

    cout<<ds.findSet("A")<<endl;
    cout<<ds.findSet("B")<<endl;
    cout<<ds.findSet("C")<<endl;
    cout<<ds.findSet("D")<<endl;
    cout<<ds.findSet("E")<<endl;
    cout<<ds.findSet("F")<<endl;
    cout<<ds.findSet("G")<<endl;
*/

    //AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
/*
    auto Grafo_1=Parser_1.Generate_Graph();
    Grafo_1.Prim();
    Grafo_1.Agregar_Vertice("F", Airport("Lima","Respect Airport","Peru",-59.785278,54.910278,3123));
    Grafo_1.Agregar_Arista("F","2");

    cout<<Grafo_1.Find_Vertex("A")<<Grafo_1.Find_Vertex("1")<<
        Grafo_1.Find_edge("2","F")<<Grafo_1.Find_edge("F","2");
*/


    auto Grafo_2=Parser_2.Generate_Graph();
    Grafo_2.printPrim();
    Grafo_2.printPrim("B");
    Grafo_2.printKruskal();
    //Grafo_2.Kruskal();
    /*Grafo_2.Agregar_Vertice("F",String_class("F"));
    Grafo_2.Agregar_Arista("A","B",500);
    cout<<Grafo_2.Find_Vertex("A")<<Grafo_2.Find_Vertex("Z");
    cout<<Grafo_2.Find_edge("A","B")<<Grafo_2.Find_edge("B","A");
    */
    return 0;
}