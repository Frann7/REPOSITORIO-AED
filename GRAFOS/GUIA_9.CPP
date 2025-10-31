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

// EJERCICIO 9
Ngrafo* ejercicio9(Ngrafo* grafo, int id_nodo) {

    grafo_conjunto_izquierdo(grafo, id_nodo);
    return grafo;
}

// EJERCICIO 11
Ngrafo* ejercicio11(Ngrafo* grafo) {

    grafo_conjunto_maximal(grafo);
    return grafo;
}

// EJERCICIO 12
Ngrafo* ejercicio12(Ngrafo* grafo) {

    grafo_conjunto_minimal(grafo);
    return grafo;
}

// EJERCICIO 13
bool ejercicio13(Ngrafo* grafo) {

    return grafo_tiene_minimo(grafo);
}

// EJERCICIO 14
Ngrafo* ejercicio14(Ngrafo* grafo, int id_nodo) {

    grafo_ideal_principal_derecho(grafo, id_nodo);
    return grafo;
}

// EJERCICIO 15
bool ejercicio15(Ngrafo* grafo, Ngrafo* grafo2) {

    return grafo_son_isomorfos(grafo, grafo2);
}

// EJERCICIO 17
bool ejercicio17(Ngrafo* grafo, int id_nodo) {

    return grafo_tiene_loop(grafo, id_nodo);
}

// EJERCICIO 18
bool ejercicio18(Ngrafo* grafo, int id_origen, int id_destino) {

    return grafo_existe_arco(grafo, id_origen, id_destino);
}

// EJERCICIO 19
bool ejercicio19(Ngrafo* grafo, int id_nodo) {

    return grafo_nodo_en_ciclo(grafo, id_nodo);
}

// EJERCICIO 20
bool ejercicio20(Ngrafo* grafo) {

    return grafo_es_basico(grafo);
}

char yes_or_no(bool valor) {
    if(valor == 0) return 'N';
    else 
        return 'Y';
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

    auto grafo2 = generar_grafo_ejemplo();

    ejercicio7(grafo2, 4);
    ejercicio8(grafo2, 4);
    ejercicio9(grafo2, 4);

    std::cout << "------------------" << std::endl;

    ejercicio11(grafo2);

    std::cout << "------------------" << std::endl;

    ejercicio12(grafo2);

    std::cout << "------------------" << std::endl;

    char respuesta = yes_or_no(ejercicio13(grafo2));
    std::cout << "El grafo tiene minimo? " << respuesta << std::endl;

    std::cout << "------------------" << std::endl;

    ejercicio14(grafo2, 4);

    std::cout << "------------------" << std::endl;

    respuesta = yes_or_no(ejercicio15(grafo, grafo2));
    std::cout << "Los grafos son isomorfos? " << respuesta << std::endl;

    std::cout << "------------------" << std::endl;

    respuesta = yes_or_no(ejercicio17(grafo2, 5));
    std::cout << "El nodo 5 tiene loop? " << respuesta << std::endl;

    std::cout << "------------------" << std::endl;

    respuesta = yes_or_no(ejercicio18(grafo2, 1, 3));
    std::cout << "Existe un arco entre el nodo 1 y 3? " << respuesta << std::endl;

    std::cout << "------------------" << std::endl;

    respuesta = yes_or_no(ejercicio19(grafo2, 3));
    std::cout << "El nodo 3 esta en un ciclo? " << respuesta << std::endl;

    std::cout << "------------------" << std::endl;

    respuesta = yes_or_no(ejercicio20(grafo2));
    std::cout << "El grafo es basico? " << respuesta << std::endl;

    liberar_grafo(grafo);
    liberar_grafo(grafo2);

    return 0;
}

