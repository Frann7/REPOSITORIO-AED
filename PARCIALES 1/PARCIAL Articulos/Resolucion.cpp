#include <iostream>
#include <string>


// El dato que guardamos
struct Articulo {
    int codigo_articulo;
    std::string rubro;
    std::string descripcion;
    float precio;
};

// --- Estructuras de las colecciones ---

// Nodo para la Lista Simplemente Enlazada
struct NodoLSE {
    Articulo* dato;
    NodoLSE* sig; // 'siguiente'
};

// Nodo para la Pila Dinámica
struct NodoPila {
    Articulo* dato;
    NodoPila* sig; // 'siguiente'
};


bool pila_vacia(NodoPila* pila) {
    return (pila == NULL);
}

void pila_agregar(NodoPila*& pila, Articulo* dato) {
    // 1. Crear el nuevo nodo
    NodoPila* nuevo = new NodoPila;
    nuevo->dato = dato;
    
    // 2. Apuntar al que era el primero
    nuevo->sig = pila;
    
    // 3. El nuevo nodo es ahora el primero (la cima)
    pila = nuevo;
}

void procesarArticulos(NodoLSE*& lista, NodoPila*& pila) {

    NodoLSE* actual = lista;
    NodoLSE* anterior = NULL; // Puntero al nodo previo

    while (actual != NULL) {

        bool cumpleCondicion = (actual->dato->rubro == "Relojeria" &&
                                actual->dato->precio < 500);

        // Si NO cumple, solo avanzamos
        if (!cumpleCondicion) {
            anterior = actual;
            actual = actual->sig;
        } 
        
        // Si SÍ cumple, hay que moverlo
        else {
            // 1. Copiamos el artículo y le subimos el precio
            Articulo* artModificado = actual->dato;
            artModificado->precio = artModificado->precio * 1.15; // Aumento 15%

            // 2. Lo agregamos a la Pila
            pila_agregar(pila, artModificado);

            // 3. Lo eliminamos de la LSE
            NodoLSE* nodoAEliminar = actual;

            if (anterior == NULL) {
                // Caso A: Estamos eliminando el PRIMER nodo de la lista
                lista = actual->sig;    // La lista ahora empieza en el siguiente
                actual = lista;         // El 'actual' para el bucle es el nuevo primero
            } else {
                // Caso B: Estamos eliminando un nodo del MEDIO o FINAL
                anterior->sig = actual->sig; // El 'anterior' saltea al nodo eliminado
                actual = actual->sig;        // El 'actual' para el bucle es el siguiente
            }

            // 4. Liberamos la memoria del nodo LSE
            delete nodoAEliminar;
        }
    }
}

// EJERCICIO B


// El dato que guardamos en el árbol
struct ArticuloABB {
    int codigo;
    std::string nombre_articulo;
    float precio;
};

// Estructura del nodo del Árbol Binario de Búsqueda
struct NodoABB {
    ArticuloABB dato;
    NodoABB* izq;
    NodoABB* der;
};


void recorrerYContar(NodoABB* nodo, 
                     int& cantHojas, 
                     int& cantSoloIzq, 
                     float& sumaPrecios, 
                     int& totalNodos) {
    
    // --- Caso Base ---
    // Si el nodo es nulo, no hay nada que hacer
    if (nodo == NULL) {
        return;
    }

    // --- Procesar el nodo actual ---
    
    // 1. Contar para el promedio
    totalNodos++;
    sumaPrecios += nodo->dato.precio;

    // 2. Chequear si es hoja
    if (nodo->izq == NULL && nodo->der == NULL) {
        cantHojas++;
    }

    // 3. Chequear si tiene solo hijo izquierdo
    if (nodo->izq != NULL && nodo->der == NULL) {
        cantSoloIzq++;
    }

    // --- Seguir recorriendo (Recursión) ---
    recorrerYContar(nodo->izq, cantHojas, cantSoloIzq, sumaPrecios, totalNodos);
    recorrerYContar(nodo->der, cantHojas, cantSoloIzq, sumaPrecios, totalNodos);
}

void informarDatosABB(NodoABB* arbol) {
    
    // 1. Variables para guardar los resultados
    int cantHojas = 0;
    int cantSoloIzq = 0;
    float sumaPrecios = 0.0;
    int totalNodos = 0;

    // 2. Llamamos a la función recursiva que llena las variables
    recorrerYContar(arbol, cantHojas, cantSoloIzq, sumaPrecios, totalNodos);

    // 3. Calculamos el promedio (cuidando de no dividir por cero)
    float promedio = 0.0;
    if (totalNodos > 0) {
        promedio = sumaPrecios / totalNodos;
    }

    // 4. Mostramos los resultados por pantalla
    std::cout << "--- Reporte del Arbol ---" << std::endl;
    std::cout << "Cantidad de nodos hoja: " << cantHojas << std::endl;
    std::cout << "Promedio de precios: " << promedio << std::endl;
    std::cout << "Cantidad de nodos con solo hijo izquierdo: " << cantSoloIzq << std::endl;
}

bool esArbolCompleto(NodoABB* arbol) {
    
    // 1. Caso Base: Un árbol vacío (NULL)
    // Se considera completo por definición.
    if (arbol == NULL) {
        return true;
    }

    // 2. Caso Hoja: (0 hijos)
    // Si es un nodo hoja, cumple la regla (0 hijos).
    if (arbol->izq == NULL && arbol->der == NULL) {
        return true;
    }

    // 3. Caso Inválido: (1 solo hijo)
    // Si tiene solo hijo izquierdo O solo hijo derecho, no cumple.
    if ((arbol->izq != NULL && arbol->der == NULL) || 
        (arbol->izq == NULL && arbol->der != NULL)) {
        return false;
    }

    // 4. Caso Intermedio: (2 hijos)
    // Si llegamos acá, es porque tiene 2 hijos.
    // El nodo actual cumple la regla, pero ahora debemos
    // verificar que sus hijos TAMBIÉN la cumplan.
    // La función solo será 'true' si AMBOS subárboles son completos.
    return esArbolCompleto(arbol->izq) && esArbolCompleto(arbol->der);
}