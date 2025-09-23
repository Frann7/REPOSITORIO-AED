#include <iostream>
#include "Listas_de_Adyacencia.cpp"

// EJERCICIO 1

Ngrafo* ejercicio1(){

    Ngrafo* grafo = NULL;


    grafo_agregar_nodo(grafo, 87);
    grafo_agregar_nodo(grafo, 32);
    grafo_agregar_nodo(grafo, 4);
    grafo_agregar_nodo(grafo, 121);
    grafo_agregar_nodo(grafo, 8);

    grafo_agregar_arco(grafo, 87, 4, 81);
    grafo_agregar_arco(grafo, 121, 8, 73);
    grafo_agregar_arco(grafo, 121, 32, 27);
    grafo_agregar_arco(grafo, 121, 87, 85);
    grafo_agregar_arco(grafo, 4, 121, 7);
    grafo_agregar_arco(grafo, 8, 4, 5);

    return grafo;
}

// EJERCICIO 2

Ngrafo* ejercicio2(Ngrafo*& grafo, int id_nodo_origen, int id_nodo_destino, int id_arco){

    grafo_eliminar_arco(grafo, id_nodo_origen, id_nodo_destino, id_arco);

    return grafo;
}

// EJERCICIO 3

void ejercicio3(Ngrafo* grafo){

    imprimir_grafo(grafo);

}

// EJERCICIO 4

Ngrafo* ejercicio4(Ngrafo*& grafo, int id_nodo){

    grafo_eliminar_nodo(grafo, id_nodo);

    return grafo;
}


// EJERCICIO 5

int ejercicio5(Ngrafo*& grafo){ return grafo_cantidad_nodos(grafo);}

// EJERCICIO 6

int ejercicio6(Ngrafo*& grafo){ return grafo_cantidad_arcos(grafo);}

// EJERCICIO 7

Ngrafo* ejercicio7(Ngrafo* grafo, int id_nodo) {

    grafo_nodos_adyacentes(grafo, id_nodo);
    return grafo;

}

// EJERCICIO 8

Ngrafo* ejercicio8(Ngrafo* grafo, int id_nodo) {

    grafo_conjunto_derecho(grafo, id_nodo);
    return grafo;

}

// MAIN para probar los ejercicios
int main(){
    
    auto grafo = ejercicio1();

    imprimir_grafo(grafo);
    std::cout << "------------------" << std::endl;

    std::cout << "Cantidad de arcos: " << ejercicio6(grafo) << std::endl;
    std::cout << "Cantidad de nodos: " << ejercicio5(grafo) << std::endl;

    std::cout << "------------------" << std::endl;

    ejercicio3(ejercicio2(grafo, 121, 32, 27));

    std::cout << "------------------" << std::endl;

    imprimir_grafo(ejercicio4(grafo, 4));

    std::cout << "------------------" << std::endl;

    std::cout << "Cantidad de nodos luego de la eliminacion: " << ejercicio5(grafo) << std::endl;
    std::cout << "Cantidad de arcos luego de la eliminacion: " << ejercicio6(grafo) << std::endl;

    std::cout << "------------------" << std::endl;

    ejercicio7(grafo, 121);

    std::cout << "------------------" << std::endl;

    ejercicio8(grafo, 121);

    return 0;
}