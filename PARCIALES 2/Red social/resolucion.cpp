#include <iostream>
#include <string>

using namespace std;

struct Persona;
struct Relacion;

struct Persona{

    int id_persona;
    string nombre;
    string sexo;
    string estado_civil;

    Relacion* relaciones = NULL;
    Persona* link = NULL;

};

struct Relacion{

    int id_arco;
    string tipo;

    Persona* destino = NULL;
    Relacion* link = NULL;

};

void funcion_C2(Persona* grafo, string tipo_relacion = "Amorosa"){

    Persona* aux = grafo;

    while(aux != NULL)
    {
        Relacion* aux_relacion = aux->relaciones;
        Relacion* anterior = NULL;

        while(aux_relacion != NULL)
        {
            if(aux_relacion->tipo == tipo_relacion && anterior == NULL)
            {
                cout << "La persona " << aux->nombre << " tiene relacion de tipo amorosa con: " << endl << aux_relacion->destino->nombre;
                cout << endl;
            }
            if(aux_relacion->tipo == tipo_relacion && anterior != NULL)
            {                
                cout << aux_relacion->destino->nombre;
                cout << endl;
            }

            anterior = aux_relacion;
            aux_relacion = aux_relacion->link;
        }
        aux = aux->link;
    }
}

void eliminar_relaciones_entrantes(Persona* aux, int id){

      while(aux != NULL) {
        Relacion* actual = aux->relaciones;
        Relacion* anterior = NULL;

        while(actual != NULL) {
            if(actual->destino != NULL && actual->destino->id_persona == id) {
                // Eliminar actual
                Relacion* toDelete = actual;
                if(anterior == NULL) {
                    aux->relaciones = actual->link;
                    actual = aux->relaciones;
                } else {
                    anterior->link = actual->link;
                    actual = anterior->link;
                }
                delete toDelete;
            } else {
                anterior = actual;
                actual = actual->link;
            }
        }
      }
}

void ermitanio(Persona* &grafo, int id){

    if(grafo == NULL) return;

    // 1) Encontrar el nodo objetivo
    Persona* objetivo = grafo;
    while(objetivo != NULL && objetivo->id_persona != id) {
        objetivo = objetivo->link;
    }

    if(objetivo == NULL) {
        // No existe la persona con ese id
        return;
    }

    // 2) Eliminar todas las relaciones salientes del nodo objetivo
    Relacion* r = objetivo->relaciones;
    while(r != NULL) {
        Relacion* sig = r->link;
        delete r;
        r = sig;
    }
    objetivo->relaciones = NULL;

    // 3) Recorrer todos los nodos y eliminar relaciones entrantes que apunten al objetivo
    Persona* aux = grafo;
    eliminar_relaciones_entrantes(aux, id);

}

