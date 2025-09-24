#ifndef LISTAS_DE_ADYACENCIA_H
#define LISTAS_DE_ADYACENCIA_H

// Estructuras del grafo (listas de adyacencia)
struct nodo_arco;
struct nodo_grafo;

struct nodo_grafo{
    int id_nodo;
    nodo_arco* lista_arco;
    nodo_grafo* link;
};
typedef nodo_grafo Ngrafo;

struct nodo_arco{
    int id_arco;
    nodo_arco* link;
    nodo_grafo* destino;
};
typedef nodo_arco Narco;

// Prototipos de funciones
void grafo_agregar_nodo(Ngrafo*& grafo, int id_nodo);
void grafo_agregar_arco(Ngrafo* grafo, int id_nodo_origen, int id_nodo_destinto, int id_arco);
void grafo_eliminar_nodo(Ngrafo*& grafo, int id_nodo);
void grafo_eliminar_arco(Ngrafo*& grafo, int id_nodo_origen, int id_nodo_destino, int id_arco);
int grafo_cantidad_nodos(Ngrafo* grafo);
int grafo_cantidad_arcos(Ngrafo* grafo);
void grafo_nodos_adyacentes(Ngrafo* grafo, int id_nodo);
void grafo_conjunto_derecho(Ngrafo* grafo, int id_nodo);
void grafo_conjunto_izquierdo(Ngrafo* grafo, int id_nodo);
void grafo_ideal_principal_izquierdo(Ngrafo* grafo, int id_nodo);
void grafo_conjunto_maximal(Ngrafo* grafo);
void grafo_conjunto_minimal(Ngrafo* grafo);
bool grafo_tiene_minimo(Ngrafo* grafo);
void grafo_ideal_principal_derecho(Ngrafo* grafo, int id_nodo);
void grafo_tiene_loop(Ngrafo* grafo);
bool grafo_son_isomorfos(Ngrafo* grafo1, Ngrafo* grafo2);
bool grafo_existe_arco(Ngrafo* grafo, int id_origen, int id_destino);
bool grafo_nodo_en_ciclo(Ngrafo* grafo, int id_nodo);
bool grafo_es_basico(Ngrafo* grafo);


Ngrafo* generar_grafo_ejemplo();
void imprimir_grafo(Ngrafo* grafo);
void liberar_grafo(Ngrafo*& grafo);

#endif // LISTAS_DE_ADYACENCIA_H
