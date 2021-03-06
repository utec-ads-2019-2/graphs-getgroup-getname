#include <iostream>
#include "Clases/Graph.h"
#include "Clases/Airports/AirportParser.h"
#include "Clases/Tester_class/Basic_Parser.h"
#include "Clases/Tester_class/Heuristic_Parser.h"

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#endif


void TestConstructorAndLoadFromFile(){
    AirportParser Parser_1("../json_files/airports.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());
    ASSERT(Grafo_dirigido!= nullptr,"Constructor con errores");
    ASSERT(Grafo__no_dirigido!= nullptr,"Constructor con errores");
    ASSERT(Grafo__no_dirigido->GetNumberOfEdgesGraph() == 20, "Incorrecto numero de aristas");
    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestFindEdgeAndFindVertex(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(!Grafo_dirigido->FindVertex("NewID"),"Error en Encontrar Vertex");
    ASSERT(!Grafo__no_dirigido->FindVertex("NewID"),"Error en Encontrar Vertex");
    ASSERT(!Grafo_dirigido->FindEdge("1","6"),"Error en Encontrar Edge");
    ASSERT(!Grafo__no_dirigido->FindEdge("I","B"),"Error en Encontrar Edge");


    Grafo_dirigido->AddVertex("NewID",Airport("City","Name","Country",12.12,12.12,10000));
    Grafo__no_dirigido->AddVertex("NewID",String_class("NewID"));
    Grafo__no_dirigido->AddEdge("I","B");
    Grafo_dirigido->AddEdge("1","6");

    ASSERT(Grafo_dirigido->FindVertex("NewID"),"Error en Encontrar Vertex");
    ASSERT(Grafo__no_dirigido->FindVertex("NewID"),"Error en Encontrar Vertex");
    ASSERT(Grafo_dirigido->FindEdge("1","6"),"Error en Encontrar Edge");
    ASSERT(Grafo__no_dirigido->FindEdge("I","B"),"Error en Encontrar Edge");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestRemoveAndAddVertex(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(!Grafo_dirigido->FindVertex("NewID"),"Error en Insertar Vertex");
    ASSERT(!Grafo__no_dirigido->FindVertex("NewID"),"Error en Insertar Vertex");

    Grafo_dirigido->AddVertex("NewID",Airport("City","Name","Country",12.12,12.12,10000));
    Grafo__no_dirigido->AddVertex("NewID",String_class("NewID"));

    ASSERT(Grafo_dirigido->FindVertex("NewID"),"Error en Insertar Vertex");
    ASSERT(Grafo__no_dirigido->FindVertex("NewID"),"Error en Insertar Vertex");


    Grafo_dirigido->RemoveVertex("NewID");
    Grafo__no_dirigido->RemoveVertex("NewID");

    ASSERT(!Grafo_dirigido->FindVertex("NewID"),"Error en Remover Vertex");
    ASSERT(!Grafo__no_dirigido->FindVertex("NewID"),"Error en Remover Vertex");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestRemoveAndAddEdge(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(!Grafo_dirigido->FindEdge("1","6"),"Error en Insertar Edge");
    ASSERT(!Grafo__no_dirigido->FindEdge("I","B"),"Error en Insertar Edge");

    Grafo__no_dirigido->AddEdge("I","B");
    Grafo_dirigido->AddEdge("1","6");

    ASSERT(Grafo_dirigido->FindEdge("1","6"),"Error en Insertar Edge");
    ASSERT(Grafo__no_dirigido->FindEdge("I","B"),"Error en Insertar Edge");

    Grafo__no_dirigido->RemoveEdge("I","B");
    Grafo_dirigido->RemoveEdge("1","6");


    ASSERT(!Grafo_dirigido->FindEdge("1","6"),"Error en Remover Edge");
    ASSERT(!Grafo__no_dirigido->FindEdge("I","B"),"Error en Remover Edge");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestDensity(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    float DDensity=Grafo_dirigido->GetDensity(); float UDensity=Grafo__no_dirigido->GetDensity();

    ASSERT(Grafo_dirigido->IsDense(DDensity),"Densidad con errores");
    ASSERT(Grafo__no_dirigido->IsDense(UDensity),"Densidad con errores");

    Grafo_dirigido->RemoveVertex("1");
    Grafo__no_dirigido->RemoveVertex("A");

    ASSERT(!Grafo_dirigido->IsDense(DDensity),"Densidad con errores");
    ASSERT(!Grafo__no_dirigido->IsDense(UDensity),"Densidad con errores");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;

}

void TestIsConnected(){
    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(Grafo__no_dirigido->IsConnected(),"Error en Grafo Conexo");
    ASSERT(Grafo_dirigido->IsConnected(),"Error en Grafo Conexo");


    Grafo__no_dirigido->RemoveEdge("I","F");
    Grafo__no_dirigido->RemoveEdge("C","F");

    Grafo_dirigido->RemoveEdge("3","4");
    Grafo_dirigido->RemoveEdge("1","2");

    ASSERT(!Grafo__no_dirigido->IsConnected(),"Error en Grafo Conexo");
    ASSERT(!Grafo_dirigido->IsConnected(),"Error en Grafo Conexo");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestIsStronglyConnected(){
    AirportParser Parser_1("../json_files/airports_strong.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(Grafo__no_dirigido->IsStrongConnected(),"Error en Grafo Fuertemente Conexo");
    ASSERT(Grafo_dirigido->IsStrongConnected(),"Error en Grafo Fuertemente Conexo");


    Grafo__no_dirigido->RemoveEdge("I","F");
    Grafo__no_dirigido->RemoveEdge("C","F");

    Grafo_dirigido->RemoveEdge("6","1");
    Grafo_dirigido->RemoveEdge("1","2");
    Grafo_dirigido->RemoveEdge("2","1");

    ASSERT(!Grafo__no_dirigido->IsStrongConnected(),"Error en Grafo Fuertemente Conexo");
    ASSERT(!Grafo_dirigido->IsStrongConnected(),"Error en Grafo Fuertemente Conexo");

    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestIsBipartite(){
    AirportParser Parser_1("../json_files/airports_bipartite.json");
    Basic_Parser Parser_2("../json_files/tester_for_bipartite.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    ASSERT(Grafo__no_dirigido->IsBipartite(),"Error en Grafo Bipartito");
    ASSERT(Grafo_dirigido->IsBipartite(),"Error en Grafo Bipartito");

    Grafo_dirigido->AddEdge("6","4");
    Grafo__no_dirigido->AddEdge("F","G");

    ASSERT(!Grafo__no_dirigido->IsBipartite(),"Error en Grafo Bipartito");
    ASSERT(!Grafo_dirigido->IsBipartite(),"Error en Grafo Bipartito");


    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestPrim(){
    AirportParser Parser_1("../json_files/airports_mini.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());


    vector<Edge*> PrimResult, PrimExpected=Grafo__no_dirigido->Prim("A");


    PrimResult.push_back( new Edge("A","C"));
    PrimResult.push_back( new Edge("A","H"));
    PrimResult.push_back( new Edge("D","H"));
    PrimResult.push_back( new Edge("C","F"));
    PrimResult.push_back( new Edge("F","I"));
    PrimResult.push_back( new Edge("A","E"));
    PrimResult.push_back( new Edge("E","G"));
    PrimResult.push_back( new Edge("B","G"));
    PrimResult.push_back( new Edge("H","J"));


    for(size_t i=0;i<PrimExpected.size();i++){
        ASSERT(PrimExpected[i]->getParId()==PrimResult[i]->getParId(),"Error en Prim");

    }

    ASSERT(Grafo_dirigido->Prim().empty(),"Error en Prim");
    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}

void TestKruskal(){
    AirportParser Parser_1("../json_files/airports_connected.json");
    Basic_Parser Parser_2("../json_files/tester.json");
    auto Grafo_dirigido=new Graph<Airport>(Parser_1.Generate_Graph());
    auto Grafo__no_dirigido=new Graph<String_class>(Parser_2.Generate_Graph());

    vector<Edge*> KruskalResult, KruskalExpected=Grafo__no_dirigido->Kruskal();

    KruskalResult.push_back( new Edge("B","G"));
    KruskalResult.push_back( new Edge("E","G"));
    KruskalResult.push_back( new Edge("A","C"));
    KruskalResult.push_back( new Edge("A","H"));
    KruskalResult.push_back( new Edge("D","H"));
    KruskalResult.push_back( new Edge("F","I"));
    KruskalResult.push_back( new Edge("C","F"));
    KruskalResult.push_back( new Edge("A","E"));
    KruskalResult.push_back( new Edge("B","J"));


    for(size_t i=0;i<KruskalExpected.size();i++){
        ASSERT(KruskalExpected[i]->getParId()==KruskalResult[i]->getParId(),"Error en Kruskal");

    }

    ASSERT(Grafo_dirigido->Kruskal().empty(),"Error en Kruskal");


    delete Grafo__no_dirigido;
    delete Grafo_dirigido;
}


int main() {

    ///TEST DE TODOS LOS METODOS EN GRAFOS DIRIGIDOS Y NO DIRIGIDOS


    TestConstructorAndLoadFromFile();

    TestFindEdgeAndFindVertex();

    TestRemoveAndAddVertex();

    TestRemoveAndAddEdge();

    TestDensity();

    TestIsConnected();

    TestIsStronglyConnected();

    TestIsBipartite();

    TestPrim();

    TestKruskal();
    return EXIT_SUCCESS;

}