#include "juego.h" 

#define PARTY 6
#define CAMPOS_ESPERADOS_ENTRENADOR 2
#define CAMPOS_ESPERADOS_POKEMON 5
#define CAMPOS_ESPERADOS_GIMNASIO 4

#define FORMATO_ENTRENADOR "%99[^;];%[^;\n]\n"
#define FORMATO_POKEMON "%99[^;];%[^;];%i;%i;%i\n"
#define FORMATO_GIMNASIO "%99[^;];%[^;];%i;%i\n"


char *leer_linea(char *memoria,int tam_memoria,FILE* archivo)
{
    char *linea_leida = NULL;
    linea_leida = fgets(memoria,tam_memoria,archivo);
    if(!linea_leida) return NULL;

    size_t posicion = strlen(linea_leida);

    if(posicion == 0 || memoria[posicion - 1] != '\n')
    {
        char descartar[1024];
        leer_linea(descartar,1024,archivo);
    }
    memoria[posicion -1] = 0;
    return memoria;
}

void mostrar_menu(menu_t *menu)
{
    char opcion[TAMANIO];
    char *linea_leida = NULL;
    menu->opcion_elegida = 0;
    do
    {   
        for(int i=0; i < menu->cantidad; i++)
        {
            printf("%s\n",menu->texto[i]);
        }
        do
        {   
            printf("\n Introduzca una de las opciones:");
            linea_leida = leer_linea(opcion,TAMANIO,stdin);

        } while (strncmp(linea_leida,menu->opciones[0],1) != 0 && strncmp(linea_leida,menu->opciones[1],1) != 0 && 
                 strncmp(linea_leida,menu->opciones[2],1) != 0 && strncmp(linea_leida,menu->opciones[3],1) != 0 && 
                 strncmp(linea_leida,menu->opciones[4],1) != 0); 
        
        if(strncmp(linea_leida,menu->opciones[0],1) == 0){
            menu->opcion_elegida = 1;
            return;
        }
        if(strncmp(linea_leida,menu->opciones[1],1) == 0){ 
            menu->opcion_elegida = 2;
            return;
        }
        if(strncmp(linea_leida,menu->opciones[2],1) == 0){
            menu->opcion_elegida = 3;
            return;
        }
        if(strncmp(linea_leida,menu->opciones[3],1) == 0){
            menu->opcion_elegida = 4;
            return;
        }
    } while (strncmp(opcion,menu->opciones[4],1) != 0);
    menu->opcion_elegida = 5;
    return;
}

void mostrar_menu_batalla(menu_t *menu)
{
    char opcion[TAMANIO];
    char *linea_leida = NULL;
    menu->opcion_elegida = 0;
    do
    {   
        for(int i=0; i < menu->cantidad; i++)
        {
            printf("%s\n",menu->texto[i]);
        }
        do
        {   
            printf("\n Introduzca una de las opciones:");
            linea_leida = leer_linea(opcion,TAMANIO,stdin);

        } while (strncmp(linea_leida,menu->opciones[0],1) != 0 && strncmp(linea_leida,menu->opciones[1],1) != 0);
        
        if(strncmp(linea_leida,menu->opciones[0],1) == 0){
            menu->opcion_elegida = 1;
            return;
        }
       
    } while (strncmp(opcion,menu->opciones[1],1) != 0);
    menu->opcion_elegida = 2;
    return;
}

