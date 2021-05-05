#include "lista.h"

lista_t* lista_crear()
{
    lista_t* lista = calloc(1,sizeof(lista_t));

    if (!lista) return NULL;
    //lista->cantidad = 0;
    return lista;
}
//O(1)
int lista_insertar(lista_t* lista, void* elemento)
{
    if (!lista)
        return ERROR;

    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo)
        return ERROR;
    
    nodo->elemento = elemento;
    nodo->siguiente = NULL;
    lista->cantidad++;
    
    if (lista->nodo_inicio == NULL)
    {
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
        nodo->siguiente = NULL;
        return OK;
    }
    lista->nodo_fin->siguiente = nodo;
    lista->nodo_fin = nodo;
    lista->nodo_fin->siguiente = NULL;
    return OK;
}
//O(1) O(n)
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion)
{
    if (!lista)
        return ERROR;

    if (lista->nodo_inicio == NULL || posicion >= lista->cantidad) //inserta si esta vacio o si la posicion no existe al final
    {
        lista_insertar(lista, elemento);
        return OK;
    }

    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo)
        return ERROR;

    nodo->elemento = elemento;
    nodo->siguiente = NULL;
    lista->cantidad++;

    if (posicion == 0)
    {
        nodo->siguiente = lista->nodo_inicio; 
        lista->nodo_inicio = nodo;
        return OK;
    }
    //aca partimos de que la posicion a insertar es mayor a 0 y existe
    nodo_t* actual = lista->nodo_inicio;
    int i = 1;
    while (i < posicion)
    {
        actual = actual->siguiente;
        i++;
    }
    nodo->siguiente = actual->siguiente;
    actual->siguiente = nodo;
    return OK;
}
//O(n)
int lista_borrar(lista_t* lista)
{
    if (!lista)
        return ERROR;

    if (lista->nodo_fin != NULL)
    {
        lista->cantidad--;
        free(lista->nodo_fin);
        if (lista->cantidad == 0)
        {
            lista->nodo_inicio = NULL;
            lista->nodo_fin = NULL;
            return OK;
        }
        nodo_t* actual = lista->nodo_inicio;
        int i = 1;
        while (lista->cantidad != i)
        {
            actual = actual->siguiente;
            i++;
        }
        lista->nodo_fin = actual;
        lista->nodo_fin->siguiente = NULL;
        return OK;
    }
    return ERROR;
}
//O(n)
int lista_borrar_de_posicion(lista_t* lista, size_t posicion)
{
    if (!lista)
        return ERROR;

    if (posicion >= lista->cantidad - 1 || lista->nodo_inicio == NULL) //ultimo, si no existe o esta vacia
    { 
        return lista_borrar(lista);
    }
    lista->cantidad--;

    if (lista->cantidad == 0) 
    {
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        return OK;      
    }
    if (posicion == 0)
    {
        nodo_t* actual = lista->nodo_inicio;
        lista->nodo_inicio = lista->nodo_inicio->siguiente;
        free(actual);
        
        return OK;
    }
    nodo_t* anterior = lista->nodo_inicio;
    
    int i = 1;
    while (i < posicion)
    {
        anterior = anterior->siguiente;
        i++;
    }

    nodo_t* actual = anterior->siguiente;
    anterior->siguiente = actual->siguiente;
    free(actual);
    return OK;
}
// O(n) / O(1)
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion)
{
    if (!lista)
        return NULL;

    if (posicion >= lista->cantidad)
        return NULL;

    nodo_t* actual = lista->nodo_inicio;

    int i = 0;
    while (i < posicion)
    {
        actual = actual->siguiente;
        i++;
    }
    return actual->elemento;
}

void* lista_ultimo(lista_t* lista)
{ 
    return lista_elemento_en_posicion(lista,lista_elementos(lista)-1);
}

bool lista_vacia(lista_t* lista)
{
    if (!lista)
        return TRUE;

    if (lista->nodo_inicio != NULL)
        return FALSE;
    
    return TRUE;
}

size_t lista_elementos(lista_t* lista)
{
    if (lista == NULL)
        return OK;
    
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento)
{
    return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista)
{
    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista)
{
    return lista_ultimo(lista);
}
//O(1)
int lista_encolar(lista_t* lista, void* elemento)
{
    return lista_insertar(lista, elemento);
}
//O(1)
int lista_desencolar(lista_t* lista)
{
    return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista)
{
    return lista_elemento_en_posicion(lista, 0);
}

void lista_destruir(lista_t* lista)
{
    if (!lista) return;

    while (!lista_vacia(lista))
    {
        lista_borrar_de_posicion(lista, 0);
    }
    free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista)
{
    if (!lista)
        return NULL;

    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if (!iterador)
        return NULL;

    if (lista->nodo_inicio == NULL)
    {
        iterador->corriente = NULL;
        iterador->lista = lista;
        return iterador;
    }
    iterador->corriente = lista->nodo_inicio;
    iterador->lista = lista;

    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador)
{
    if (!iterador)
        return FALSE;

    if (iterador->corriente == NULL)
        return FALSE;

    return TRUE;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador)
{
    if (!iterador)
        return FALSE;

    if (iterador->corriente == NULL)
    {
        return FALSE;
    }
    if (iterador->corriente->siguiente == NULL)
    {
        iterador->corriente = NULL;
        return FALSE;
    }
    iterador->corriente = iterador->corriente->siguiente;
    return TRUE;
}

void *lista_iterador_elemento_actual(lista_iterador_t* iterador)
{
    if (!iterador)
        return NULL;

    if (iterador->corriente)
        return iterador->corriente->elemento;

    return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador)
{
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void *, void *), void* contexto)
{
    if (!lista || !funcion) return 0;

    if (lista->nodo_inicio == NULL)
        return 0; 
    size_t contador = 1;
    nodo_t* inicio = lista->nodo_inicio;
    void* elemento = lista->nodo_inicio->elemento;
    
    while (funcion(elemento, contexto) && inicio->siguiente != NULL)
    {            
        inicio = inicio->siguiente;
        elemento = inicio->elemento;
        contador++;
    }
    return contador;
}
