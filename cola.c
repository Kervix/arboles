#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Función para crear una nueva cola vacía
Cola* crearCola() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->frente = NULL;
    cola->final = NULL;
    return cola;
}

// Función para verificar si la cola está vacía
int colaVacia(Cola* cola) {
    return (cola->frente == NULL);
}

// Función para insertar un elemento en la cola
void encolar(Cola* cola, void* dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    if (colaVacia(cola)) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
}

// Función para eliminar y obtener el elemento del frente de la cola
void* desencolar(Cola* cola) {
    if (colaVacia(cola)) {
        printf("La cola está vacía.\n");
        return NULL;
    }

    Nodo* nodoFrente = cola->frente;
    void* datoFrente = nodoFrente->dato;
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoFrente);
    return datoFrente;
}

// Función para destruir la cola y liberar la memoria
void cola_destruir(Cola* cola) {
    while (!colaVacia(cola)) {
        desencolar(cola);
    }

    free(cola);
}

// Función para visitar todos los elementos de la cola
void cola_visitar(Cola* cola, void (*funcionVisitar)(void* dato)) {
    Nodo* nodoActual = cola->frente;
    while (nodoActual != NULL) {
        funcionVisitar(nodoActual->dato);
        nodoActual = nodoActual->siguiente;
    }
}
