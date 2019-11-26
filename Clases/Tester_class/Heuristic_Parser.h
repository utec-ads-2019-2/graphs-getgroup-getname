#ifndef PROYECT_1_HEURISTIC_PARSER_H
#define PROYECT_1_HEURISTIC_PARSER_H

#include "Heuristic_class.h"

class Heuristic_Parser{
    string archivo;
public:
    explicit Heuristic_Parser(string archivo) : archivo(std::move(archivo)) {}

    Graph<Heuristic_class> Generate_Graph(){

        map<string,Vertice<Heuristic_class>*> Map_for_graph;

        ifstream ifs(archivo); IStreamWrapper isw(ifs); Document d; d.ParseStream(isw);

        Value& vertices= d["Vertices"];

        for (size_t i=0; i<vertices.Size(); i++) {
            auto heuristic1=new Heuristic_class(vertices[i].GetObject()["ID"].GetString(),
                    vertices[i]["posX"].GetInt(),vertices[i]["posY"].GetInt());

            auto vertice1= new Vertice<Heuristic_class> (heuristic1);
            Map_for_graph[vertice1->getSelf()->getName()] = vertice1;
        }

        Graph<Heuristic_class> Graph1(Map_for_graph, false);

        Value& aristas= d["Aristas"];
        for (size_t i=0; i<aristas.Size(); i++) {
            auto vertice1=aristas[i][0].GetString();
            auto vertice2=aristas[i][1].GetString();

            auto arista=new Arista(vertice1,vertice2);
            arista->setWeight(Heuristic_class::Calculate_weight(*Map_for_graph[vertice1]->self,*Map_for_graph[vertice2]->self));

            Graph1.getSelf()[vertice1]->Lista_de_adyacencia.push_back(arista);
            Graph1.getSelf()[vertice2]->Lista_de_adyacencia.push_back(arista);
        }

        return Graph1;
    }

    ~Heuristic_Parser()= default;
};


#endif //PROYECT_1_HEURISTIC_PARSER_H
