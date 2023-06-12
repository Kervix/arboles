#include "btree.h"
#include "cola.c"
#include <assert.h>
#include <stdlib.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
  if (arbol != NULL) {
    if(orden==BTREE_RECORRIDO_PRE) visit(arbol->dato);
    btree_recorrer(arbol->left, orden, visit);
    if(orden==BTREE_RECORRIDO_IN) visit(arbol->dato);
    btree_recorrer(arbol->right, orden, visit);
    if(orden==BTREE_RECORRIDO_POST) visit(arbol->dato);
  }
}


int btree_nnodos(BTree arbol){
  int suma=0;
  if(arbol!=NULL){
    suma++;
    suma+=btree_nnodos(arbol->left);
    suma+=btree_nnodos(arbol->right);
  }
  return suma;
}

int btree_buscar(BTree arbol, int dato){
  int encontrado=0;
  if (!(btree_empty(arbol) || encontrado)){
    if(arbol->dato==dato) encontrado++;
    encontrado=encontrado || btree_buscar(arbol->left, dato) || btree_buscar(arbol->right, dato);
  }
  return encontrado;
}

BTree btree_copiar(BTree arbol){
  BTree nuevoArbol=btree_crear();
  if(!btree_empty(arbol)){
    nuevoArbol=btree_unir(arbol->dato, btree_crear(), btree_crear());
    nuevoArbol->left=btree_copiar(arbol->left);
    nuevoArbol->right=btree_copiar(arbol->right);
  }
  return nuevoArbol;
}

int btree_altura(BTree arbol){
  int altura=-1;
  if(!btree_empty(arbol)){
    altura=1;
    altura+=btree_altura(arbol->left)<btree_altura(arbol->right)?btree_altura(arbol->right):btree_altura(arbol->left);
  }
  return altura;
}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  int nnodos = 0;
  if (!btree_empty(arbol)){
    if(!profundidad) nnodos++;
    profundidad--;
    nnodos+=btree_nnodos_profundidad(arbol->left, profundidad);
    nnodos+=btree_nnodos_profundidad(arbol->right, profundidad);
  }
  return nnodos;
}

int btree_profundidad(BTree arbol, int dato){
  int profundidad=-1;
  if(!btree_empty(arbol)){
    btree_profundidad(arbol->left, dato);
    btree_profundidad(arbol->left, dato);
  }
  return profundidad;
}

int btree_sumar(BTree arbol){
  if(!btree_empty(arbol)){
    int suma=0;
    suma+=arbol->dato;
    suma+=btree_sumar(arbol->left);
    suma+=btree_sumar(arbol->right);
    return suma;
  }
  return 0;
}

// void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void *extra){
//   if(!btree_empty){

//   }
// }

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit){
  Cola *cola=crearCola();
  if (btree_empty(arbol)) return;
  encolar(cola, arbol);
  while(!colaVacia(cola)){
    BTree subarbol=desencolar(cola);
    visit(subarbol->dato);
    if(!btree_empty(subarbol->left)) encolar(cola, subarbol->left);
    if(!btree_empty(subarbol->right)) encolar(cola, subarbol->right);
  }
  cola_destruir(cola);
}