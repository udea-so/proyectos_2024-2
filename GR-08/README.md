# Sistema de Riego Automático con ESP32

Este proyecto utiliza un ESP32 para automatizar el riego de plantas según los niveles de humedad del suelo. El sistema incluye un sensor de humedad capacitivo, un relé para controlar la bomba y un esquema de conexión claro para facilitar la implementación.

## Requisitos del sistema

### Hardware
- ESP32
- Protoboard
- Sensor de humedad capacitivo
- Relé optoacoplador
- Mini bomba de agua
- Fuente de alimentación (5V)

### Software:
- VS Code con la extensión PlatformIO
- Librerias necesarias: ESP32 SPIRAM, FreeRTOS

## Esquema de conexion


## Pasos para usar este proyecto

### 1. Instalación de dependencias

  - Descarga la carpeta [riegoauto](https://github.com/sebudea/proyectos_2024-2/tree/main/GR-08/riegoauto)

4. Configuración del proyecto

- En VSCode, con la extension PlatformIO, selecciona "Open Project" y navega hasta la carpeta riegoauto que descargaste

- PlatformIO debería detectar automáticamente la configuración para el ESP32 en el archivo platformio.ini

3. Compilación y subida del código al ESP32

- Conecta tu ESP32 al computador vía USB

- En la barra lateral de PlatformIO, selecciona el ícono de "PlatformIO" y elige Build para compilar el código.

- Si la compilación es exitosa, selecciona Upload para cargar el código al ESP32.

## Nota

- La bomba se activa cuando el nivel de humedad es bajo (valor analógico >= 2100).




## Lista de chequeo

### Documentos

Dentro del directorio [documentos](documentos/) agregar los pdf de:
- [x] Propuesta.
- [ ] PDF del reporte escrito en formato IEEE ([Plantilla](https://docs.google.com/document/d/1STlifdKxZfG4ckL1YRGXvTSxvrQErKwg9SXYhQl0JYo/edit?usp=sharing)).
- [ ] Dispositivas de la presentacion final.

### Archivos y elementos del respositorio

- [ ] El repositorio del código implementado con su documentación. 
- [ ] Código que incluya todos los recursos relevantes para ejecutar la aplicación desarrollada para resolver el desafío. 
- [ ] Explicación de los requisitos del sistema
- [ ] Librerias y dependencias necesarias (pasos necesarios para llevar a cabo la instalación)
- [ ] Pasos necesarioas para ejecutar la aplicación.
- [ ] Ademas del código, es deseable que tenga un Notebook de Jupyter como complemento para la parte estadistica.
