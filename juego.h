#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "batallas.h"
#include "lista.h"
#include "heap_minimal.h"

#define OK 0
#define ERROR -1

#define TAMANIO 50

#define LETRAS 100
#define MAX 5

typedef int (*funcion_batalla)(void *, void *);

typedef struct pokemon
{
  char letra[TAMANIO];
  char nombre[TAMANIO];
  int velocidad;
  int defensa;
  int ataque;
  int puntos;
} pokemon_t;

typedef struct personaje
{
  char letra[TAMANIO];
  char nombre[TAMANIO];
  lista_t *pokemones;
} personaje_t;

typedef struct entrenador
{
  char letra[TAMANIO];
  char nombre[TAMANIO];
  lista_t *pokemones;
} entrenador_t;

typedef struct gimnasio
{
  char letra[TAMANIO];
  char nombre[TAMANIO];
  int dificultad;
  int id_funcion;
  lista_t *entrenadores;
} gimnasio_t;

typedef struct juego
{
  personaje_t *personaje;
  heap_t *gimnasios;
  gimnasio_t *gym_actual;
  bool habilitado;
  entrenador_t *lider_actual;
} juego_t;

typedef struct menu
{
  char *opciones[MAX];
  char texto[MAX][LETRAS];
  int cantidad;
  int opcion_elegida;
} menu_t;

/*Suma las caracteristicas como máximo hasta 63 veces */
int sumar_caracteristicas(pokemon_t *pokemon);

/*Ingreso por parámetro el archivo (o lo escrito por teclado), un puntero de cadena
donde guardar lo leido por fgets y el tamaño máximo de la memoria. La función se
asegura que la linea leida termine en '\0' y no en \n' y lo devuelve.*/
char *leer_linea(char *memoria, int tam_memoria, FILE *archivo);

/* Recibe el nombre de un archivo, si se abrio sin problemas lo devuelve.
   Caso contrario devuelve NULL.*/
void *abrir_archivo(const char *ruta_entrada);

/*Muestra el menu y devuelve la opcion valida que el usuario eligio.
  Caso contrario seguirá preguntado hasta que abandone el menú.*/
void mostrar_menu(menu_t *menu);

void mostrar_menu_batalla(menu_t *menu);

void mostrar_menu_victoria_derrota(menu_t *menu);

/*Recibe una lista y muestra sus elementos */
void mostrar_informacion(lista_t *lista, bool (*funcion_mostrar)(void *, void *));

/*Función que se encarga de pedir archivos válidos al usuario. Una vez que lo hace guarda 
  la ruta del archivo en el array ingresado por parámetro, así hasta que el usuario ingresa 
  la letra "R" de abandonar el menú. Se cierran todos los archivos antes de salir del menú.*/
int pedir_archivos_validos(char **archivos);

/*Destruye los elementos del array de punteros pasados por parámetro.*/
void destruir_array_elementos(char **array, int tamanio_array);

/*Recibe un array y un elemento, devuelve true si el elemento
ya esta en el array. Caso contario devuelve false */
int verificar_si_existe_archivo(char **array, char *elemento, int tamanio_array);

/* Crea un pokemón y lo devuelve. En caso de algún error, devuelve NULL.*/
pokemon_t *crear_pokemon();

/*Crea un entrenador y lo devuelve. En caso de algún error, devuelve NULL. */
entrenador_t *crear_entrenador();

/* Crea un gimnasio y lo devuelve. En caso de algún error, devuelve NULL.*/
gimnasio_t *crear_gimnasio();

//DESTRUCTOR
void sacar_elemento(void *elemento);

/* Recibe un archivo válido, crea el personaje, lee el archivo llenando los campos del personaje, 
   si la cantidad de campos leidos son los esperados y es un archivo de personaje,lo devuelve. 
   En caso contrario, se libera la memoria y devuelve NULL.*/
personaje_t *crear_personaje_y_guardar_datos(void *archivo);

/*Recibe un archivo y una lista, crea un pokemon y lee el archivo guardando los datos del pokemon,
  si todo sale bien (tiene los campos esperados y el pokemon leido comienza con su letra representativa)
  lo agrega a la lista y retorna los campos leidos. En caso contrario, libero la memoria del pokemon y 
  devuelvo -1 en caso de terminar de leer el archivo u otro número (2,4) si no es un pokemon. */
int crear_pokemon_y_guardar_datos(void *archivo, lista_t *lista);

/*Recibe un archivo, crea una lista y va leyendo los campos del archivo creando así una lista de pokemones,
  se verifica que el archivo tenga la cantidad de campos esperados y su letra representativa de pokemon "P"
  hasta llegar al final del archivo, cerrarlo  y devolverlo. Si hubo algún error, lo ignoro y sigo. 
  A menos que la cantidad de pokeones sea 0, en cuyo caso libero la memorio y devuelvo NULL */
lista_t *cargar_pokemones(void *archivo);

/*LLamo a todas las funciones necesarias para cargar el personaje y los pokemones, devuelvo un
  puntero a ese personaje válido creado junto a sus pokemones. */
personaje_t *cargar_personaje();

/* Recibe una lista, elimina todos los elementos de una lista.
  Solo válido para los pokemones del personaje principal*/
void destructor_de_elementos(lista_t *lista);

/* Comparador del HEAP */
int comparar_gimnasios_por_dificultad(void *gym1, void *gym2);

/* Destructor del HEAP */
void sacar_elementos(void *elemento);

/* Recibe un heap, elimina todos los gimnasios del heap.*/
void destructor_de_gimnasios(heap_t *heap);

/* Llama a todas las funciones necesarias para cargar los gimnasios del juego.*/
heap_t *cargar_gimnasios();

