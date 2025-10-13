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

// generar grafo de ejemplo con una persona que tenga varias relaciones del mismo tipo amorosa
Persona* generar_grafo_ejemplo()
{
    Persona* p1 = new Persona{1, "Alice", "F", "Soltera", NULL, NULL};
    Persona* p2 = new Persona{2, "Bob", "M", "Soltero", NULL, NULL};
    Persona* p3 = new Persona{3, "Charlie", "M", "Casado", NULL, NULL};
    Persona* p4 = new Persona{4, "Diana", "F", "Soltera", NULL, NULL};

    // Relaciones de Alice
    p1->relaciones = new Relacion{101, "Amorosa", p2, new Relacion{102, "Amorosa", p3, NULL}};
    
    // Relaciones de Bob
    p2->relaciones = new Relacion{201, "Amorosa", p1, new Relacion{202, "Amorosa", p4, NULL}};
    
    // Relaciones de Charlie
    p3->relaciones = new Relacion{301, "Amorosa", p1, NULL};
    
    // Relaciones de Diana
    p4->relaciones = new Relacion{401, "Amorosa", p2, NULL};

    // Enlazar personas
    p1->link = p2;
    p2->link = p3;
    p3->link = p4;

    return p1; // Retorna la cabeza del grafo (Alice)
  
}