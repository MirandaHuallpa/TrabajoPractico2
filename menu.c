#include "juego.h"

menu_t inicio[] =  {{{"E","A","I","S","R"},{"E: Ingresa el archivo del entrenador principal","A: Agrega un gimnasio al árbol de gimnasios",
                        "I: Comienza la partida","S: Simula la partida","R: Regresar"},5}};
menu_t gimnasio[] =  {{{"E","G","C","B","R"},{"E: Muestra al entrenador principal junto a sus Pokémon.",
                        "G: Muestra la información del gimnasio actual.","C: Permite cambiar los Pokémon de batalla.",
                        "B: Realiza la próxima batalla planificada.","R: Regresar"},5}};
menu_t batalla[] = {{{"N","R"},{"N:Proximo Combate","R:Terminar juego"},2}};

menu_t victoria[] = {{{"T","C","N"},{"T: Toma un Pokémon del líder y lo incorpora en los Pokémon obtenidos del jugador.",
                       "C: Permite cambiar los Pokémon de batalla.","N: Próximo gimnasio."},3}}; 

menu_t victoria2[] = {{{"C","N","R"},{"C: Permite cambiar los Pokémon de batalla.","N: Próximo gimnasio.","R: Regresar."},3}}; 

menu_t derrota[] = {{{"C","R","F"},{"C: Permite cambiar los Pokémon de batalla.","R: Reintenta el gimnasio.","F: Finaliza la partida."},3}};

juego_t juego = {NULL,NULL,NULL};
bool elegido = FALSE;

