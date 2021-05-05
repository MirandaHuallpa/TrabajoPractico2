gcc *.c -o menu -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./menu

Comencé con el menú y a partir de ahi, fui elegiendo la estructura para cada opción y sus funciones a realizar.
Al hacer el menú me aseguré que hubiese una buena interacción con el usuario, y que se le preguntase en los pasos
importantes si está seguro de sus decisiones, para asi poder seguir con el juego, tratando de reutilizar las funciones
ya hechas lo más posible.
Después de terminar el primer menú(Menú de Inicio) y el ingreso de los datos y creación del Entrenador Principal, corri valgrind
y me saltaron muchos errores. Tuve que cambiar casi por completo la función de mostrar_menú, y en vez de pasar por parámetro un vector
bidimensional, hice un struct de menu con los campos necesarios (el texto a mostrar, las opciones, la cantidad y la opcion elegida
por el ususario). En este punto, trate de muchas maneras, asignar la opcion elegida por el usuario como una letra, pero lo termine
cambiando por un número (siendo la primera opcion "E" igual a 1 y asi sucesivamente).

Para la interacción con el usuario, realice la función de pedir_archivos_válidos, donde todas las rutas se guarda en el vector
y lo cierra antes de pedir el siguiente archivo. Al salir devuelve el array de archivos ingresados por el usuario.

La interacción con el usuario comienza, ingresando un archivo de personaje principal y de gimnasios. En ambas tenes la opción de ingresar
cuantos archivos válidos quieras, pero en el caso del Personaje Principal sólo tomará en cuenta el primer archivo que se ingrese, mientras 
que para los gimnasios tomará todos los archivos válidos ingresados. Si se ingresara otro vez un archivo nuevo, ya sea de Personaje principal
o de Gimnasios, el juego se quedaría con el último ingresado y se reiniciaria desde el comienzo.
Para ingresar a las opciones del Menú se deberá hacer en orden, es decir, si fuiste a la segunda opción, y queres ir después a la primera
se volverá automaticamente al Menú de inicio.

Para cargar la información de los pokemones del entrenador principal(personaje) elegí el TDA lista,porque necesitaré poder 
acceder a cada uno de ellos sin importar donde esten (al inicio, al final o al medio),cosa que con el TDA cola o pila no podria 
(ya que en el primero solo accedo al nodo del inicio y en el segundo solo accedo al último -tope).
Y para cuando el entrenador principal quiera elegir otros pokemones de la CAJA, cambiarlo fácilmente.

Por otro lado, para cargar los pokemones de los entrenadores elegí el TDA Cola ya que hasta ahora entiendo que 
sus pokemones aparecerán en la batalla en el orden en que fueron leidos. Teniendo cuidado de usar sólo las funciones del TDA Cola.
Una vez que llegue a la realización del flujo del programa para las batallas, me di cuenta que no me conviene usar el TDA Cola para los
pokemones de los entrenadores, ya que para cada batalla al ser una cola tendria que desencolar para jugar con el siguiente pokemon,
y eso no conviene ya que si el pokemon del personaje pierde tendria que poder volver a jugar con ese pokemon. Y con una lista podria 
acceder directamente al siguiente pokemon sin necesidad de eliminarlo.

Para cargar los entrenadores de los gimnasios, elegí el TDA pila, ya que aparecerán en las batallas primero los entrenadores y a lo último 
el líder. En todos los casos, para que se cargue correctamente el gimnasio debe tener por lo menos: un líder y un pokemon cada uno de los 
entrenadores o por lo menos uno. A falta de tiempo, decido cambiar el TDA PILA por la lista. Si quedó algún nombre de variable por ahi sin
cambiar es por esta razón.

Una vez cargado los gimnasios, en la opción del Menú donde se debe mostrar el gimnasio actual, realice una funcion donde reciba un gimnasio.
Para mostrarlos entrenadores y pokemones (la primera es un Pila y la segunda una Cola), debo crearme una pila auxiliar para ir guardando los 
elementos que voy desapilando para poder mostrarlos. Una vez terminado se vuelve a agregar a la pila original y lo devuelve.
Los mismo con el TDA Cola de los pokemones.
No logré realizar estas funciones, así que decidí tratar el pokemones y los entrenadores como TDA lista.