void mostrar_menu_victoria_derrota(menu_t *menu)
{
    char opcion[TAMANIO];
    char *linea_leida = NULL;
    menu->opcion_elegida = 0;
    do
    {   
        for(int i=0; i < menu->cantidad; i++)
        {
            printf("%s\n",menu->texto[i]);
        }
        do
        {   
            printf("\n Introduzca una de las opciones:");
            linea_leida = leer_linea(opcion,TAMANIO,stdin);

        } while (strncmp(linea_leida,menu->opciones[0],1) != 0 && strncmp(linea_leida,menu->opciones[1],1) != 0 && strncmp(linea_leida,menu->opciones[2],1) != 0);
        
        if(strncmp(linea_leida,menu->opciones[0],1) == 0){
            menu->opcion_elegida = 1;
            return;
        }
        if(strncmp(linea_leida,menu->opciones[1],1) == 0){ 
            menu->opcion_elegida = 2;
            return;
        }

    } while (strncmp(opcion,menu->opciones[2],1) != 0);
    menu->opcion_elegida = 3;
    return;
}

void *abrir_archivo(const char* ruta_entrada)
{
    FILE *archivo = fopen(ruta_entrada,"r");
    if(!archivo) return NULL;

    return archivo;
}

int pedir_archivos_validos(char **archivos)
{   
    char ruta_archivo[TAMANIO];
    char eleccion[TAMANIO];

    int contador = 0;
    void *archivo_cargado;
    do
    {
        printf("Ingrese un archivo válido <R para salir>:");
        leer_linea(ruta_archivo,TAMANIO,stdin);
        
        if (strcmp(ruta_archivo,"R") == 0) return contador;
        do
        {
            printf("\n¿Quieres reiniciar la carga? <S-N>");
            leer_linea(eleccion,TAMANIO,stdin);
            
            if(strcmp(eleccion,"N") == 0) 
            {   
                if (!verificar_si_existe_archivo(archivos,ruta_archivo,contador))
                    {
                    archivo_cargado = abrir_archivo(ruta_archivo); 
                    if(archivo_cargado != NULL) 
                    {
                        printf("\nArchivo válido guardado :)\n");
                        char *frase = calloc(1,TAMANIO*sizeof(char));
                        strcpy(frase,ruta_archivo);
                        archivos[contador] = frase;
                        printf("%s",archivos[contador]);
                        contador += 1;
                        
                        printf("\nTotal de archivos guardados:%d\n",contador);
                        fclose(archivo_cargado);
                    }    
                    else printf("\nArchivo inválido :(\n");
                    }
                else printf("\nEste archivo ya fue ingresado. Ingrese otro, por favor!\n");
            }
      
        } while (strcmp(eleccion,"S") != 0 && strcmp(eleccion,"N") != 0);
        
    } while(strcmp(ruta_archivo,"R") != 0);
    return contador;
}

void destruir_array_elementos(char **array,int tamanio_array)
{
    if (!array) return;

    for (int i=0;i < tamanio_array;i++)
    {
        free(array[i]);
    }
}

int verificar_si_existe_archivo(char **array,char *elemento,int tamanio_array)
{
    for (int i=0;i < tamanio_array; i++)
    {
        if (strcmp(array[i],elemento) == 0) return true;
    }
    return false;
}


pokemon_t *crear_pokemon()
{
    pokemon_t *pokemon = calloc(1,sizeof(pokemon_t));
    if(!pokemon) return NULL;  
    
    return pokemon;
}

personaje_t *crear_personaje()
{
    personaje_t *personaje = calloc(1,sizeof(personaje_t));
    if(!personaje) return NULL;

    return personaje;
}

entrenador_t *crear_entrenador()
{
    entrenador_t *entrenador = calloc(1,sizeof(entrenador_t));
    if(!entrenador) return NULL;  
    
    return entrenador;
}

