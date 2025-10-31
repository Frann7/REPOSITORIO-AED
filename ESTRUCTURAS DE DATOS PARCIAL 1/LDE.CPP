#include <iostream>

using namespace std;

struct nodo_listade
{
 int dato;
 struct nodo_listade* ant;
 struct nodo_listade* sig;
};
typedef struct nodo_listade NListaDE;

void listade_mostrar (NListaDE* listade);
void listade_agregar_final (NListaDE* &listade, int ndato);
void listade_agregar_ordenado (NListaDE* &listade, int ndato);
bool listade_eliminar_ocurrencia (NListaDE* &listade, int datoe);
void listade_eliminar_ocurrencias (NListaDE* &listade, int datoe);

void listade_mostrar(NListaDE* listade)
{
 cout << "Lista Doblemente Enlazada:\n\n";
 while (listade != NULL)
 {
 cout << listade->dato << " <-> ";
 listade = listade->sig;
 }
 cout << "NULL\n\n\n";
}

void listade_agregar_final(NListaDE* &listade, int ndato)
{
 NListaDE* nuevo_nodo = new NListaDE;
 nuevo_nodo->dato = ndato;
 nuevo_nodo->sig = NULL;
 nuevo_nodo->ant = NULL;
 if (listade == NULL)
 {
 listade = nuevo_nodo;
 }
 else
 {
 NListaDE* aux = listade;
 while (aux->sig != NULL)
 aux = aux->sig;
 aux->sig = nuevo_nodo;
 nuevo_nodo->ant = aux;
 }
}

void listade_agregar_ordenado(NListaDE* &listade, int ndato)
{
 NListaDE* nuevo_nodo = new NListaDE;
 nuevo_nodo->dato = ndato;
 nuevo_nodo->sig = NULL;
 nuevo_nodo->ant = NULL;
 NListaDE* actual = listade;
 while (actual != NULL && actual->dato < ndato)
 actual = actual->sig;
 if (actual == listade)
 {
 // Insertar al inicio
 nuevo_nodo->sig = listade;
 if (listade != NULL)
 listade->ant = nuevo_nodo;
 listade = nuevo_nodo;
 }
 else if (actual == NULL)
 {
 listade_agregar_final(listade, ndato);
 delete nuevo_nodo;
 }
 else
 {
 nuevo_nodo->sig = actual;
 nuevo_nodo->ant = actual->ant;
 actual->ant->sig = nuevo_nodo;
 actual->ant = nuevo_nodo;
 }
}

bool listade_eliminar_ocurrencia(NListaDE* &listade, int datoe)
{
 NListaDE* actual = listade;
 while (actual != NULL && actual->dato != datoe)
 actual = actual->sig;
 if (actual == NULL)
 return false; // no encontrado
 if (actual == listade)
 {
 listade = actual->sig;
 if (listade != NULL)
 listade->ant = NULL;
 }
 else
 {
 if (actual->ant != NULL)
 actual->ant->sig = actual->sig;
 if (actual->sig != NULL)
 actual->sig->ant = actual->ant;
 }
 delete actual;
 return true;
}

void listade_eliminar_ocurrencias (NListaDE* &listade, int datoe)
{
 while (listade_eliminar_ocurrencia (listade, datoe));
}