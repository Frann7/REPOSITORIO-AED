#include <iostream>
#include <algorithm>

using namespace std;

struct nodo_listase
{
int dato;
struct nodo_listase* link;
};
typedef struct nodo_listase NListaSE;

//  -- EJERCICIO 1 --

void mostrarLista(NListaSE* lista) {
    std::cout << "L -> "; 
    NListaSE* aux = lista; // Usamos un auxiliar para recorrer

    while (aux != NULL) {
        std::cout << aux->dato << " -> "; 
        aux = aux->link; // Avanzamos al siguiente nodo
    }

    std::cout << "NULL" << std::endl; 
}

void cargarListaDesdeVector(NListaSE*& lista, int v[], int tam) {
    
    // Nos aseguramos de que la lista comience vacía 
    lista = NULL; 
    NListaSE* ultimo = NULL; // Puntero auxiliar para el último nodo

    for (int i = 0; i < tam; i++) {
        // 1. Crear el nuevo nodo
        NListaSE* nuevo = new NListaSE;
        nuevo->dato = v[i];
        nuevo->link = NULL;

        // 2. Enganchar el nodo a la lista
        if (lista == NULL) {
            // Si es el primer nodo, la 'lista' apunta a él
            lista = nuevo;
        } else {
            // Si no, el 'link' del que era 'ultimo' apunta al nuevo
            ultimo->link = nuevo;
        }

        // 3. Actualizar el puntero 'ultimo'
        ultimo = nuevo;
    }
}

//  -- EJERCICIO 2 --

float obtenerPromedio(NListaSE* lista) {
    
    // 1. Manejo de lista vacía
    if (lista == NULL) {
        return 0.0; // No hay elementos, el promedio es 0
    }

    // 2. Variables para el cálculo
    float sumaTotal = 0.0;
    int contador = 0;
    NListaSE* aux = lista; // Puntero auxiliar para recorrer

    // 3. Recorremos la lista
    while (aux != NULL) {
        sumaTotal += aux->dato; // Sumamos el valor
        contador++;             // Contamos el nodo
        aux = aux->link;        // Avanzamos
    }

    // 4. Retornamos el promedio (la 'sumaTotal' como float fuerza la división flotante)
    return sumaTotal / contador;
}

// -- EJERCICIO 3 --

void duplicarValores(NListaSE* lista) {
    
    NListaSE* aux = lista; // Puntero auxiliar para recorrer

    while (aux != NULL) {
        aux->dato = aux->dato * 2; // Duplicamos el valor
        aux = aux->link;           // Avanzamos al siguiente
    }
}

// -- EJERCICIO 4 --

int obtenerMaximoIterativo(NListaSE* lista) {
    
    // 1. Manejo de lista vacía
    if (lista == NULL) {
        return -1; 
    }

    // 2. Iniciamos el máximo con el primer valor
    int maxValor = lista->dato;
    NListaSE* aux = lista->link; // Empezamos a recorrer desde el *segundo*

    // 3. Recorremos el resto de la lista
    while (aux != NULL) {
        if (aux->dato > maxValor) {
            maxValor = aux->dato; // Encontramos un nuevo máximo
        }
        aux = aux->link; // Avanzamos
    }

    // 4. Retornamos el resultado
    return maxValor;
}

int obtenerMinimoIterativo(NListaSE* lista) {
    
    // 1. Manejo de lista vacía
    if (lista == NULL) {
        return -1; 
    }

    // 2. Iniciamos el mínimo con el primer valor
    int minValor = lista->dato;
    NListaSE* aux = lista->link; // Empezamos a recorrer desde el segundo

    // 3. Recorremos el resto de la lista
    while (aux != NULL) {
        if (aux->dato < minValor) {
            minValor = aux->dato; // Encontramos un nuevo mínimo
        }
        aux = aux->link; // Avanzamos
    }

    // 4. Retornamos el resultado
    return minValor;
}

int obtenerMaximoRecursivo(NListaSE* lista) {
    
    // 1. Caso Base: La lista (o el resto de ella) está vacía
    if (lista == NULL) {
        return -1;
    }

    // 2. Caso Recursivo:
    // Obtenemos el máximo del resto de la lista
    int maxDelResto = obtenerMaximoRecursivo(lista->link);

    // Comparamos el dato actual con el máximo del resto
    return std::max(lista->dato, maxDelResto);
}

// -- EJERCICIO 6 --

