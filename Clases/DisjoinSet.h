#ifndef PROYECT_1_DISJOINSET_H
#define PROYECT_1_DISJOINSET_H


#include <string>
#include <map>
using namespace std;
struct Node{
    string data;
    int rank;
    Node* parent;

    Node(string data) : data(data), rank(0), parent(this){};
};

class DisjointSet{
    map<string, Node*> nodes;
public:
    void makeSet(string Id){
        Node* node = new Node(Id);
        nodes.emplace(Id,node);
    }
    void unionSet(string idA, string idB){
        Node* nodeA = nodes[idA];
        Node* nodeB = nodes[idB];

    }


};




#endif //PROYECT_1_DISJOINSET_H
