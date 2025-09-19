#include <iostream>

struct nodo_arco; // Declaracion adelantada
struct nodo_grafo; // Declaracion adelantada

struct nodo_grafo{
    // Funciones de asignacion a nodo
    int id_nodo;
    //...
    nodo_arco* lista_arco;
    nodo_grafo* link;
};

typedef nodo_grafo Ngrafo;

struct nodo_arco{
    // Funciones de asignacion a arco
    int id_arco;
    //...
    nodo_arco* link;
    Ngrafo* destino;
};

typedef nodo_arco Narco;

// Agregar nodo al grafo
void grafo_agregar_nodo(Ngrafo*& grafo, int id_nodo){

    // Verificar si el nodo ya existe
    Ngrafo* aux = grafo;
    while (aux != NULL){
        if (aux->id_nodo == id_nodo){
            std::cout << "El nodo" << aux->id_nodo << "ya existe en el grafo." << std::endl;
            return;
        }
         aux = aux->link;
    }

    Ngrafo* nuevo = new Ngrafo;
    nuevo->id_nodo = id_nodo;
    nuevo->lista_arco = NULL;
    nuevo->link = grafo;
    grafo = nuevo;
}

// Agregar arco al grafo
void grafo_agregar_arco(Ngrafo* grafo, int id_nodo_origen, int id_nodo_destinto, int id_arco){

    Ngrafo* nodo_origen = grafo;
    Ngrafo* nodo_destino= grafo;

    while(nodo_origen != NULL && nodo_origen->id_nodo != id_nodo_origen){
        nodo_origen = nodo_origen->link;
    }

    while(nodo_destino != NULL && nodo_destino->id_nodo != id_nodo_destinto){
        nodo_destino = nodo_destino->link;
    }

    if(nodo_origen == NULL || nodo_destino == NULL){
        std::cout << "El nodo origen o destino no existe en el grafo." << std::endl;
        return;
    }

   // Verificar que no exista el mismo arco
    Narco* arco_aux = nodo_origen->lista_arco; 
    while(arco_aux != NULL){
        if(arco_aux->id_arco == id_arco && arco_aux->destino == nodo_destino){
            std::cout << "El arco" << arco_aux->id_arco << "ya existe en el grafo." << std::endl;
            return;
        }
        arco_aux = arco_aux->link;
    }

    Narco* nuevo = new Narco;
    nuevo->id_arco = id_arco;
    nuevo->destino = nodo_destino;
    nuevo->link = nodo_origen->lista_arco;
    nodo_origen->lista_arco = nuevo;

}

// Función para imprimir el grafo y sus arcos
void imprimir_grafo(Ngrafo* grafo) {
    Ngrafo* nodo = grafo;
    while (nodo != NULL) {
        std::cout << "Nodo " << nodo->id_nodo << " -> ";
        Narco* arco = nodo->lista_arco;
        if(arco == NULL) {
            std::cout << "No tiene arcos";
        }
        while (arco != NULL) {
            std::cout << "(Arco " << arco->id_arco << " a Nodo " << arco->destino->id_nodo << ") ";
            arco = arco->link;
        }
        std::cout << std::endl;
        nodo = nodo->link;
    }
}

int main() {
    Ngrafo* grafo = NULL;

    // Agregar nodos
    grafo_agregar_nodo(grafo, 1);
    grafo_agregar_nodo(grafo, 2);
    grafo_agregar_nodo(grafo, 3);

    grafo_agregar_nodo(grafo, 3);
    
    // Agregar arcos
    grafo_agregar_arco(grafo, 1, 2, 101);
    grafo_agregar_arco(grafo, 1, 3, 102);
    grafo_agregar_arco(grafo, 2, 3, 103);

     grafo_agregar_arco(grafo, 2, 3, 103);

    // Imprimir grafo
    imprimir_grafo(grafo);

    return 0;
}