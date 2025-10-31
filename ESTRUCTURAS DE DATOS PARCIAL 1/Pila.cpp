#include <iostream>

struct nodo_pila
{
 int dato;
 struct nodo_pila* link;
};
typedef struct nodo_pila NPila;

void pila_agregar (NPila* &pila, int ndato);
int pila_obtener (NPila* &pila);
bool pila_vacia (NPila* pila);

void pila_agregar(NPila* &pila, int ndato)
{
 NPila* nuevo_nodo = new NPila;
 nuevo_nodo->dato = ndato;
 nuevo_nodo->link = pila;
 pila = nuevo_nodo;
}

int pila_obtener(NPila* &pila)
{
 if (pila == NULL)
 {
 std::cout << "ERROR: Pila vacía.\n";
 return -1; // O manejar de otro modo
 }

 NPila* aux = pila;
 int dato = aux->dato;
 pila = pila->link;
 delete aux;
 return dato;
}

bool pila_vacia(NPila* pila)
{
 return (pila == NULL);
}