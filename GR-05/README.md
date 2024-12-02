# PROGRAMACIÓN PARALELA CON ALGORITMO GENÉTICO DE OPTIMIZACIÓN

> **Importante** 

## Lista de chequeo

### Documentos

Dentro del directorio [documentos](documentos/) agregar los pdf de:
- [x] Propuesta.
- [x] PDF del reporte escrito en formato IEEE.
- [x] Dispositivas de la presentacion final.


### Archivos y elementos del respositorio

- [x] El repositorio del código implementado con su documentación. 
- [x] Código que incluya todos los recursos relevantes para ejecutar la aplicación desarrollada para resolver el desafío. 
- [x] Explicación de los requisitos del sistema
- [x] Librerias y dependencias necesarias (pasos necesarios para llevar a cabo la instalación)
- [x] Pasos necesarioas para ejecutar la aplicación.
- [x] Ademas del código, es deseable que tenga un Notebook de Jupyter como complemento para la parte estadistica.

## Requisitos para ejecución del código del proyecto
- Python 3.12 o superior.
- JDK 21 o superior.

## Requisitos de hardware
- Procesador multicore.
- RAM 16GB o superior.

## Instrucciones de ejecución
- Si se utiliza un IDE, utilizar el compilador para correr el programa, sea en Python o Java.
- Si se utiliza una terminal, ejecutar los archivos correspondientes con su lenguaje de programación de la siguiente manera:

Para la ejecución del código Python en linux:
`python3 TSP.py`

Para la ejecución del código Python en windows:
`python TSP.py`

Para la compilación del código Java:
`javac TSP.java`

Para la ejecución del código Java:
`java TSP`

 ## Variación de parámetros
 En el código se puede modificar la cantidad de ciudades que va a tomar el algoritmo y la cantidad de hilos a utilizar para su ejecución. En el siguiente fragmento se pueden hacer dichas modificaciones:

- Modificar número de ciudades en Python (4 en el ejemplo):
```pyhon
TSP.py
...
# Ejemplo de uso
distancias = generar_matriz_distancias(4, 100)
...
```
 - Modificar número de hilos en Python (1 en el ejemplo):
```
TSP.py
...
# Ejemplo de uso
inicio = time.time()
resultado = tsp_paralelo(distancias, 1)  # Ajusta el número de procesos
...
```
 - Modificar número de ciudades e hilos en Java:
```
TSP.java
...
 public static void main(String[] args) throws InterruptedException, ExecutionException {
        int numCiudades = 12;
        int rangoDistancias = 100;

        int numProcesadores = 4;
...
```
