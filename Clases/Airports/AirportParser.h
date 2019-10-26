#ifndef GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
#define GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
#include "Airport.h"
#include "../../rapidjson/document.h"
#include "../../rapidjson/writer.h"
#include "../../rapidjson/stringbuffer.h"
#include "../../rapidjson/istreamwrapper.h"
#include <fstream>
#include <utility>
using namespace rapidjson;

class AirportParser{
    string archivo;

    void Generate_airports(){
        ifstream ifs(archivo); IStreamWrapper isw(ifs); Document d; d.ParseStream(isw);
        for(auto itr = d.Begin(); itr != d.End() ;++itr){
            string City=(*itr)["City"].GetString(),Name=(*itr)["Name"].GetString(),Country=(*itr)["Country"].GetString();
            float Longitude=stof((*itr)["Longitude"].GetString()),Latitude=stof((*itr)["Latitude"].GetString());
            int Id=stoi((*itr)["Id"].GetString());


            const Value& a = (*itr)["destinations"]; auto destinations= new int[a.Size()];
            for (SizeType i = 0; i < a.Size(); i++){
                destinations[i]=stoi(a[i].GetString());
            }

            auto airport1=new Airport(City,Name,Country,Longitude,Latitude,Id,destinations);

        }
    }
public:

    explicit AirportParser(string file):archivo(std::move(file)){
        Generate_airports();
    }
};


#endif //GRAPHS_GETGROUP_GETNAME_AIRPORTPARSER_H
