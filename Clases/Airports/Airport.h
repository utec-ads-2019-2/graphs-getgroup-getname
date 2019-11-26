//
// Created by fabrizio on 26/10/2019.
//

#ifndef GRAPHS_GETGROUP_GETNAME_AIRPORT_H
#define GRAPHS_GETGROUP_GETNAME_AIRPORT_H

#include <utility>
#include <cmath>


class Airport {
private:
    string City, Name, Country;
    float Longitude,Latitude;
    int id;
public:

    Airport(string city, string name, string country, float longitude, float latitude, int id) :
            City(std::move(city)), Name(std::move(name)), Country(std::move(country)), Longitude(longitude), Latitude(latitude),
            id(id){}
    int getId() const {
        return id;
    }

    const string &getName() const {
        return Name;
    }

    float getLongitude() const {
        return Longitude;
    }

    float getLatitude() const {
        return Latitude;
    }


    static double Calculate_weight(const Airport& airport1,const Airport& airport2){

        double dLat = (airport2.getLatitude() - airport1.getLatitude() ) *  M_PI / 180.0;
        double dLon = (airport2.getLongitude() - airport1.getLongitude()) * M_PI / 180.0;
        double lat1 = (airport1.getLatitude()) * M_PI / 180.0;
        double lat2 = (airport2.getLatitude()) * M_PI / 180.0;

        double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) *cos(lat1) * cos(lat2);
        double rad = 6371, c = 2 * asin(sqrt(a));
        return rad * c;
        }

    ~Airport()= default;
}
;


#endif //GRAPHS_GETGROUP_GETNAME_AIRPORT_H
