#ifndef COLA_H
#define COLA_H

// Definición de la estructura de un nodo de la cola
typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la estructura de la cola
typedef struct {
    Nodo* frente;
    Nodo* final;
} Cola;

// Función para crear una nueva cola vacía
Cola* crearCola();

// Función para verificar si la cola está vacía
int colaVacia(Cola* cola);

// Función para insertar un elemento en la cola
void encolar(Cola* cola, void* dato);

// Función para eliminar y obtener el elemento del frente de la cola
void* desencolar(Cola* cola);

// Función para destruir la cola y liberar la memoria
void cola_destruir(Cola* cola);

// Función para visitar todos los elementos de la cola
void cola_visitar(Cola* cola, void (*funcionVisitar)(void* dato));

#endif /* COLA_H */
