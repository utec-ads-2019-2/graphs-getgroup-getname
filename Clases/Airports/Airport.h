//
// Created by fabrizio on 26/10/2019.
//

#ifndef GRAPHS_GETGROUP_GETNAME_AIRPORT_H
#define GRAPHS_GETGROUP_GETNAME_AIRPORT_H

#include <utility>

#include "../Aristas/Arista_dirigida.h"
class Airport {
private:
    string City, Name, Country;
    float Longitude,Latitude;
    int id;
    int *destinations;
public:
    typedef Arista_dirigida Edge_type;

    Airport(string city, string name, string country, float longitude, float latitude, int id,int *destinations) :

            City(std::move(city)), Name(std::move(name)), Country(std::move(country)), Longitude(longitude), Latitude(latitude),
            id(id), destinations(destinations) {

    }
}
;


#endif //GRAPHS_GETGROUP_GETNAME_AIRPORT_H
