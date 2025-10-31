#include <iostream>
#include <string>
#include <queue> 

using namespace std;

// Estructura de datos del cliente
struct Cliente {
    int id_cliente;
    string nombre;  
    string direccion;
    int edad;
    float saldo;
};

// Estructura del nodo de la Lista Doblemente Enlazada
struct NListaDE {
    Cliente* datos; // Puntero a los datos del cliente
    NListaDE* ant; // Puntero al anterior
    NListaDE* sig; // Puntero al siguiente
};

// EJERCICIO A

int contarNodos(NListaDE* lista) {
    int count = 0;
    NListaDE* aux = lista;
    while (aux != NULL) {
        count++;
        aux = aux->sig;
    }
    return count;
}


NListaDE* buscarPorPosicion(NListaDE* lista, int pos) {
    NListaDE* aux = lista;
    for (int i = 1; i < pos; i++) {
        aux = aux->sig;
    }
    return aux;
}


void eliminarNodo(NListaDE*& lista, NListaDE* nodoAEliminar) {
    
    if (nodoAEliminar == NULL) {
        return;
    }

    NListaDE* anterior = nodoAEliminar->ant;
    NListaDE* siguiente = nodoAEliminar->sig;

    // 1. Re-enlazar el nodo anterior (si existe)
    if (anterior != NULL) {
        anterior->sig = siguiente; 
    } else {
        // Si no hay anterior, el nodo a eliminar era la cabeza (lista).
        lista = siguiente;
    }

    // 2. Re-enlazar el nodo siguiente (si existe)
    if (siguiente != NULL) {
        siguiente->ant = anterior;
    }

    // 3. Liberar la memoria del nodo
    delete nodoAEliminar;
}


void eliminarMedio(NListaDE*& lista) {
    
    int count = contarNodos(lista);

    if (count == 0) {
        return;
    }

    // 1. Lógica para cantidad IMPAR
    if (count % 2 != 0) {
        // (Ej: 5 nodos -> (5+1)/2 = 3er nodo)
        int posMedia = (count + 1) / 2;
        NListaDE* nodoMedio = buscarPorPosicion(lista, posMedia);
        eliminarNodo(lista, nodoMedio);
    } 
    // 2. Lógica para cantidad PAR
    else {
        // (Ej: 6 nodos -> 6/2 = 3er y 4to nodo)
        int posMedia1 = count / 2;
        NListaDE* nodo1 = buscarPorPosicion(lista, posMedia1);
        NListaDE* nodo2 = nodo1->sig; // El segundo medio es el siguiente

        // IMPORTANTE: Eliminamos el segundo (nodo2) primero
        eliminarNodo(lista, nodo2);
        eliminarNodo(lista, nodo1);
    }
}

// EJERCICIO B

// Estructura del nodo del Árbol Binario
struct NABinario {
    int dato;        // La "clave"
    NABinario* iz;
    NABinario* de;
};

// Estructura del nodo de la Cola
// (Es un nodo de LSE que "apunta" a un nodo de árbol)
struct NodoColaArbol {
    NABinario* nodoArbol; // El dato que guardamos
    NodoColaArbol* sig;   // Puntero al siguiente en la cola
};

bool cola_arbol_vacia(NodoColaArbol* frente) {
    return (frente == NULL);
}

void cola_arbol_agregar(NodoColaArbol*& frente, NodoColaArbol*& fondo, NABinario* nodo) {
    
    // 1. Crear el nuevo nodo de cola
    NodoColaArbol* nuevo = new NodoColaArbol;
    nuevo->nodoArbol = nodo;
    nuevo->sig = NULL;

    // 2. Engancharlo
    if (cola_arbol_vacia(frente)) {
        // Si la cola estaba vacía, frente y fondo son el mismo
        frente = nuevo;
    } else {
        // Si no, el 'fondo' actual apunta al nuevo
        fondo->sig = nuevo;
    }
    
    // 3. El nuevo nodo es siempre el nuevo 'fondo'
    fondo = nuevo;
}

NABinario* cola_arbol_obtener(NodoColaArbol*& frente, NodoColaArbol*& fondo) {
    
    // 1. Guardamos el dato a retornar
    NABinario* dato = frente->nodoArbol;

    // 2. Avanzamos la cola
    NodoColaArbol* aux = frente; // Nodo a eliminar
    frente = frente->sig;        // Avanza el puntero 'frente'

    // 3. Caso especial: si la cola quedó vacía
    if (frente == NULL) {
        fondo = NULL; // El 'fondo' también debe ser NULL
    }

    // 4. Liberamos memoria y retornamos el dato
    delete aux;
    return dato;
}

int cola_arbol_tamano(NodoColaArbol* frente) {
    int tam = 0;
    NodoColaArbol* aux = frente;
    while (aux != NULL) {
        tam++;
        aux = aux->sig;
    }
    return tam;
}

// En parcial escrito solo deberiamos programar esta funcion
int contarYMostrarNivel(NABinario* arbol, int nivelBuscado) {
    
    if (arbol == NULL || nivelBuscado < 0) {
        return 0;
    }

    NodoColaArbol* frente = NULL;
    NodoColaArbol* fondo = NULL;

    cola_arbol_agregar(frente, fondo, arbol);
    int nivelActual = 0;

    while (!cola_arbol_vacia(frente)) {
        
        // Contamos cuántos nodos hay en ESTE nivel
        int nodosEnNivel = cola_arbol_tamano(frente); 

        // ¿Es el nivel que buscamos?
        if (nivelActual == nivelBuscado) {
            
            std::cout << "Claves en el nivel " << nivelBuscado << ": ";
            
            // Procesamos (mostramos y contamos) SOLO los nodos de este nivel
            for (int i = 0; i < nodosEnNivel; i++) {
                NABinario* aux = cola_arbol_obtener(frente, fondo);
                std::cout << aux->dato << " ";
                // No encolamos los hijos
            }
            std::cout << std::endl;
            
            // Retornamos la cantidad que contamos
            return nodosEnNivel;
        }

        // Si NO es el nivel, procesamos este nivel
        // y encolamos a sus hijos para el *siguiente* nivel.
        for (int i = 0; i < nodosEnNivel; i++) {
            NABinario* aux = cola_arbol_obtener(frente, fondo);
            
            if (aux->iz != NULL)
                cola_arbol_agregar(frente, fondo, aux->iz);
            if (aux->de != NULL)
                cola_arbol_agregar(frente, fondo, aux->de);
        }
        
        // Avanzamos al siguiente nivel
        nivelActual++;
    }

    // Si salimos del bucle (cola vacía)
    // es porque el nivelBuscado era más profundo que el árbol.
    return 0; 
}