#include <iostream>
#include "Listas_de_Adyacencia.h"


// Agregar nodo al grafo
void grafo_agregar_nodo(Ngrafo*& grafo, int id_nodo){
    // Verificar si el nodo ya existe
    Ngrafo* aux = grafo;
    while (aux != NULL){
        if (aux->id_nodo == id_nodo){
            std::cout << "El nodo " << id_nodo << " ya existe." << std::endl;
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

    // Verificar que no exista el mismo arco (mismo id_arco y mismo destino)
    Narco* arco_aux = nodo_origen->lista_arco;
    while(arco_aux != NULL){
        if(arco_aux->id_arco == id_arco && arco_aux->destino == nodo_destino){
            std::cout << "El arco " << id_arco << " ya existe entre esos nodos." << std::endl;
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

// Funcion para eliminar nodo
void grafo_eliminar_nodo(Ngrafo*& grafo, int id_nodo){
    Ngrafo* nodo_aux = grafo;
    Ngrafo* nodo_anterior = NULL;

    // Buscar el nodo a eliminar
    while (nodo_aux != NULL && nodo_aux->id_nodo != id_nodo) {
        nodo_anterior = nodo_aux;
        nodo_aux = nodo_aux->link;
    }

    if (nodo_aux == NULL) {
        std::cout << "El nodo " << id_nodo << " no existe." << std::endl;
        return;
    }

    // 1) Eliminar todos los arcos entrantes que apunten a nodo_aux
    Ngrafo* iter = grafo;
    while (iter != NULL) {
        Narco* arco = iter->lista_arco;
        Narco* arco_prev = NULL;
        while (arco != NULL) {
            if (arco->destino == nodo_aux) {
                Narco* to_delete = arco;
                if (arco_prev == NULL) {
                    iter->lista_arco = arco->link;
                } else {
                    arco_prev->link = arco->link;
                }
                arco = arco->link;
                delete to_delete;
                continue;
            }
            arco_prev = arco;
            arco = arco->link;
        }
        iter = iter->link;
    }

    // 2) Liberar la lista de arcos salientes del nodo a eliminar
    Narco* salida = nodo_aux->lista_arco;
    while (salida != NULL) {
        Narco* next = salida->link;
        delete salida;
        salida = next;
    }

    // 3) Quitar el nodo de la lista y liberarlo
    if (nodo_anterior == NULL) {
        grafo = nodo_aux->link;
    } else {
        nodo_anterior->link = nodo_aux->link;
    }
    delete nodo_aux;

    std::cout << "Nodo " << id_nodo << " eliminado." << std::endl;
}

// Funcion para eliminar un arco
void grafo_eliminar_arco(Ngrafo*& grafo, int id_nodo_origen, int id_nodo_destino, int id_arco) {
    Ngrafo* nodo_origen = grafo;
    Ngrafo* nodo_destino = grafo;

    while(nodo_origen != NULL && nodo_origen->id_nodo != id_nodo_origen){
        nodo_origen = nodo_origen->link;
    }

    while(nodo_destino != NULL && nodo_destino->id_nodo != id_nodo_destino){
        nodo_destino = nodo_destino->link;
    }

    if(nodo_origen == NULL || nodo_destino == NULL){
        std::cout << "El nodo origen o destino no existe en el grafo." << std::endl;
        return;
    }

    Narco* arco_aux = nodo_origen->lista_arco;
    Narco* arco_anterior = NULL;

    while(arco_aux != NULL){
        if(arco_aux->id_arco == id_arco && arco_aux->destino == nodo_destino){
            // eliminar
            if(arco_anterior == NULL){
                nodo_origen->lista_arco = arco_aux->link;
            } else {
                arco_anterior->link = arco_aux->link;
            }
            delete arco_aux;
            std::cout << "Arco " << id_arco << " eliminado." << std::endl;
            return;
        }
        arco_anterior = arco_aux;
        arco_aux = arco_aux->link;
    }

    std::cout << "El arco " << id_arco << " no existe." << std::endl;
}

// Funcion para calcular cantidad de nodos del grafo
int grafo_cantidad_nodos(Ngrafo* grafo){
    int contador = 0;
    Ngrafo* aux = grafo;
    while(aux != NULL){
        ++contador;
        aux = aux->link;
    }
    return contador;
}

// Funcion para calcular cantidad de arcos del grafo
int grafo_cantidad_arcos(Ngrafo* grafo){
    int contador = 0;
    Ngrafo* aux_nodo = grafo;
    while(aux_nodo != NULL){
        Narco* arco = aux_nodo->lista_arco;
        while(arco != NULL){
            ++contador;
            arco = arco->link;
        }
        aux_nodo = aux_nodo->link;
    }
    return contador;
}

// Funcion para determinar nodos adyacentes.
void grafo_nodos_adyacentes(Ngrafo* grafo, int id_nodo) {
    Ngrafo* nodo = grafo;
    while (nodo != NULL) {
        if (nodo->id_nodo == id_nodo) {
            Narco* arco = nodo->lista_arco;
            if (arco == NULL) {
                std::cout << "El nodo " << id_nodo << " no tiene adyacentes." << std::endl;
                return;
            }
            std::cout << "Adyacentes de " << id_nodo << ": ";
            while (arco != NULL) {
                std::cout << arco->destino->id_nodo << " (arco " << arco->id_arco << ") ";
                arco = arco->link;
            }
            std::cout << std::endl;
            return;
        }
        nodo = nodo->link;
    }
    std::cout << "El nodo " << id_nodo << " no existe." << std::endl;
}

// Funcion para determinar el conjunto derecho de un nodo
void grafo_conjunto_derecho(Ngrafo* grafo, int id_nodo) {   
    Ngrafo* nodo = grafo;
    while (nodo != NULL) {
        if (nodo->id_nodo == id_nodo) {
            Narco* arco = nodo->lista_arco;
            if (arco == NULL) {
                std::cout << "El nodo " << id_nodo << " no tiene adyacentes." << std::endl;
                return;
            }
            std::cout << "Conjunto derecho de " << id_nodo << ": ";
            while (arco != NULL) {
                std::cout << arco->destino->id_nodo << " ";
                arco = arco->link;
            }
            std::cout << std::endl;
            return;
        }
        nodo = nodo->link;
    }
    std::cout << "El nodo " << id_nodo << " no existe." << std::endl;
}




// Función para imprimir el grafo y sus arcos
void imprimir_grafo(Ngrafo* grafo) {
    Ngrafo* nodo = grafo;
    while (nodo != NULL) {
        std::cout << "Nodo " << nodo->id_nodo << " -> ";
        Narco* arco = nodo->lista_arco;
        if (arco == NULL) {
            std::cout << "No tiene arcos";
        } else {
            while (arco != NULL) {
                std::cout << "(Arco " << arco->id_arco << " a Nodo " << arco->destino->id_nodo << ") ";
                arco = arco->link;
            }
        }
        std::cout << std::endl;
        nodo = nodo->link;
    }
}

// Función para liberar la memoria del grafo
void liberar_grafo(Ngrafo*& grafo) {
    Ngrafo* nodo = grafo;
    while (nodo != NULL) {
        Narco* arco = nodo->lista_arco;
        while (arco != NULL) {
            Narco* sig_arco = arco->link;
            delete arco;
            arco = sig_arco;
        }
        Ngrafo* sig_nodo = nodo->link;
        delete nodo;
        nodo = sig_nodo;
    }
    grafo = NULL;
}
