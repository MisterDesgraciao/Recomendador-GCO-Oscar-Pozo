# Práctica Sistemas de recomendación. Métodos de Filtrado Colaborativo
## Gestión del Conocimiento en las Organizaciones

- Autor: Óscar Ignacio Pozo Fernández
- Correo: alu0101036526@ull.edu.es
- Fecha: 01-11-2022

## Objetivo
El objetivo de esta prácticas es la de conseguir una implementación de Sistemas de Recomendación basado en Usuarios a través del Método de Filtrado Colaborativo explicado en clase. 

Según las diferentes calificaciones que un grupo de usuarios ha realizado sobre una serie de artículos, podemos predecir las calificaciones de estos usuarios ante artículos que no han calificado. 

## Ejemplo de ejecución
Un ejemplo de ejecución del programa es el siguiente:
`./bin/RecomendadorEXE ./ejemplos/utility-matrix-10-25-3.txt Coseno 3 Simple`

- `/bin/RecomendadorEXE` es el primer argumento. Es el ejecutable, situado en la carpeta `bin`.
- `./ejemplos/utility-matrix-10-25-3.txt` es el segundo argumento. Es el fichero situado en la carpeta `ejemplos` al que vamos a aplicar la predicción. También puede recibir la palabra `Random` como segundo argumento para indicar al programa que escoja un fichero aleatorio del directorio.
- `Coseno` es el tercer argumento. Indica el tipo de método utilizado para calcular la similitud entre usuarios. Acepta una de estas 3 opciones: `Pearson`, `Coseno` y `Euclidea`.
- `3` es el cuarto argumento. Indica el número de vecinos que se usan para la predicción. El valor mínimo debe ser 3, pues menos supondría una predicción poco fiable.
- `Simple` es el quinto y último argumento. Indica el tipo de predicción a usar entre estas dos opciones: `Simple` o `Media`.

Un ejemplo de ejecución es el siguiente:
`./bin/RecomendadorEXE Random Coseno 3 Simple`

Argumentos de ejecución: `Random Coseno 3 Simple`
Fichero seleccionado al azar: `./ejemplos/utility-matrix-10-25-6.txt`

Matriz ratings original:
2 5 3 2 1 3 3 2 3 5 2 - 0 5 1 - 2 1 1 4 0 5 4 4 0 
2 4 3 1 0 2 3 5 2 5 3 1 0 4 1 3 0 2 1 2 5 1 5 2 0 
1 0 3 5 4 1 - 0 4 4 2 4 5 3 4 4 5 1 3 3 2 4 5 3 5 
4 3 5 4 1 1 2 1 4 2 4 1 - 5 3 5 2 5 2 1 1 2 3 0 3 
3 1 2 5 1 0 0 0 0 - 3 0 - 1 3 2 0 - 1 4 5 5 5 4 3 
0 5 5 2 4 4 3 5 1 - 0 3 - 1 1 4 3 5 2 - - 4 4 2 5 
4 4 2 4 5 1 2 5 3 3 3 4 0 5 1 - 3 - 2 1 5 3 2 1 4 
0 3 1 2 1 2 2 0 - 0 4 3 3 3 3 2 5 1 2 0 5 4 1 3 5 
3 4 5 0 4 1 0 1 4 2 1 2 3 0 4 4 2 2 0 4 1 4 0 5 5 
3 1 4 2 5 3 2 3 1 2 3 0 0 0 2 4 1 1 5 4 3 3 0 4 1 

Matriz ratings similitudes:
1 0.999031 0.997991 0.998514 0.998114 0.997492 0.998611 0.998026 0.998387 0.998571 
0.999031 1 0.998222 0.999076 0.998364 0.997865 0.998762 0.998508 0.998477 0.998957 
0.997991 0.998222 1 0.998505 0.998426 0.997517 0.998348 0.998778 0.999019 0.998613 
0.998514 0.999076 0.998505 1 0.998453 0.998603 0.998305 0.998389 0.998681 0.998824 
0.998114 0.998364 0.998426 0.998453 1 0.997427 0.998441 0.99861 0.998372 0.998796 
0.997492 0.997865 0.997517 0.998603 0.997427 1 0.99753 0.998001 0.998175 0.998119 
0.998611 0.998762 0.998348 0.998305 0.998441 0.99753 1 0.998596 0.998226 0.998542 
0.998026 0.998508 0.998778 0.998389 0.99861 0.998001 0.998596 1 0.998657 0.998698 
0.998387 0.998477 0.999019 0.998681 0.998372 0.998175 0.998226 0.998657 1 0.99917 
0.998571 0.998957 0.998613 0.998824 0.998796 0.998119 0.998542 0.998698 0.99917 1 

Matriz con las predicciones realizadas:
2 5 3 2 1 3 3 2 3 5 2 1 0 5 1 3 2 1 1 4 0 5 4 4 0 
2 4 3 1 0 2 3 5 2 5 3 1 0 4 1 3 0 2 1 2 5 1 5 2 0 
1 0 3 5 4 1 1 0 4 4 2 4 5 3 4 4 5 1 3 3 2 4 5 3 5 
4 3 5 4 1 1 2 1 4 2 4 1 0 5 3 5 2 5 2 1 1 2 3 0 3 
3 1 2 5 1 0 0 0 0 1 3 0 0 1 3 2 0 2 1 4 5 5 5 4 3 
0 5 5 2 4 4 3 5 1 2 0 3 1 1 1 4 3 5 2 2 1 4 4 2 5 
4 4 2 4 5 1 2 5 3 3 3 4 0 5 1 2 3 1 2 1 5 3 2 1 4 
0 3 1 2 1 2 2 0 3 0 4 3 3 3 3 2 5 1 2 0 5 4 1 3 5 
3 4 5 0 4 1 0 1 4 2 1 2 3 0 4 4 2 2 0 4 1 4 0 5 5 
3 1 4 2 5 3 2 3 1 2 3 0 0 0 2 4 1 1 5 4 3 3 0 4 1

