#include <iostream>
#include <string>

using namespace std;

struct router;
struct enlance;

struct router
{
    int codigo;
    string ubicacion;
    int max_conexiones;
    string marca;
    string fecha_compra;

    enlance* enlances;
    router* link;
};

struct enlance
{
    string codigo;
    string tipo;
    int velocidad_max;
    string estado;

    router* destino;
    enlance* link;
};

void conexiones_entrantes(router* lista_n, string estado);

int funcion_C2(router* lista_n, string estado = "Down"){
    
    int contador = 0;
    router* aux = lista_n;

    while(aux != NULL)
    {
        enlance* aux_e = aux->enlances;
        while(aux_e != NULL)
        {
            if(aux_e->estado==estado)
                contador++;

            if(aux_e->destino != NULL)
            {
                cout<<"El enlance "<< aux_e->codigo <<" con estado " <<aux_e->estado << " llega al nodo " << aux_e->destino->codigo;
                cout<<endl;
            }
            aux_e = aux_e->link;
        }
        aux = aux->link;
    }

    router* aux2 = lista_n;
    conexiones_entrantes(aux2, estado)

}