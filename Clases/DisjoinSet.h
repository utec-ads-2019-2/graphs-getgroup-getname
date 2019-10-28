#ifndef PROYECT_1_DISJOINSET_H
#define PROYECT_1_DISJOINSET_H


#include <string>
#include <map>
using namespace std;
template <typename T>
class DisjointSet{
private:
    struct Node{
        T data;
        int rank;
        Node* parent;

        Node(T data) : data(data), rank(0), parent(this){};
    };

    map<T, Node*> nodes;

    Node* findSet(Node* node){
        Node* parent = node->parent;
        if(parent == node) return parent;
        node->parent = findSet(node->parent);
        return node->parent;
    }
public:
    DisjointSet(){};
    void makeSet(T Id){
        Node* node = new Node(Id);
        nodes[Id]=node;
    }

    T findSet(T data){
        return findSet(nodes[data])->data;
    }

    void unionSet(T idA, T idB){

        Node* parentA = findSet(nodes[idA]);
        Node* parentB = findSet(nodes[idB]);

        if(parentA->data == parentB->data) return;

        if(parentA->rank >= parentB->rank){
            if(parentA->rank == parentB->rank){
                (parentA->rank)++;
            }
            parentB->parent = parentA;
        }
        else parentA->parent = parentB;

    }


};




#endif //PROYECT_1_DISJOINSET_H