/*Función que lee la lines de un archivo, si es fin de archivo TRUE.
  Caso contrario devuelve FALSE y vuelvo a la linea anterior para 
  continuar leyendo la informacion del archivo. */
bool es_fin_archivo(void *archivo);

/*Crea el gimnasio, verifica que sea uno, si es válido lo devuelve, si no devuleve NULL */
gimnasio_t *crear_gimnasio_y_guardar_datos(void *archivo);

/* Recibe un archivo, carga todos los estrenadores que haya en el gimnasio.
   Si hubo algún error devuelve NULL y sigue. Excepto con el líder, si este no existe
   libera la memoria y sigo con el siguiente gimnasio si tiene.*/
lista_t *cargar_entrenadores(void *archivo);

/*Función que recibe un archivo, una letra y el TDA pila. Crea un entrenador válido, si lo es
  lo inserta a la pila. Si es un gimnasio vuelvo al puntero anterior antes de leerlo. 
  En cada caso devuelve la cantidad de campos leidos. 
  Devuelve 0 si ocurrió un error interno o si es una línea a ignorar y libera la memoria.
  Si se llegó al final del archivo devuelve -1*/
int crear_entrenador_y_guardar_datos(void *archivo, char *caracter, lista_t *pila);

/*Recibe un archivo, crea el TDA Cola y carga todos los pokemones siguientes hasta que 
  se encuentra con un entrenador, gimnasio o final de archivo. 
  Si la cola esta vacia o sea el entrenador tenia 0 pokemones, devuelve NULL.
  Ante cualquier error devueleve NULL y libera la memoria.
  Caso contario devuelve la cola de pokemones.*/
lista_t *cargar_pokemones_de_entrenador(void *archivo);

/*Función que recibe un archivo y un TDA Cola. Crea un pokemon y lee sus datos, si son válidos
  lo inserta al TDA y devuelve sus campos leidos.
  Si es un entrenador o un gimnasio, vulevo al puntero anterior para poder volver a leerlo y 
  devuelve la cantidad de campos leidos.
  Si devuelve 0 es una línea a ignorar y libero la memoria antes de salir de la función.
  Devuelve -1 si llego al final del archivo. */
int crear_pokemon_y_guardar_datos_de_entrenadores(void *archivo, lista_t *cola);

/*Muestra los pokemones que se pasan por parámetro.*/
bool mostrar_pokemones(void *elemento, void *cantidad_elementos);

/*Recibe un número y una letra que determinan caracteristicas.
  Devuelve TRUE si coincide con esa caracteristicas.
  Caso contrario devuelve False*/
bool es_pokemon(int campo_leidos, char *letra);

bool es_entrenador(int campos_leidos, char *letra_leida, char *letra);

bool es_gimnasio(int campos_leidos, char *letra);

/*Llama a todas las funciones necesarias para eliminar todos los elementos de los gimnasios.*/
void eliminar_heap(heap_t *un_heap);

void eliminar_entrenadores(lista_t *entrenadores);

/* Recibe una lista y le pide al usuario que ingrese una de las opciones, 
   si es válida lo retorna. Caso contarrio sigue preguntando.*/
size_t pedir_numero_valido(lista_t *lista);

/* Función que recibe una lista y un número cambia de lugar el elemento en esa posicion, poniendolo 
   al principio de la lista. Devuelve 0 si salio todo bien, caso contrario -1.*/
int intercambiar_pokemones(lista_t *lista_pokemones, size_t posicion);

bool mostrar_hasta_6_pokemones(void *elemento, void *cantidad_elementos);

lista_t *seleccionar_pokemones_batalla(lista_t *lista_pokemones);

/*Recibe por parámetro un gimnasio, y lo muestra junto con sus entrenadores y pokemones. */
void mostrar_gimnasio(gimnasio_t *un_gimnasio);

/*Recibe un TDA Cola, crea una cola auxiliar y a medida que desencolo voy agregando los elementos.
  Una vez que termino de mostrarlos, vuelvo a encolar en la Cola de pokemones original.*/
void mostrar_pokemones_gym(lista_t *pokemones);

/*Recibe un TDA Pila, crea una pila auxiliar y a medida que desapilo voy agregando los elementos.
  Llamo a la función mostrar_pokemones_gym para mostrar los pokemones de cada entrenador.
  Una vez que termino de mostrarlos, vuelvo a apilar en la Pila de pokemones original.*/
lista_t *mostrar_entrenadores_gym(lista_t *entrenadores);

bool mostrar_entrenadores(void *elemento, void *cantidad_elementos);

/*Recibo un personaje y un entrenador. Voy peleando pokemon a pokemon hasta que el personaje pierda
  o gane a todos lo pokemones del entrenador. Cada vez que gane aumento +1 sus caracteristicas.
  Si pierde retorna -1 y si gana retorna 0. */
int jugar_por_entrenador(personaje_t *personaje, entrenador_t *un_entrenador, int id_funcion);

int jugar_entrenadores(lista_t *entrenadores,personaje_t* personaje,int id_funcion);

//int batalla_pokemon(personaje_t *un_personaje,gimnasio_t *un_gimnasio);
heap_t *juego_simular(heap_t *un_heap,personaje_t *un_personaje);

/*Si devuelve 1 gano mi pokemon, si no devuelve -1 y gano el rival */
int batalla_pokemon(pokemon_t *mi_pokemon,pokemon_t *pokemone_rival,int id_funcion);

pokemon_t *prestar_pokemon(lista_t *lista_pokemones);

void vaciar_auxiliar(heap_t *heap,heap_t *aux);

void eliminar_pokemones_gym(lista_t *pokemones);
#endif /* __JUEGO_H__ */