Como se puede apreciar, en este ejemplo se ha usado el selector aleatorio. Para más ejemplos, consultar el PDF adjunto en el repositorio.


# Implementación del código
## Lectura de los argumentos
Lo primero que realiza el programa es la lectura de los argumentos pasados en la ejecución. Los imprime por pantalla y los manda a comprobar con la función `comprobarArgumentos()`. Además si hemos introducido `Random` como opción en vez del nombre de un fichero, se llamará a `seleccionarMatrizAleatoria()` para elegir un fichero sobre el que predecir.
![](/capturas/main1.png)

En esta función simplemente comprobamos que los valores adjuntados en la ejecución son los esperados. Si alguno no lo es, abortamos la ejecución y notificamos el fallo por consola.
![](/capturas/comprobarArgumentos.png)

Usando la función `directory_iterator` de `filesytem` (implementado a partir de C++17) podemos leer el nombre de todos los archivos que se encuentran en la carpeta **ejemplos**. Los añadimos todos a un vector y luego generamos un número aleatorio para seleccionar el archivo a predecir.
![](/capturas/seleccionarMatrizAleatoria.png)

A continuación invocamos la función `readFromFile()` que retorna una matriz de *char* que contiene los valores leídos del fichero seleccionado. Después llamamos a `calcularPredicciones()` que recibe la matriz de calificaciones y únicamente retorna un vector de enteros que indica los usuarios que requieren de alguna predicción en sus calificaciones (busca en qué filas hay un '-').

Posteriormente se imprime por pantalla el contenido de la matriz de ratings original, que incluye las calificaciones vacías de los usuarios. Así podemos ver qué valores se van a predecir.
![](/capturas/main2.png)

El siguiente paso es calcular la matriz de similitudes con la función `crearMatrizSimilitudes()` que utiliza `matrizRatings` para crear una estructura del tamaño adecuado donde almacenar los valores de similitud que tiene cada usuario respecto al resto. 

La función `calcularSimilitudes()` se encarga de actualizar `matrizSimilitudes`, pues comienza vacía, a los valores de similitud que tienen los usuarios entre sí, siguiendo la métrica elegida.

Después imprime por pantalla esos valores de similitud calculados.
![](/capturas/main3.png)

La función `calcularSimilitudes()` recibe la matriz de calificaciones, la `matrizSimilitudes` como *referencia* y el `metodo` para calcular la similitud. Dependiendo de este último valor, se calcula el valor de similitud de cada usuario con el resto usando `correlacionPearson()`, `distanciaCoseno()` o `distanciaEuclidea()`.
![](/capturas/calcularSimilitudes.png)

Estas tres funciones son una traducción directa de la fórmula, que se puede encontrar en el PDF o Internet, de cada método a código.
![](/capturas/correlacionPearson.png)
![](/capturas/formula%20Pearson.png)

![](/capturas/distanciaEuclidea.png)
![](/capturas/formula%20euclidea.png)

![](/capturas/distanciaCoseno.png)
![](/capturas/formula%20coseno.png)

La parte final de la función `main` contiene las últimas dos invocaciones. La primera es la función `ejecutar()`, que recibe todos los valores calculados para construir y devolver una `matrizFinal` del mismo tamaño que `matrizRatings` con todos los valores que hacían falta predecir.

Es también mostrada por pantalla y se termina el programa.
![](/capturas/main4.png)

El bucle iterativo de la función `ejecutar()` recorre la fila de calificaciones de los usuarios que necesitan alguna predicción. Una vez que encuentra un '-', calcula el valor a predecir invocando `calcularVecinos()`. Esta función devuelve un vector de pares, que contienen a los vecinos más afines y su valor de similitud.

Por último, se llama a `prediccionSimple()` o `prediccionDiferenciaMedia()` para calcular el valor a predecir y añadirlo a `matrizFinal`.
![](/capturas/ejecutar.png)

La función `calcularVecinos()` lo que hace es seleccionar a los vecinos más afines. Lo primero que hace es ordenar los valores de Similitud de mayor a menos, se queda con los X primeros (número indicado en la ejecución)

Detalles a tener en cuenta son: no puede usarse a sí mismo como referencia ni tampoco puede usar a un vecino afín pero que no haya calificado ese elemento que buscamos predecir.

Así pues, devolvemos en formato de vector de pares a los usuarios más afines que hayan calificado el elemento junto a su valor.
![](/capturas/calcularVecinos.png)

Por último, las funciones `prediccionSimple()` y `prediccionDiferenciaMedia()` son traducciones a código de las fórmulas de los apuntes de clase. Su cometido es calcular la predicción del usuario sobre el item en base a los vecinos más afines. Este valor lo devuelve como *char*.
![](/capturas/prediccionSimple.png)
![](/capturas/formula%20prediccion%20simple.png)


![](/capturas/prediccionMedia.png)
![](/capturas/formula%20prediccion%20media.png)