void eliminarLista(NListaSE*& lista) {
    
    NListaSE* aux; // Puntero auxiliar para no perder la referencia

    while (lista != NULL) {
        aux = lista;         // 1. Guardamos el nodo actual
        lista = lista->link; // 2. Avanzamos la cabeza al siguiente
        delete aux;          // 3. Eliminamos el nodo guardado
    }

    // Al salir del bucle, 'lista' ya es NULL, reflejando la situación 
}

// -- EJERCICIO 7 --

void mostrarSuperioresAlPromedio(NListaSE* lista) {
    
    // 1. Obtenemos el promedio de la lista
    //    Usamos la función que ya definimos (Ejercicio 2)
    float promedio = obtenerPromedio(lista);

    // 2. Manejamos el caso de lista vacía (promedio 0, nada que mostrar)
    if (lista == NULL) {
        std::cout << "La lista esta vacia, no hay valores para mostrar." << std::endl;
        return;
    }

    std::cout << "Valores que superan el promedio (" << promedio << "):" << std::endl;
    
    NListaSE* aux = lista; // Puntero auxiliar para recorrer
    bool encontrados = false;

    // 3. Recorremos la lista comparando
    while (aux != NULL) {
        // Comparamos el dato (int) con el promedio (float)
        if (aux->dato > promedio) {
            std::cout << "- " << aux->dato << std::endl;
            encontrados = true;
        }
        aux = aux->link; // Avanzamos
    }

    // 4. Mensaje por si ninguno superó el promedio
    if (!encontrados) {
        std::cout << "Ningun valor supera el promedio." << std::endl;
    }
}

// -- EJERCICIO 8 --

bool insertarEnPosicion(NListaSE*& lista, int dato, int pos) {

    // 1. Validar la posición (debe ser > 0)
    if (pos <= 0) {
        std::cout << "Error: Posicion 0 o negativa no es valida." << std::endl;
        return false; 
    }

    // 2. Crear el nuevo nodo
    NListaSE* nuevo = new NListaSE;
    nuevo->dato = dato;
    nuevo->link = NULL;

    // 3. Caso: Inserción al principio (pos = 1)
    if (pos == 1) {
        nuevo->link = lista;
        lista = nuevo;
        return true;
    }

    // 4. Caso: Inserción en medio o al final (pos > 1)
    
    // Necesitamos un puntero al nodo ANTERIOR a la posición de inserción
    NListaSE* anterior = lista;
    int posActual = 1;
    
    // Avanzamos 'anterior' hasta la posición (pos - 1)
    // (Si pos=3, avanzamos i=1. 'anterior' queda en el nodo 2)
   while (posActual < (pos - 1) && anterior != NULL) {
        anterior = anterior->link;
        posActual++;
    }

    // 5. Validar si la posición excede el tamaño
    // Si 'anterior' es NULL, significa que 'pos' fue mayor que (tamaño + 1)
    if (anterior == NULL) {
        std::cout << "Error: La posicion excede el tamanio de la lista." << std::endl;
        delete nuevo; // Liberamos el nodo que no se usó
        return false;
    }

    // 6. Enganchar el nodo
    nuevo->link = anterior->link;
    anterior->link = nuevo;
    return true;
}

// -- EJERCICIO 9 --

bool estaOrdenadaAscendenteIterativo(NListaSE* lista) {
    // Una lista vacía o de un solo elemento se considera ordenada
    if (lista == NULL || lista->link == NULL) {
        return true;
    }

    NListaSE* aux = lista;

    // Recorremos mientras queden al menos dos nodos por comparar
    while (aux->link != NULL) {
        // Si el actual es MAYOR que el siguiente, no está ordenada
        if (aux->dato > aux->link->dato) {
            return false;
        }
        aux = aux->link; // Avanzamos
    }

    // Si salimos del bucle, es porque nunca se rompió el orden
    return true;
}

bool estaOrdenadaDescendenteRecursivo(NListaSE* lista) {
    
    // 1. Caso Base: Lista vacía o de un solo elemento
    // Se consideran ordenadas.
    if (lista == NULL || lista->link == NULL) {
        return true;
    }

    // 2. Caso Recursivo:
    // Comparamos el nodo actual con el siguiente
    if (lista->dato < lista->link->dato) {
        // Si el actual es MENOR que el siguiente, no está ordenada
        return false;
    }

    // Si el orden se mantiene, verificamos el resto de la lista
    return estaOrdenadaDescendenteRecursivo(lista->link);
}

bool estaOrdenada(NListaSE* lista) {
    // La lista está ordenada si está ordenada ascendente
    // O si está ordenada descendente.
    return estaOrdenadaAscendenteIterativo(lista) || 
           estaOrdenadaDescendenteRecursivo(lista);
}