gimnasio_t *crear_gimnasio()
{
    gimnasio_t *gimnasio = calloc(1,sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    return gimnasio;
}


/*PERSONAJE*/
personaje_t *crear_personaje_y_guardar_datos(void *archivo) 
{   
    personaje_t *personaje = crear_personaje();
    if (!personaje) return NULL;

    int campos_leidos = fscanf(archivo,FORMATO_ENTRENADOR,personaje->letra,personaje->nombre);
    if(!es_entrenador(campos_leidos,personaje->letra,"E")) 
    {
		free(personaje);
        return NULL;
    }
    return personaje;
}

/*POKEMONES*/
int crear_pokemon_y_guardar_datos(void *archivo,lista_t *lista) 
{   
    pokemon_t *un_pokemon = crear_pokemon();
    if(!un_pokemon) return OK;  
    
    int campos_leidos = fscanf(archivo,FORMATO_POKEMON,un_pokemon->letra,un_pokemon->nombre,&un_pokemon->velocidad,&un_pokemon->defensa,&un_pokemon->ataque);
    if(!es_pokemon(campos_leidos,un_pokemon->letra))
    {
        free(un_pokemon);
        return campos_leidos;
    }
    int resultado = lista_insertar(lista,un_pokemon); 
    if(resultado != OK)
    { 
        free(un_pokemon);
        return OK;
    }
    return campos_leidos; 
}

lista_t *cargar_pokemones(void *archivo)  
{   
    lista_t *lista_pokemon = lista_crear();
    if (!lista_pokemon) return NULL;
    
    int resultado = crear_pokemon_y_guardar_datos(archivo,lista_pokemon);
    
    while(resultado != EOF)
    {     
        resultado = crear_pokemon_y_guardar_datos(archivo,lista_pokemon);
    }
    if (lista_pokemon->cantidad == 0)
    {
        free(lista_pokemon);
        return NULL; 
    }
    return lista_pokemon;
}

personaje_t *cargar_personaje()
{  
    char *archivos[TAMANIO];
    int cantidad = pedir_archivos_validos(archivos);
    if (cantidad == 0)
    {
        printf("\nNo ingreso ningún archivo. Vuelva a intentarlo\n");
        return NULL;
    }
    void *archivo_abierto = abrir_archivo(archivos[0]);
    if(!archivo_abierto) 
    {
        destruir_array_elementos(archivos,cantidad); 
        return NULL;
    }
    personaje_t *un_personaje = crear_personaje_y_guardar_datos(archivo_abierto);
    if(!un_personaje)
    {
        fclose(archivo_abierto);
        destruir_array_elementos(archivos,cantidad); 
        return NULL;
    }
    lista_t *una_lista = cargar_pokemones(archivo_abierto);
    if(!una_lista) 
    {   
        destruir_array_elementos(archivos,cantidad);

        free(un_personaje);
        fclose(archivo_abierto);
        return NULL;
    }
    un_personaje->pokemones = una_lista;
    printf("\nEl personaje principal cargo correctamente\n");

    destruir_array_elementos(archivos,cantidad);
    fclose(archivo_abierto); 
    return un_personaje;
}

void destructor_de_elementos(lista_t *lista) 
{
    if(!lista) return;

    nodo_t *inicio = lista->nodo_inicio;
    void* elemento;
    while(inicio != NULL)
    {
        elemento = inicio->elemento;
        
        free(elemento);
        inicio->elemento = NULL;

        inicio = inicio->siguiente;  
    }
}

//COMPARADOR
int comparar_gimnasios_por_dificultad(void *gym1, void *gym2)
{
    if (((gimnasio_t *)gym1)->dificultad < ((gimnasio_t *)gym2)->dificultad)
        return -1;
    if (((gimnasio_t *)gym1)->dificultad < ((gimnasio_t *)gym2)->dificultad)
        return 1;
    return 0;
}

//DESTRUCTOR
void sacar_elemento(void *elemento)
{
    if (!elemento) return;
    free(elemento);
}

void destructor_de_gimnasios(heap_t *heap)
{
    if (!heap) return;

    for (int i=0; i < heap->tope; i++)
    {
        if (heap->destructor) heap->destructor(heap->vector[i]);
    }
}

void eliminar_entrenadores(lista_t *entrenadores) 
{
    for(size_t i=0;i < entrenadores->cantidad;i++)
    {
        entrenador_t *un_entrenador = lista_elemento_en_posicion(entrenadores,i);
        lista_t *pokemones = un_entrenador->pokemones;
        destructor_de_elementos(pokemones);
        lista_destruir(pokemones);
    }
    destructor_de_elementos(entrenadores);
    lista_destruir(entrenadores);
}

void eliminar_heap(heap_t *un_heap) 
{
    for(int i=0; i < un_heap->tope; i++) 
    {
        gimnasio_t *un_gimnasio = un_heap->vector[i];
        lista_t *entrenadores = un_gimnasio->entrenadores;
        eliminar_entrenadores(entrenadores);
    }
    destructor_de_gimnasios(un_heap); 
    heap_destruir(un_heap);                
}

/*GIMNASIOS*/
heap_t *cargar_gimnasios()
{
    heap_t *gimnasios = heap_crear(comparar_gimnasios_por_dificultad,sacar_elemento); 

    char *archivos[TAMANIO];
    int cantidad = pedir_archivos_validos(archivos);
    if (cantidad == 0) return NULL;
    
    for (int i=0;i<cantidad;i++) //cantidad de archivos
    {
        printf("Archivo %d: %s\n",i+1,archivos[i]);
        void *archivo_abierto = abrir_archivo(archivos[i]);
        if(!archivo_abierto) 
        {
            printf("El archivo no pudo abrirse");
            destruir_array_elementos(archivos,cantidad); 
            return NULL;
        }

        while (!es_fin_archivo(archivo_abierto)) 
        {
            gimnasio_t *un_gimnasio = crear_gimnasio_y_guardar_datos(archivo_abierto); 
            if(un_gimnasio) 
            {
                lista_t *entrenadores = cargar_entrenadores(archivo_abierto);
                if(entrenadores) 
                {
                    un_gimnasio->entrenadores = entrenadores;
                    int resultado = heap_insertar(gimnasios,un_gimnasio);
                    if(resultado == ERROR) free(un_gimnasio);
                }
                else free(un_gimnasio);
            }
        }
        if(gimnasios->tope == 0)
            free(gimnasios);
        
        fclose(archivo_abierto);
    }
    destruir_array_elementos(archivos,cantidad);
    return gimnasios;
}

bool es_fin_archivo(void *archivo)
{
    pokemon_t *un_pokemon = crear_pokemon();
    if (!un_pokemon) return FALSE; 
    
    long posicion_anterior = ftell(archivo); 

    int campos_leidos = fscanf(archivo,FORMATO_POKEMON,un_pokemon->letra,un_pokemon->nombre,&un_pokemon->velocidad,&un_pokemon->defensa,&un_pokemon->ataque);
    if (campos_leidos == ERROR)
    {
        free(un_pokemon);
        return TRUE;
    }
    fseek(archivo,posicion_anterior,SEEK_SET);
    free(un_pokemon);
    return FALSE;
}

gimnasio_t *crear_gimnasio_y_guardar_datos(void *archivo)
{
    gimnasio_t *un_gimnasio = crear_gimnasio();
    if (!un_gimnasio) return NULL;
    
    int campos_leidos = fscanf(archivo, FORMATO_GIMNASIO, un_gimnasio->letra, un_gimnasio->nombre,&un_gimnasio->dificultad,&un_gimnasio->id_funcion);
    if(campos_leidos == ERROR) 
    {
        free(un_gimnasio);
        return NULL;
    }
    if(es_gimnasio(campos_leidos,un_gimnasio->letra)) return un_gimnasio; 
    
	free(un_gimnasio);
    return NULL;
}

/*ENTRENADORES*/
lista_t *cargar_entrenadores(void *archivo) 
{
    lista_t *pila_entrenadores = lista_crear(); 
    if(!pila_entrenadores) return NULL;
    
    int resultado = crear_entrenador_y_guardar_datos(archivo,"L",pila_entrenadores); //2 bien, 0 ignoro, -1 termino, 4 
    if(resultado != CAMPOS_ESPERADOS_ENTRENADOR || resultado == ERROR) //si es G = 4 elimino el anterior G
    {
        free(pila_entrenadores); 
        return NULL; 
    }
    lista_t *cola_de_pokemones = cargar_pokemones_de_entrenador(archivo); 
    if(!cola_de_pokemones)
    {
        free(pila_entrenadores); 
        return NULL;
    }
    entrenador_t *primer_entrenador = lista_tope(pila_entrenadores); 
    primer_entrenador->pokemones = cola_de_pokemones;

    while (resultado != EOF) 
    {     
        resultado = crear_entrenador_y_guardar_datos(archivo,"E",pila_entrenadores); 
        if(resultado == CAMPOS_ESPERADOS_GIMNASIO) return pila_entrenadores;

        if(resultado == CAMPOS_ESPERADOS_ENTRENADOR) 
        {
            cola_de_pokemones = cargar_pokemones_de_entrenador(archivo); 
            if(!cola_de_pokemones) 
            {
                free(lista_tope(pila_entrenadores));
                lista_desapilar(pila_entrenadores); //borra el último entrenador xq no tiene pokemones
            }
            else
            {
                entrenador_t *ultimo_entrenador = lista_tope(pila_entrenadores);
                ultimo_entrenador->pokemones = cola_de_pokemones;
            }
        }
    }
    return pila_entrenadores;
}

int crear_entrenador_y_guardar_datos(void *archivo,char *letra,lista_t *lista) 
{    
    entrenador_t *un_entrenador = crear_entrenador();
    if (!un_entrenador) return OK;
    
    long posicion_anterior = ftell(archivo); 

    int campos_leidos = fscanf(archivo,FORMATO_ENTRENADOR,un_entrenador->letra,un_entrenador->nombre);
    if (campos_leidos == ERROR) 
    {
        free(un_entrenador);
        return ERROR;
    }
    if(es_entrenador(campos_leidos,un_entrenador->letra,letra)) 
    {
        int resultado = lista_apilar(lista,un_entrenador); 
        if(resultado != OK)
        { 
            printf("\nEl entrenador no se pudo insertar.\n");
            free(un_entrenador);
            return OK;
        }
        return campos_leidos; //2
    }     
    
    //vuelvo a la linea anterior para cersiorarme que sea un gymnasio
    gimnasio_t *gym = crear_gimnasio();
    if(!gym) return OK;
    fseek(archivo,posicion_anterior,SEEK_SET);
    campos_leidos = fscanf(archivo,FORMATO_GIMNASIO,gym->letra,gym->nombre,&gym->dificultad,&gym->id_funcion);
    if(es_gimnasio(campos_leidos,gym->letra)) 
    {
        fseek(archivo,posicion_anterior,SEEK_SET);
        free(un_entrenador);
        free(gym);
        return campos_leidos; //4
    }
    free(un_entrenador);
    free(gym);
    return OK; 
}

/*POKEMONES*/
lista_t *cargar_pokemones_de_entrenador(void *archivo) 
{
    lista_t *cola_de_pokemones = lista_crear();
    if (!cola_de_pokemones) return NULL;
    
    int resultado = crear_pokemon_y_guardar_datos_de_entrenadores(archivo,cola_de_pokemones);

    while(resultado != ERROR) //no sea E o G
    {
        if (resultado == CAMPOS_ESPERADOS_ENTRENADOR || resultado == CAMPOS_ESPERADOS_GIMNASIO) 
            resultado = ERROR;
        
        else resultado = crear_pokemon_y_guardar_datos_de_entrenadores(archivo, cola_de_pokemones);
    }

    if (cola_de_pokemones->cantidad == 0) 
    {
        free(cola_de_pokemones); 
        return NULL; 
    }
    return cola_de_pokemones;
}

int crear_pokemon_y_guardar_datos_de_entrenadores(void *archivo,lista_t *lista)
{   
    pokemon_t *un_pokemon = crear_pokemon();
    if (!un_pokemon) return OK; 
    
    long posicion_anterior = ftell(archivo); 

    int campos_leidos = fscanf(archivo,FORMATO_POKEMON,un_pokemon->letra,un_pokemon->nombre,&un_pokemon->velocidad,&un_pokemon->defensa,&un_pokemon->ataque);
    if (campos_leidos == ERROR)
    {
        free(un_pokemon);
        return ERROR;
    }
    if(es_pokemon(campos_leidos,un_pokemon->letra))
    {
        int resultado = lista_encolar(lista,un_pokemon); 
        if(resultado != OK)
        { 
            printf("\nEl pokemon no se pudo insertar.\n");
            free(un_pokemon);
            return OK;
        }
        return campos_leidos; 
    }
    if(es_entrenador(campos_leidos,un_pokemon->letra,"E") || es_gimnasio(campos_leidos,un_pokemon->letra)) 
    {
        fseek(archivo,posicion_anterior,SEEK_SET);
        free(un_pokemon);
        return campos_leidos;
    }
    free(un_pokemon);
    return OK;
}


bool es_pokemon(int campos_leidos,char *letra)
{
    if(campos_leidos == CAMPOS_ESPERADOS_POKEMON && strncmp(letra,"P",1) == 0)
        return TRUE;
    return FALSE;
}

bool es_entrenador(int campos_leidos, char *letra_leida, char* letra) //E o L
{
    if(campos_leidos == CAMPOS_ESPERADOS_ENTRENADOR && strncmp(letra_leida,letra,1) == 0)
        return TRUE;
    return FALSE; 
}

bool es_gimnasio(int campos_leidos,char *letra)
{
    if(campos_leidos == CAMPOS_ESPERADOS_GIMNASIO && strncmp(letra,"G",1) == 0)
        return TRUE;
    return FALSE;
}

bool mostrar_entrenadores(void *elemento,void *cantidad_elementos)
{
    if (elemento && cantidad_elementos) 
    {   
        printf("\n%d.-  %s\n",(*(int*)cantidad_elementos)++,(*(entrenador_t*)elemento).nombre);
        return TRUE;
    }
    return FALSE;
}

bool mostrar_pokemones(void* elemento,void* cantidad_elementos)
{
    if (elemento && cantidad_elementos) 
    {   
        printf("\n%d.-  %s\n",(*(int*)cantidad_elementos)++,(*(pokemon_t*)elemento).nombre);
        return TRUE;
    }
    return FALSE;
}

bool mostrar_hasta_6_pokemones(void* elemento,void* cantidad_elementos)
{
    if (elemento && cantidad_elementos) 
    {   
        if((*(int*)cantidad_elementos) > 6 ) return FALSE;
        printf("\n%d.-  %s\n",(*(int*)cantidad_elementos)++,(*(pokemon_t*)elemento).nombre);
        return TRUE;
    }
    return FALSE;
}

void mostrar_informacion(lista_t *lista,bool (* funcion_mostrar)(void*, void *))
{
    if(!lista || !funcion_mostrar) return;
    int cantidad_elementos = 1;
    lista_con_cada_elemento(lista, funcion_mostrar, (void*)&cantidad_elementos);
    return;
}

/*Muestra todo el gimnasio */
void mostrar_gimnasio(gimnasio_t *un_gimnasio)
{
    printf("\nGIMNASIO: %s\n ",un_gimnasio->nombre);
    printf("\nDificultad:%d\n",un_gimnasio->dificultad);
    printf("\nID_funcion:%d\n",un_gimnasio->id_funcion);
    
    lista_t *entrenadores = un_gimnasio->entrenadores; 
    printf("\nCantidad de entrenadores: %ld\n",entrenadores->cantidad); 
    for(size_t i=0;i < entrenadores->cantidad;i++)
    {
        entrenador_t *un_entrenador = lista_elemento_en_posicion(entrenadores,i);
        printf("ENTRENADOR : %s\n",un_entrenador->nombre);
        mostrar_informacion(un_entrenador->pokemones,mostrar_pokemones);
    }
}

size_t pedir_numero_valido(lista_t *lista) 
{
    size_t opcion;
    do
    {   
        mostrar_informacion(lista,mostrar_pokemones);
        do
        {   
            printf("\n Ingrese una de las opciones <1-%ld> <0 para salir>:",lista->cantidad);
            scanf("%20zu",&opcion);

        }while ((opcion < 1 || opcion > lista->cantidad) && opcion != 0); 
        return opcion;
    } while (opcion != 0);
    return opcion;
}

int intercambiar_pokemones(lista_t *lista_pokemones,size_t posicion)
{
    if(!lista_pokemones) return ERROR;

    if(posicion-1 == 0) return OK;

    pokemon_t *pokemon_elegido = lista_elemento_en_posicion(lista_pokemones,posicion-1);
    if(!pokemon_elegido) return ERROR;

    int resultado = lista_borrar_de_posicion(lista_pokemones,posicion-1);
    if(resultado == ERROR) return ERROR;

    resultado = lista_insertar_en_posicion(lista_pokemones,pokemon_elegido,0);
    if(resultado == ERROR) return ERROR;

    return ERROR;
}

lista_t *seleccionar_pokemones_batalla(lista_t *lista_pokemones)//personaje principal
{
    printf("\nSeleccione uno o más pokemones <0 para salir>\n");
    printf("El último que seleccione aparecerá primero.");
    size_t numero = pedir_numero_valido(lista_pokemones);
    
    while(numero != 0)                   
    {                    
        intercambiar_pokemones(lista_pokemones,numero);
        numero = pedir_numero_valido(lista_pokemones);
    }
    printf("\nPOKEMONES DE BATALLA\n");
    printf("\nEstos son los pokemones seleecionados para la batalla\n");
    mostrar_informacion(lista_pokemones,mostrar_hasta_6_pokemones);
    return lista_pokemones;
}


int sumar_caracteristicas(pokemon_t *pokemon)
{
    if (!pokemon || pokemon->puntos >= 63)
        return ERROR;
    
    pokemon->ataque += 1;
    pokemon->defensa += 1;
    pokemon->velocidad += 1;
    pokemon->puntos += 1;
    return OK;
    
}

pokemon_t *prestar_pokemon(lista_t *lista_pokemones)//personaje principal
{
    printf("\nSeleccione uno pokemon <0 para salir>\n");
    printf("El último que seleccione antes de salir es el pokemon elegido.");
    size_t numero = pedir_numero_valido(lista_pokemones);
    
    pokemon_t *pokemon_elegido = lista_elemento_en_posicion(lista_pokemones,numero);
    return pokemon_elegido;
}

/*Si devuelve 1 gano mi pokemon, si no devuelve -1 y gano el rival */
int batalla_pokemon(pokemon_t *mi_pokemon,pokemon_t *pokemon_rival,int id_funcion)
{
    int ganador;
    if(id_funcion == 1)
        ganador = funcion_batalla_1(mi_pokemon,pokemon_rival); 
                     
    if(id_funcion == 2)
        ganador = funcion_batalla_2(mi_pokemon,pokemon_rival);
                            
    if(id_funcion == 3)
        ganador = funcion_batalla_3(mi_pokemon,pokemon_rival);
                            
    if(id_funcion == 4)
        ganador = funcion_batalla_4(mi_pokemon,pokemon_rival);
                            
    if(id_funcion == 5)
        ganador = funcion_batalla_5(mi_pokemon,pokemon_rival);
    return ganador;
}

int jugar_por_entrenador(personaje_t *personaje, entrenador_t *un_entrenador, int id_funcion)
{    
    size_t contador = 0;
    size_t contador_rival = 0;
    lista_t *pokemones = un_entrenador->pokemones;
    lista_t *mis_pokemones = personaje->pokemones;
    
    pokemon_t *pokemon_rival;
    pokemon_t *mi_pokemon;
    while(contador <= 6 && contador != mis_pokemones->cantidad) //para cuando perdi
    {
        if(contador_rival == pokemones->cantidad)
        {
            printf("\nGANADOR: %s\n",mi_pokemon->nombre);
            return OK;
        }
        pokemon_rival = lista_elemento_en_posicion(pokemones,contador_rival);//primer pokemon 
        mi_pokemon = lista_elemento_en_posicion(mis_pokemones,contador); //lista si pierdo la posicion cambia al sig con un contador
        printf("\n%s VS %s\n",mi_pokemon->nombre,pokemon_rival->nombre);
        printf("\nVelocidad: %d  %d\n",mi_pokemon->velocidad,pokemon_rival->velocidad);
        printf("\nDefensa:   %d   %d\n",mi_pokemon->defensa,pokemon_rival->defensa);
        printf("\nAtaque:    %d   %d\n",mi_pokemon->ataque,pokemon_rival->ataque);

        int ganador = batalla_pokemon(mi_pokemon,pokemon_rival,id_funcion);
        if(ganador == 1) //gane
        {
            contador_rival += 1;
            sumar_caracteristicas(mi_pokemon);
        }
        else contador += 1; //perdi
    }
    printf("\n\nGANADOR: %s\n ",pokemon_rival->nombre);
    return ERROR; //perdi
}

int jugar_entrenadores(lista_t *entrenadores,personaje_t* personaje,int id_funcion)
{
    for(size_t i=entrenadores->cantidad;i > 0;i--)
    {
        entrenador_t *un_entrenador = lista_elemento_en_posicion(entrenadores,i-1);
        int resultado = jugar_por_entrenador(personaje,un_entrenador,id_funcion);
        if(resultado == ERROR) return ERROR;
    }
    return 1;
}

/* Recibe un heap por parámetro, crea otro y mediante se va extrayendo la raiz de uno se lo agrega al otro.*/
heap_t *juego_simular(heap_t *un_heap,personaje_t *un_personaje)
{
    heap_t *simular_heap = heap_crear(comparar_gimnasios_por_dificultad,sacar_elemento);
    
    for (size_t i=0; i < un_heap->tope;i++)
    {
        gimnasio_t *un_gimnasio = heap_elemento_raiz(un_heap); //heap_extraer_raiz();

        mostrar_gimnasio(un_gimnasio);

        int resultado = jugar_entrenadores(un_gimnasio->entrenadores,un_personaje,un_gimnasio->id_funcion);
        if(resultado == ERROR) break; 
       
        if(resultado == 1)
        {
            heap_extraer_raiz(un_heap);
            heap_insertar(simular_heap,un_gimnasio);
        }
        mostrar_gimnasio(un_gimnasio);

    }
    while(!heap_vacio(simular_heap))
    {
        heap_insertar(un_heap,heap_extraer_raiz(simular_heap));
    }
    heap_destruir(simular_heap);
    return un_heap;

}

void vaciar_auxiliar(heap_t *heap,heap_t *aux)
{
    while(!heap_vacio(aux))
    {
        gimnasio_t *gym = heap_extraer_raiz(aux);
        heap_insertar(heap,gym);
    }
}  

void eliminar_pokemones_gym(lista_t *pokemones) //lista
{
    while(!lista_vacia(pokemones))
    {
        free(lista_elemento_en_posicion(pokemones, 0)); //elimina primer elemento
        lista_borrar_de_posicion(pokemones,0);   //elimina primer nodo
    }
    lista_destruir(pokemones);
}