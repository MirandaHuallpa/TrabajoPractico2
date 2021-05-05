#include "heap_minimal.h"

heap_t *heap_crear(heap_comparador comparador, heap_liberar_elemento destructor)
{
    heap_t *heap = calloc(1,sizeof(heap_t));
    if(!heap) return NULL;

    heap->comparador = comparador;
    heap->destructor = destructor;
    return heap;
}

int heap_insertar(heap_t *heap,void *elemento)
{
    if(!heap || !elemento || !heap->comparador) return ERROR;

    void *aux = realloc(heap->vector,(size_t)(heap->tope + 1)* sizeof(void*));
    if(!aux) return ERROR;

    heap->tope += 1;
    heap->vector = aux;
    heap->vector[heap->tope - 1] = elemento;

    sift_up(heap,heap->tope - 1);

    return OK;
}

bool heap_vacio(heap_t* heap)
{
    if(!heap) return true;

    return (heap->tope == 0); 
}

void *heap_elemento_raiz(heap_t *heap)
{
    if (!heap || heap->tope == 0) return NULL; 
    
    return heap->vector[0];
}

void *heap_extraer_raiz(heap_t *heap)
{
    if(heap->tope == 0) return NULL; 

    void *valor_raiz = heap->vector[0];

    swap(heap->vector, 0,heap->tope-1); 
    heap->vector[0] = heap->vector[heap->tope -1]; 
    heap->tope -= 1;
    
    if(heap->tope != 0)
        sift_down(heap,0);

    return valor_raiz;
}

void sift_up(heap_t *heap, size_t n)
{
    if (n == 0) return; 

    size_t padre = posicion_padre(n);
    if(padre == ERROR) return;

    if(heap->comparador(heap->vector[n],heap->vector[padre]) < 0) 
    {
        swap(heap->vector, n,padre);
        sift_up(heap,padre);
    }
}

void sift_down(heap_t *heap, size_t n)
{   
    size_t pos_der = posicion_hijo_derecho(n);
    size_t pos_izq = posicion_hijo_izquierdo(n);
    size_t pos_mayor = pos_izq; 

    if (pos_izq >= heap->tope) return; 

    if (pos_der < heap->tope) 
        if(heap->comparador(heap->vector[pos_der],heap->vector[pos_izq]) > 0) 
            pos_mayor = pos_der;

    if(heap->comparador(heap->vector[n],heap->vector[pos_mayor]) > 0) 
    {
        swap(heap->vector, n,pos_mayor);
        sift_down(heap,pos_mayor);
    }
}

size_t posicion_padre(size_t n) 
{
    return (n-1)/2;
}

void swap(void **vector,size_t i,size_t j)
{
    void *aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

size_t posicion_hijo_derecho(size_t n)
{
    return 2*n+2;
}

size_t posicion_hijo_izquierdo(size_t n)
{
    return 2*n+1;
}

void heap_destruir(heap_t *heap)
{
    if(heap)
        free(heap->vector);
    free(heap);
}
