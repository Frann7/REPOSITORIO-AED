#include <iostream>
#include <string>

// El dato principal
struct Nino {
    std::string nombreNino;
    std::string nombreTutor;
    int edad;
    float distancia; // "en km"
    std::string telefono;
    std::string salita; // "inicialmente en blanco"
};

// Nodo de la Lista Doblemente Enlazada (LDE)
struct NListaDE {
    Nino dato;
    NListaDE* ant; // Puntero al anterior
    NListaDE* sig; // Puntero al siguiente
};

// Nodo de la Pila (es una LSE simple)
struct NodoPila {
    Nino dato;
    NodoPila* sig;
};

void pila_agregar(NodoPila*& pila, Nino dato) {
    // 1. Crear el nuevo nodo
    NodoPila* nuevo = new NodoPila;
    nuevo->dato = dato;
    
    // 2. Apuntar al que era el primero
    nuevo->sig = pila;
    
    // 3. El nuevo nodo es ahora el primero (la cima)
    pila = nuevo;
}

void eliminarNodoLDE(NListaDE*& lista, NListaDE* nodoAEliminar) {
    
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

void distribuirNinos(NListaDE*& lista, NodoPila*& pilaVerde, NodoPila*& pilaNegra) {
    
    NListaDE* actual = lista;

    while (actual != NULL) {
        
        Nino datoNino = actual->dato; // Copiamos el dato para leerlo
        NListaDE* nodoParaBorrar = NULL; // Marcador

        // Condición Salita Verde: [2, 4) y > 2km
        bool esVerde = (datoNino.edad >= 2 && datoNino.edad < 4 && 
                        datoNino.distancia > 2);

        // Condición Salita Negra: [4, 6) y > 2km
        bool esNegra = (datoNino.edad >= 4 && datoNino.edad < 6 && 
                        datoNino.distancia > 2);

        
        if (esVerde) {
            datoNino.salita = "Verde"; // Actualizamos el campo
            pila_agregar(pilaVerde, datoNino);
            nodoParaBorrar = actual;
        } 
        else if (esNegra) {
            datoNino.salita = "Negra"; // Actualizamos el campo
            pila_agregar(pilaNegra, datoNino);
            nodoParaBorrar = actual;
        }

        // --- Avanzamos ---
        
        // Guardamos el siguiente ANTES de borrar el actual
        NListaDE* siguiente = actual->sig; 

        if (nodoParaBorrar != NULL) {
            // Si marcamos un nodo para borrar, lo eliminamos
            eliminarNodoLDE(lista, nodoParaBorrar);
        }
        
        // Avanzamos al siguiente nodo de la lista original
        actual = siguiente;
    }
}

// EJERCICIO B

// Nodo del Árbol Binario
struct NArbol {
    int codigo; // "código numérico entero"
    NArbol* izq;
    NArbol* der;
};

// Nodo de la Cola (para el recorrido)
struct NodoColaArbol {
    NArbol* nodoArbol; // Guarda un puntero al nodo del árbol
    NodoColaArbol* sig;
};

bool cola_arbol_vacia(NodoColaArbol* frente) {
    return (frente == NULL);
}

void cola_arbol_agregar(NodoColaArbol*& frente, NodoColaArbol*& fondo, NArbol* nodo) {
    NodoColaArbol* nuevo = new NodoColaArbol;
    nuevo->nodoArbol = nodo;
    nuevo->sig = NULL;

    if (cola_arbol_vacia(frente)) {
        frente = nuevo;
    } else {
        fondo->sig = nuevo;
    }
    fondo = nuevo;
}

NArbol* cola_arbol_obtener(NodoColaArbol*& frente, NodoColaArbol*& fondo) {
    NArbol* dato = frente->nodoArbol;
    NodoColaArbol* aux = frente; 
    frente = frente->sig;        

    if (frente == NULL) {
        fondo = NULL; 
    }
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

void mostrarArbolPorNiveles(NArbol* arbol) {
    
    if (arbol == NULL) {
        std::cout << "El arbol esta vacio." << std::endl;
        return;
    }

    // 1. Inicializar la cola
    NodoColaArbol* frente = NULL;
    NodoColaArbol* fondo = NULL;

    // 2. Agregar la raíz (Nivel 0)
    cola_arbol_agregar(frente, fondo, arbol);
    int nivelActual = 0;

    // 3. Mientras queden nodos por procesar...
    while (!cola_arbol_vacia(frente)) {
        
        // (El truco para separar niveles)
        // Contamos cuántos nodos hay en el nivel actual
        int nodosEnNivel = cola_arbol_tamano(frente);

        // Imprimimos el título del nivel
        std::cout << "Nivel " << nivelActual << ": ";

        // 4. Procesamos TODOS los nodos de ESE nivel
        for (int i = 0; i < nodosEnNivel; i++) {
            
            // a. Sacar el nodo de la cola
            NArbol* nodo = cola_arbol_obtener(frente, fondo);
            
            // b. Mostrar su código
            std::cout << nodo->codigo << " ";

            // c. Agregar sus hijos (para el PRÓXIMO nivel)
            if (nodo->izq != NULL) {
                cola_arbol_agregar(frente, fondo, nodo->izq);
            }
            if (nodo->der != NULL) {
                cola_arbol_agregar(frente, fondo, nodo->der);
            }
        }
        
        // 5. Terminamos el nivel
        std::cout << std::endl; // Salto de línea
        nivelActual++;         // Pasamos al siguiente nivel
    }
}