int main()
{       
    heap_t *aux = heap_crear(comparar_gimnasios_por_dificultad,sacar_elemento);
    char opcion;
    char vacio[TAMANIO];
   
    do
    {   
        printf("\n\n BIENVENID@ A LA BATALLA POKEMON \n\n");
        printf("\n  1.Menú de inicio.");
        printf("\n  2.Menú de gimnasio.");
        printf("\n  3.Menú de batalla.");
        printf("\n  4.Menú de Victoria.");
        printf("\n  5.Menú de Derrota.");
        printf("\n  6.Salir.\n");
        
        do
        {   
            printf("\n Introduzca una opción (1-6):");
            scanf("%20s",&opcion);

        } while (opcion < '1' || opcion > '6'); 

        printf("\n");
        fgets(vacio,TAMANIO,stdin);
        
        switch (opcion)
        {   
            case '1': 
                    printf("\n       Menú de Inicio\n");
                    mostrar_menu(inicio); 

                    if(inicio->opcion_elegida == 1) //PERSONAJE PRINCIPAL
                    {
                        printf("\n     AGREGAR ENTRENADOR PRINCIPAL     \n");
                        if(juego.personaje) //si ya existia un personaje lo libero
                        {
                            personaje_t *un_personaje = juego.personaje;
                            destructor_de_elementos(un_personaje->pokemones);
                            lista_destruir(un_personaje->pokemones);
                            free(un_personaje);
                        }
                        personaje_t *un_personaje = cargar_personaje();
                        if(!un_personaje) 
                        {
                            printf("\nEl personaje no existe, intente otra vez.\n");
                            break;
                        }
                        juego.personaje = un_personaje;
                        printf("\nSe creo un PERSONAJE correctamente.\n");
                    } 

                    if(inicio->opcion_elegida == 2) //GIMNASIOS
                    {
                        printf("\n         AGREGAR GIMNASIO      \n");
                        if(juego.gimnasios)
                            eliminar_heap(juego.gimnasios);

                        heap_t *un_heap = cargar_gimnasios();
                        if(!un_heap) 
                        {
                            printf("El heap no existe, intentelo otra vez!");
                            break;
                        }
                        //heap_t *otro_heap = cargar_gym_simular();
                        juego.gimnasios = un_heap;
                        gimnasio_t *un_gimnasio = heap_elemento_raiz(juego.gimnasios);
                        juego.gym_actual = un_gimnasio;
                        printf("\nSe crearon el/los Gimnasio/s correctamente.\n");
                        break;
                    }
                    
                    if(inicio->opcion_elegida == 3) //COMENZAR PARTIDA
                    {
                        printf("\nCOMIENZA LA PARTIDA");
                        printf("\nDirigete al Menú de Batalla\n");
                        break;
                    }

                    if(inicio->opcion_elegida == 4) //SIMULAR
                    {
                        if(!juego.personaje || !juego.gimnasios || !juego.gym_actual)
                        {
                            printf("\nEl juego no tiene un Personaje o Gimnasios. Regrese al Menú de Inicio.\n");
                            break;
                        }
                        printf("\nSIMULAR PARTIDA");  
                        juego_simular(juego.gimnasios,juego.personaje);
                        break;
                    }
                    
            case '2': 
                    if(!juego.personaje || !juego.gimnasios || !juego.gym_actual)
                    {
                        printf("\nEl juego no tiene un Personaje o Gimnasios. Regrese al Men Inicio.\n");
                        break;
                    }

                    printf("\n        Menú de gimnasio    \n\n");
                    mostrar_menu(gimnasio);

                    if(gimnasio->opcion_elegida == 1) //MOSTRAR PERSONAJE
                    {
                        printf("\n        Información del Personaje Principal.\n");
                        if(!juego.personaje)
                        {
                            printf("El personaje principal no existe, intentelo otra vez!");
                            break;
                        }
                        printf("\nNombre:%s\n",juego.personaje->nombre);
                        mostrar_informacion(juego.personaje->pokemones,mostrar_pokemones);
                        break;
                    }
                    
                    if(gimnasio->opcion_elegida == 2) //MOSTRAR GIMNASIO ACTUAL
                    {
                        printf("\n        Información del Gimnasio Actual.\n");
                        if(!juego.gym_actual)
                        {
                            printf("El gimnasio actual no existe, intentelo otra vez!");
                            break;
                        }
                        mostrar_gimnasio(juego.gym_actual);   
                        break; 
                    }

                    if(gimnasio->opcion_elegida == 3) //CAMBIAR POKEMONES
                    {
                        printf("\n  Cambiar los pokemones de batalla\n");
                        printf("\n         CAJA          \n");
                        if(!juego.personaje)
                        {
                            printf("\nEl personaje está vacio. Por favor, ingrese un archivo del personaje antes!!");
                            break;
                        }
                        seleccionar_pokemones_batalla(juego.personaje->pokemones);
                        break;
                    }    
                    
                    if(gimnasio->opcion_elegida == 4) //PROXIMA BATALLA
                    {
                        printf("\nPróxima Batalla\n");
                        //mostrar menu de batalla
                        printf("\nPREPARATE PARA LA BATALLA\n");
                    }
                
            case '3': 
                    if(!juego.personaje || !juego.gimnasios || !juego.gym_actual)
                    {
                        printf("\nFELICIDADES ERES UN MAESTRO POKEMON,GANASTE LA PARTIDA.\n");
                        vaciar_auxiliar(juego.gimnasios,aux); //vuelvo como al principio
                        break;
                    }
                    printf("\n         Menú de batalla\n\n");
                    mostrar_menu_batalla(batalla);

                    if(batalla->opcion_elegida == 1) //PROXIMO COMBATE
                    { 
                        //juego el primer combate
                        
                        int resultado = jugar_entrenadores(juego.gym_actual->entrenadores,juego.personaje,juego.gym_actual->id_funcion);
                        entrenador_t *lider = lista_elemento_en_posicion(juego.gym_actual->entrenadores,0);
                        if(es_entrenador(2,lider->letra,"L"))
                            juego.lider_actual = lider;

                        if(resultado == 1)
                        {
                            printf("\nHAZ GANADO. FELICIDADES. VE AL MENU DE VICTORIA\n");
                            juego.habilitado = TRUE;//ganar
                        }
                        else 
                        {
                            juego.habilitado = FALSE; //perder
                            printf("HAZ PERDIDO. VE AL MENU DE DERROTA");
                        }
                    }
                    break;
            case '4':
                    if(!juego.personaje || !juego.gimnasios || !juego.gym_actual)
                    {
                        printf("\nFELICIDADES ERES UN MAESTRO POKEMON,GANASTE LA PARTIDA.\n");
                        vaciar_auxiliar(juego.gimnasios,aux); //vuelvo como al principio
                        break;
                    }
                    if(juego.habilitado)
                    {
                        printf("\n         MENU DE VICTORIA   \n\n");
                        printf("\nFELICIDADES\n");
                        

                        if(!elegido)
                        {
                            mostrar_menu_victoria_derrota(victoria); 

                            if(victoria->opcion_elegida == 1)
                            {
                                elegido = TRUE;
                                pokemon_t *pok_prestado = prestar_pokemon(juego.lider_actual->pokemones);
                                lista_insertar(juego.personaje->pokemones,pok_prestado);
                                printf("\nPOKEMONES OBTENIDOS\n");
                                mostrar_informacion(juego.personaje->pokemones,mostrar_pokemones);
                            }
                            if(victoria->opcion_elegida == 2)
                            {
                                printf("\n  Cambiar los pokemones de batalla\n");
                                printf("\n         CAJA          \n");
                                seleccionar_pokemones_batalla(juego.personaje->pokemones);
                            }
                            if(victoria->opcion_elegida == 3)
                            {
                                printf("\n  PROXIMA BATALLA\n");
                                heap_t *gym_viejo = heap_extraer_raiz(juego.gimnasios);
                                heap_insertar(aux,gym_viejo);
                                juego.gym_actual = heap_elemento_raiz(juego.gimnasios);

                                printf("Dirigase al MENU DE BATALLA para continuar con el siguiente gimnasio.");
                            }
                        }
                        
                        else
                        {
                            mostrar_menu_victoria_derrota(victoria2);
                            if(victoria2->opcion_elegida == 1)
                            {
                                printf("\n  Cambiar los pokemones de batalla\n");
                                printf("\n         CAJA          \n");
                                seleccionar_pokemones_batalla(juego.personaje->pokemones);
                            }
                            if(victoria2->opcion_elegida == 2)
                            {
                                printf("\n  PROXIMA BATALLA\n");
                                heap_t *gym_viejo = heap_extraer_raiz(juego.gimnasios);

                                heap_insertar(aux,gym_viejo);
                                juego.gym_actual = heap_elemento_raiz(juego.gimnasios);
                                if(!juego.gym_actual)
                                    printf("\nFELICIDADES!! YA NO QUEDAN MAS GIMNASIOS\n");
                                else printf("Dirigase al MENU DE BATALLA para continuar con el siguiente gimnasio.");
                            }

                        }
                    }
                    else printf("HAZ PERDIDO! DIRIGETE AL MENU DE DERROTA");
                    break;
            case '5': 
                    if(!juego.personaje || !juego.gimnasios || !juego.gym_actual)
                    {
                        printf("\nFELICIDADES ERES UN MAESTRO POKEMON,GANASTE LA PARTIDA.\n");
                        vaciar_auxiliar(juego.gimnasios,aux); //vuelvo como al principio
                        break;
                    }

                    //MENU DERROTA
                    if(!juego.habilitado)
                    {
                        printf("\n         MENU DE DERROTA   \n\n");
                        mostrar_menu_batalla(derrota); 
                        if(derrota->opcion_elegida == 1)
                        {
                            printf("\nPOKEMONES OBTENIDOS\n");
                            seleccionar_pokemones_batalla(juego.personaje->pokemones);
    
                        }
                        if(derrota->opcion_elegida == 2)
                        {
                            printf("\nReintentar GYM\n");
                            while(!heap_vacio(aux))
                            {
                                gimnasio_t *gym = heap_extraer_raiz(aux);
                                heap_insertar(juego.gimnasios,gym);
                            }
                            printf("\nPuede volver a jugar el gimnasio actual.\n");  
                        }
                        if(victoria2->opcion_elegida == 3) //FINALIZAR PARTIDA
                        {
                            //libero toda la memoria
                            printf("GRACIAS POR JUGAR!!");
                            if(juego.personaje)
                            {
                                personaje_t *un_personaje = juego.personaje;
                                destructor_de_elementos(un_personaje->pokemones);
                                lista_destruir(un_personaje->pokemones);
                                free(un_personaje);
                            }
                            if(juego.gimnasios)
                                eliminar_heap(juego.gimnasios);
                            if(aux)
                                eliminar_heap(juego.gimnasios);
                            break;
                        }

                    }
                    else printf("\nHAZ GANADO. DIRIGETE A MENU DE VICTORIA\n");
                    break;
        }
    } while (opcion != '6');
    vaciar_auxiliar(juego.gimnasios,aux);

    //eliminar
    if(juego.personaje)
    {
        personaje_t *un_personaje = juego.personaje;
        destructor_de_elementos(un_personaje->pokemones);
        lista_destruir(un_personaje->pokemones);
        free(un_personaje);
    }
    if(juego.gimnasios)
        eliminar_heap(juego.gimnasios);
    if(aux)
        free(aux);
    return 0;
}


