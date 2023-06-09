#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  BTree nuevo = btree_copiar(raiz);

  int a;
  btree_recorrer_bfs(nuevo, imprimir_entero);
  puts("");
  a=btree_sumar(raiz);
  printf("Suma:%d\n", a);
  btree_destruir(raiz);
  btree_destruir(nuevo);

  return 0;
}