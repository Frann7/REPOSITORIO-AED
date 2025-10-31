#include <iostream>

using namespace std;

struct nodo_listase
{
 int dato;
 struct nodo_listase* link;
};
typedef struct nodo_listase NListaSE;

void listase_mostrar (NListaSE* listase);
void listase_agregar_final (NListaSE* &listase, int ndato);
void listase_agregar_ordenado (NListaSE* &listase, int ndato);
bool listase_eliminar_ocurrencia (NListaSE* &listase, int datoe);
void listase_eliminar_ocurrencias (NListaSE* &listase, int datoe);

void listase_mostrar (NListaSE* listase)
{
 cout << "Lista Simplemente Enlazada:\n\n";
 while (listase != NULL)
 {
 cout << listase->dato << " -> ";
 listase = listase->link;
 }
 cout << "NULL\n";
}

void listase_agregar_final (NListaSE* &listase, int ndato)
{
 NListaSE* aux_lse = listase;
 NListaSE* nuevo_nodo = new (NListaSE);
 nuevo_nodo->dato = ndato;
 nuevo_nodo->link = NULL;

 if (aux_lse == NULL)
 listase = nuevo_nodo;
 else
 {
 while (aux_lse->link != NULL)
 aux_lse = aux_lse->link;
 aux_lse->link = nuevo_nodo;
 }
}

void listase_agregar_ordenado (NListaSE* &listase, int ndato)
{
 NListaSE* actual = listase;
 NListaSE* anterior = NULL;
 NListaSE* nuevo_nodo = new (NListaSE);
 nuevo_nodo->dato = ndato;

 while (actual != NULL && actual->dato < ndato)
 {
 anterior = actual;
 actual = actual->link;
 }

 if (anterior == NULL)
 {
 nuevo_nodo->link = listase;
 listase = nuevo_nodo;
 } else
 {
 nuevo_nodo->link = anterior->link;
 anterior->link = nuevo_nodo;
 }
}

bool listase_eliminar_ocurrencia (NListaSE* &listase, int datoe)
{
 NListaSE* actual = listase;
 NListaSE* anterior = NULL;
 NListaSE* aux = NULL;

 while ((actual != NULL) and (actual->dato != datoe))
 {
 anterior = actual;
 actual = actual->link;
 }

 if ((actual != NULL) and (anterior == NULL))
 {
 aux = actual;
 listase = listase->link;
 delete aux;
 return true;
 } else if ((actual != NULL) and (anterior != NULL))
 {
 aux = actual;
 anterior->link = actual->link;
 delete aux;
 return true;
 }
 return false;
}

void listase_eliminar_ocurrencias (NListaSE* &listase, int datoe)
{
 while (listase_eliminar_ocurrencia (listase, datoe));
}