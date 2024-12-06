# Técnicas de aprendizaje automático para sistemas operativos (Scheduling)

## Descripción

Este proyecto tiene como objetivo desarrollar un modelo de aprendizaje automático para la programación de procesos en sistemas operativos. El modelo se entrena utilizando un entorno de simulación que imita la ejecución de procesos en un sistema operativo, buscando optimizar el tiempo de **turnaround (TT)** y **respuesta (TR)**. El proyecto implementa varios algoritmos de planificación tradicionales (como **FCFS**, **SJF**, **STCF**, **RR**) y un modelo basado en **PPO** (Proximal Policy Optimization) para comparar su desempeño.

## Objetivos

- **Objetivo Principal**: Desarrollar un modelo de aprendizaje automático que optimice la ejecución de procesos en un sistema operativo, minimizando los tiempos de **turnaround** y **respuesta**.
- **Objetivos Específicos**:
  - Implementar algoritmos de planificación de procesos (FCFS, SJF, STCF, RR).
  - Entrenar un modelo basado en PPO para aprender la mejor estrategia de ejecución de procesos.
  - Comparar los resultados del modelo de aprendizaje automático con los algoritmos tradicionales.
  - Visualizar el desempeño del modelo a través de gráficas de Gantt.

## Tecnologías

- **Lenguajes de Programación**: Python
- **Bibliotecas**:
  - **Gym**: Para la creación del entorno de simulación.
  - **Stable-Baselines3**: Para el entrenamiento del modelo PPO.
  - **Matplotlib**: Para la visualización de los resultados.
  - **NumPy**: Para manipulación de datos.
- **Frameworks**: TensorFlow/PyTorch (utilizados por Stable-Baselines3 para el entrenamiento del modelo PPO).

## Instalación

El proyecto está contenido en un único archivo de **Jupyter Notebook**:

1. **Ejecutar las dependencias**:
   Dentro del notebook, en el apartado correspondiente al **modelo**, se ejecutan las dependencias necesarias para el funcionamiento del proyecto. Asegúrate de ejecutar este bloque al inicio. Es posible que se necesite reiniciar el entorno de ejecución después de la instalación de las dependencias.

2. **Ejecutar el notebook en orden**:
   Una vez que las dependencias estén instaladas y el entorno reiniciado, ejecuta las celdas del notebook en orden. El código está estructurado para ser ejecutado de forma secuencial sin necesidad de modificaciones adicionales.

## Descripción de las Funciones

### Algoritmos de Scheduling

El proyecto implementa los siguientes algoritmos de scheduling:

- **FCFS** (First Come, First Served)
- **SJF** (Shortest Job First)
- **STCF** (Shortest Time to Completion First)
- **RR** (Round Robin)

### Funciones de Evaluación

- **t_turnaround**: Calcula el tiempo de turnaround promedio para todos los procesos.
- **t_response**: Calcula el tiempo de respuesta promedio para todos los procesos.
- **plot_scheduling**: Genera gráficos visuales para mostrar cómo se ejecutan los procesos a lo largo del tiempo.

### Modelo de Aprendizaje Automático (PPO)

Se utiliza un modelo de **aprendizaje por refuerzo** basado en **Proximal Policy Optimization (PPO)**, implementado con la librería **Stable Baselines3**. El objetivo del modelo es aprender a optimizar el orden de ejecución de los procesos mediante la interacción con un entorno de simulación.

En el aprendizaje por refuerzo, el modelo actúa de manera secuencial, eligiendo acciones (en este caso, el orden de ejecución de los procesos) basadas en el estado actual del entorno (los tiempos restantes de cada proceso). A medida que el modelo toma decisiones, recibe recompensas en función de su desempeño, que en este caso se calculan en función de los tiempos de **turnaround (TT)** y **respuesta (TR)**. El modelo utiliza estas recompensas para actualizar su política y mejorar su capacidad para predecir el orden de ejecución que minimice estos tiempos, aprendiendo a optimizar el rendimiento con el tiempo.


## Resultados

El modelo entrenado, los algoritmos de scheduling y sus comparaciones de rendimiento se visualizan mediante gráficos generados al final del notebook. Estos gráficos muestran cómo los algoritmos afectan los tiempos de ejecución, turnaround y respuesta.

## Conclusión

Este proyecto busca mejorar el rendimiento de los sistemas de scheduling mediante el uso de algoritmos tradicionales y técnicas de aprendizaje automático. Los resultados obtenidos muestran cómo el uso de un modelo de aprendizaje puede optimizar la eficiencia de la ejecución de procesos en comparación con los algoritmos clásicos.
