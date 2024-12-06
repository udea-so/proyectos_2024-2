# Implementación del Algoritmo **TF-IDF** de manera *Secuencial* y *Paralelizada*

## Descripción
Este repositorio contiene el código fuente, recursos relevantes, y un complemento en formato Jupyter Notebook para la implementación del algoritmo TF-IDF en sus versiones secuencial y paralelizada. 
Este proyecto forma parte de un desafío que busca evaluar el rendimiento y escalabilidad del algoritmo procesando un conjunto grande de documentos.

## Requisitos del Sistema
Antes de ejecutar la aplicación, asegúrate de que tu sistema cumpla con los siguientes requisitos.

  ### Hardware Recomendado:
  Clúster de cómputo con al menos 4 nodos y 8 GB de RAM por nodo.
  
  ### Software Necesario:
  > * Python 3.9 o superior.
  > * Apache Spark 3.3 o superior.
  > * Jupyter Notebook.

## Pasos para su ejecución
  ### [Algoritmo No Paralelizado](TF_IDF_NonP.ipynb/)
  1. Asegurate de importar las librerías necesarias como **nltk**
  2. Modifica la línea:
     ```Python
      folder_path = "../Data"
     ```
     Con el correspondiente path a tu Dataset
  3. Corre el Algoritmo

  ### [Algoritmo Paralelizado](TF_IDF_P3.ipynb/)
  1. Importa ***Spark Framework*** y las otras librerías como **nltk**
  2. Configura tu sesión de *Spark* con los recursos que tengas disponibles
  3. Modificas las líneas:
     ```Python
      path="../Data"
     ```
     ```Python
      nro_docs=len(sc.wholeTextFiles("../Data/", minPartitions=3)\
               .map(lambda txt: txt[0].split('/')[-1].split('.')[0]).collect())
     ```
     Con el correspondiente path a tu Dataset
  4. Corre el Algoritmo
