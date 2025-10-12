#include <iostream>
#include <string>
#include "resolucion.cpp"


Persona* generar_grafo_ejemplo();


int main()
{

    Persona* grafo = generar_grafo_ejemplo();

    funcion_C2(grafo, "Amorosa");

    eliminar_relaciones_entrantes(grafo, 2);

    funcion_C2(grafo, "Amorosa");

    return 0;


}

Persona* generar_grafo_ejemplo()
{
    Persona* grafo = new Persona();
    grafo->id_persona = 1;
    grafo->nombre = "Juan";
    grafo->sexo = "Masculino";
    grafo->estado_civil = "Soltero";

    Persona* persona2 = new Persona();
    persona2->id_persona = 2;
    persona2->nombre = "Maria";
    persona2->sexo = "Femenino";
    persona2->estado_civil = "Soltera";

    Persona* persona3 = new Persona();
    persona3->id_persona = 3;
    persona3->nombre = "Pedro";
    persona3->sexo = "Masculino";
    persona3->estado_civil = "Casado";

    grafo->link = persona2;
    persona2->link = persona3;

    Relacion* relacion1 = new Relacion();
    relacion1->id_arco = 1;
    relacion1->tipo = "Amorosa";
    relacion1->destino = persona2;

    Relacion* relacion2 = new Relacion();
    relacion2->id_arco = 2;
    relacion2->tipo = "Amistad";
    relacion2->destino = persona3;

    grafo->relaciones = relacion1;
    relacion1->link = relacion2;

    return grafo;
}