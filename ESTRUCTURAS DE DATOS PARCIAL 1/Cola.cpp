#include <iostream>

struct nodo_cola
{
 int dato;
 struct nodo_cola* link;
};
typedef struct nodo_cola NCola;


void cola_agregar (NCola* &frete, NCola* &fondo, int ndato);
int cola_obtener (NCola* &frete, NCola* &fondo);
bool cola_vacia (NCola* frete, NCola* fondo);

void cola_agregar(NCola* &frente, NCola* &fondo, int ndato)
{
 NCola* nuevo_nodo = new NCola;
 nuevo_nodo->dato = ndato;
 nuevo_nodo->link = NULL;
 if (frente == NULL)
 {
 frente = nuevo_nodo;
 fondo = nuevo_nodo;
 }
 else
 {
 fondo->link = nuevo_nodo;
 fondo = nuevo_nodo;
 }
}

int cola_obtener(NCola* &frente, NCola* &fondo)
{
 if (frente == NULL)
 {
 std::cout << "ERROR: Cola vacía.\n";
 return -1; // O manejar de otro modo
 }
 NCola* aux = frente;
 int dato = aux->dato;
 frente = frente->link;
 if (frente == NULL)
 fondo = NULL; // Se vació la cola
 delete aux;
 return dato;
}

bool cola_vacia(NCola* frente, NCola* fondo)
{
 return (frente == NULL && fondo == NULL);
}