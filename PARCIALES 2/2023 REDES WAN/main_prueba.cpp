#include <iostream>
#include <string>
#include "resolucion.cpp"

router* generar_red_ejemplo();

int main()
{
    router* red = generar_red_ejemplo();

    int resultado = funcion_C2(red, "Down");
    cout << "Cantidad de enlaces Down: " << resultado << endl;

    return 0;
}

// generar red de ejemplo con varios enlaces Down
router* generar_red_ejemplo()
{
    router* r1 = new router{1, "New York", 5, "Cisco", "2020-01-01", NULL, NULL};
    router* r2 = new router{2, "Los Angeles", 4, "Juniper", "2019-05-15", NULL, NULL};
    router* r3 = new router{3, "Chicago", 6, "Huawei", "2021-03-20", NULL, NULL};

    // Enlaces de r1
    r1->enlances = new enlance{"E1", "Fiber", 1000, "Up", r2, new enlance{"E2", "Copper", 100, "Down", r3, NULL}};
    
    // Enlaces de r2
    r2->enlances = new enlance{"E3", "Fiber", 1000, "Down", r1, new enlance{"E4", "Copper", 100, "Up", r3, NULL}};
    
    // Enlaces de r3
    r3->enlances = new enlance{"E5", "Fiber", 1000, "Up", r1, new enlance{"E6", "Copper", 100, "Down", r2, NULL}};

    // Enlazar routers
    r1->link = r2;
    r2->link = r3;

    return r1; // Retorna la cabeza de la red (r1)
}