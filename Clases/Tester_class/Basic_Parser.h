#ifndef GRAPHS_GETGROUP_GETNAME_BASIC_PARSER_H
#define GRAPHS_GETGROUP_GETNAME_BASIC_PARSER_H
#include <utility>

#include "Basic_class.h"

class Basic_Parser {
    string archivo;
public:
    explicit Basic_Parser(string archivo) : archivo(std::move(archivo)) {}

    Grafo<String_class> Generate_Graph(){
        map<string,Vertice<String_class>*> Map_for_graph;
        ifstream ifs(archivo); IStreamWrapper isw(ifs); Document d; d.ParseStream(isw);


        Value& vertices= d["Vertices"];
        for (size_t i=0; i<vertices.Size(); i++) {
            auto basic_class1=new String_class(vertices[i].GetString());
            auto vertice1= new Vertice<String_class> (basic_class1);
            Map_for_graph[vertice1->getSelf()->getName()]=vertice1;
        }

        Grafo<String_class> Grafo1(Map_for_graph, false);


        Value& aristas= d["Aristas"];
        for (size_t i=0; i<aristas.Size(); i++) {
            auto vertice1=aristas[i][0].GetString();auto vertice2=aristas[i][1].GetString();
            auto arista=new Arista(vertice1,vertice2,aristas[i][2].GetInt());
            Grafo1.getSelf()[vertice1]->Lista_de_adyacencia.push_back(arista);
            Grafo1.getSelf()[vertice2]->Lista_de_adyacencia.push_back(arista);
        }

        return Grafo1;
    }

};


#endif //GRAPHS_GETGROUP_GETNAME_BASIC_PARSER_H
