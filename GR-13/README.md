# Servidor Web Concurrente en Python

Este proyecto implementa un **servidor web concurrente** en Python utilizando **hilos** para manejar múltiples solicitudes simultáneamente. El servidor es capaz de responder con contenido HTML básico y guardar métricas de rendimiento, como tiempos de respuesta y errores HTTP, en un archivo CSV.

---

## **Características**
- Manejo de múltiples conexiones concurrentes mediante **hilos (`threading`)**.
- Respuestas HTTP básicas con una página HTML simple.
- Registro de métricas clave en un archivo CSV:
  - **Tiempos de respuesta**.
  - **Códigos de error HTTP**.
- Configuración del tamaño de la cola de conexiones para controlar la carga.
- Código modular y fácil de extender.

---

## **Requisitos**
- Python 3.7 o superior.
- Librerías estándar:
  - `socket`
  - `threading`
  - `time`
  - `csv`

---

## **Instalación**
1. Clona este repositorio:
   git clone https://github.com/Veritax0/servidor-web-concurrente.git
   cd servidor-web-concurrente

2. Verifica la instalación de python e instala dependencias
    python3 --version
    pip install requests

3. Ejecuta el archivo server.py para iniciar el servidor:
    python server.py
    **El servidor escuchará en 127.0.0.1:8080 de manera predeterminada. Puedes modificar las variables HOST y PORT en el archivo server.py para cambiar la dirección y puerto.**

4. Para probar el servidor, utiliza el script test.py, que genera múltiples solicitudes concurrentes:
    python test.py

5. Se creará un archivo csv en la carpeta raiz donde se guardaran las metricas del servidor para su posterior analisis.

