//
// Created by fabrizio on 26/10/2019.
//

#ifndef GRAPHS_GETGROUP_GETNAME_AIRPORT_H
#define GRAPHS_GETGROUP_GETNAME_AIRPORT_H

#include "../Aristas/Arista_dirigida.h"
class Airport {
private:
    string City, Name, Country;
    float Longitude,Latitude;
    int destinations[];
public:
    typedef Arista_dirigida Edge_type;

    Airport(const string& City, const string& Name, const string& Country,float Latitude,float Longitude,string destinations[]){
        this->City=City; this->Name=Name; this->Country=Country; this->Longitude=Longitude; this->Latitude=Latitude;

        for (size_t i = 0; i < destinations->size(); i++)
            this->destinations[i]=stoi(destinations[i]);
    }

}
;


#endif //GRAPHS_GETGROUP_GETNAME_AIRPORT_H
