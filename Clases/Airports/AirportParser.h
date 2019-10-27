#ifndef GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
#define GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
#include "Airport.h"
#include "../../rapidjson/document.h"
#include "../../rapidjson/writer.h"
#include "../../rapidjson/stringbuffer.h"
#include "../../rapidjson/istreamwrapper.h"
#include <fstream>
#include <utility>
#include <vector>
using namespace rapidjson;
class AirportParser{
    string archivo;

public:

    explicit AirportParser(string file):archivo(std::move(file)){
    }

    Grafo<Airport> Generate_Graph(){
        map<string,Vertice<Airport>*> Map_for_graph;
        ifstream ifs(archivo); IStreamWrapper isw(ifs); Document d; d.ParseStream(isw);
        for(auto itr = d.Begin(); itr != d.End() ;++itr){
            string City=(*itr)["City"].GetString(),Name=(*itr)["Name"].GetString(),Country=(*itr)["Country"].GetString();
            float Longitude=stof((*itr)["Longitude"].GetString()),Latitude=stof((*itr)["Latitude"].GetString());
            int Id=stoi((*itr)["Id"].GetString());


            const Value& a = (*itr)["destinations"]; vector<Arista_dirigida*> aristas;

            for (SizeType i = 0; i < a.Size(); i++){
                auto arista= new Arista_dirigida((*itr)["Id"].GetString(),a[i].GetString());
                aristas.push_back(arista);
            }

            auto airport1=new Airport(City,Name,Country,Longitude,Latitude,Id);
            auto vertice1=new Vertice<Airport> (airport1,aristas);
            Map_for_graph[to_string(vertice1->getSelf()->getId())]=vertice1;
        }

        for(const auto& vertice:Map_for_graph){
            for(auto arista:vertice.second->getLista()){
                auto Primer_vertice=vertice.second->getSelf();
                auto Segundo_Vertice=Map_for_graph[arista->getIdEnd()]->getSelf();
                arista->setWeight(Airport::Calculate_distance(*Primer_vertice,*Segundo_Vertice));
            }
        }


        Grafo<Airport> Grafo1(Map_for_graph);
        return Grafo1;
    }

};


#endif //GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
