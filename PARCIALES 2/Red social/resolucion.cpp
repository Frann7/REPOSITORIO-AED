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

void display(Persona* p, int contador, string tipo_relacion);
void funcion_C2(Persona* grafo, string tipo_relacion);
void eliminar_relaciones_entrantes(Persona* aux, int id);
void ermitanio(Persona* &grafo, int id);
void ermitanio_v2(Persona* &lista_n, int id);

void display(Persona* p, int contador, string tipo_relacion){
     if(contador > 1){
                cout << "La persona " << p->nombre << " tiene " << contador << " relaciones de tipo " << tipo_relacion << " con las personas: ";
                Relacion* aux_relacion = p->relaciones;
                while(aux_relacion != NULL)
                {
                    if(aux_relacion->tipo == tipo_relacion)
                    {
                        cout << aux_relacion->destino->nombre << ", ";
                    }
                    aux_relacion = aux_relacion->link;
                }
                cout << endl;
            } else if (contador == 0){
                cout << "La persona " << p->nombre << " no tiene relaciones de tipo " << tipo_relacion << endl;
            } else {
                cout << "La persona " << p->nombre << " tiene una relacion de tipo " << tipo_relacion << endl;
            }
        }

void funcion_C2(Persona* grafo, string tipo_relacion = "Amorosa"){

    Persona* aux = grafo;
    int contador = 0;

    while(aux != NULL)
    {
        Relacion* aux_relacion = aux->relaciones;

        while(aux_relacion != NULL)
        {   

            if(aux_relacion->tipo == tipo_relacion)
            {
                contador++;
            }
           
            aux_relacion = aux_relacion->link;
        }
        display(aux, contador, tipo_relacion);
        contador = 0;
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

// 1 forma de hacerlo
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

void ermitanio_v2(Persona* &lista_n, int id){
    
    Persona* aux = lista_n;

    while(aux != NULL)
    {
        if(aux->id_persona == id)
        {
            Relacion* aux_r = aux->relaciones;
            while(aux_r != NULL){

                Relacion* siguiente = aux_r->link;
                delete aux_r;
                aux_r = siguiente;
            }
        }
        aux = aux->link;
    }

    Persona* aux_2 = lista_n;
    eliminar_relaciones_entrantes(aux_2, id);

}


