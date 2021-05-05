#ifndef __HEAP_MINIMAL_H__
#define __HEAP_MINIMAL_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 0

#define TRUE 1
#define FALSE 0

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
    void **vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor; 
}heap_t;


/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t *heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
 * Inserta un elemento en el heap al final a la derecha, que es agregarlo al
 * final del vector. Y voy subiendo si el elemento insertado es menor al padre.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int heap_insertar(heap_t *heap,void *elemento);

/* 
 * Devuelve true si el heap está vacío o false en caso contrario.
 */
bool heap_vacio(heap_t* heap);

/*
 * Devuelve el elemento de la raiz, si no tiene devuelve NULL.
 */
void *heap_elemento_raiz(heap_t *heap);

/*
 * Extrae la raiz del heap, y devuelve el elemento.
 * Caso contrario devuelve NULL.
 */
void *heap_extraer_raiz(heap_t *heap);

/*
 * Devuelve la posicion del padre del elemento pasado por parámetro.
 * No admite posicion 0 porque no tiene padre, en ese caso retorna -1.
 */
size_t posicion_padre(size_t n);

/*
 * Recibe una posición y devuelve la posición de su hijo derecho.
 */
size_t posicion_hijo_derecho(size_t n);

/*
 * Recibe una posición y devuelve la posición de su hijo izquierdo.
 */
size_t posicion_hijo_izquierdo(size_t n); //llegue aca

/*
 * Intercambia los elementos en las posiciones pasadas por parámetro.
 */
void swap(void **vector,size_t i,size_t j);

/*
 * Si el elemento insertado es mayor al padre intercambio valor y voy subiendo,
 * hasta que no pueda más, de forma recursiva.
 */
void sift_up(heap_t *heap, size_t n);

/*
 * Recibe un puntero al heap y una posicion, Si el elemento insertado es menor al 
 * padre intercambio valor y voy subiendo, hasta que no pueda más, de forma recursiva.
 */
void sift_down(heap_t *heap, size_t n);

/*
 * Libera la memoria reservada por la heap.
 * No así de sus elementos, para eso tengo el destructor.
 */
void heap_destruir(heap_t *heap);

#endif /* __HEAP_MINIMAL_H__ */