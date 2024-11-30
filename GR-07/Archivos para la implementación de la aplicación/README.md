# Detección de Objetos en Vegetales con ESP32-CAM y Edge Impulse

Este proyecto implementa un sistema de detección de objetos en vegetales utilizando un ESP32-CAM, Edge Impulse y Arduino IDE. A continuación, se describen los pasos y recursos necesarios.

---

## 📦 Requisitos

### Hardware

- **ESP32-CAM**: Módulo principal para captura de imágenes y despliegue del modelo.
- **Cables**: Para conexiones eléctricas.
- **Cable USB**: Para cargar el código y alimentar el ESP32-CAM.
- **Protoboard**: Para prototipado de las conexiones.

### Software

1. **Arduino IDE**: Para programar y cargar el código en el ESP32-CAM.
2. **Edge Impulse**: Plataforma para entrenar y desplegar modelos TinyML.
3. **Biblioteca EloquentEsp32camb (v2.7.15)**: Para configurar el ESP32-CAM como servidor web y capturar imágenes.
4. **Librerías ESP32**: Configura Arduino IDE con el siguiente enlace JSON:
   [https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)

---

## 🚀 Proceso de Implementación

### 1. Preparativos

- Configura el hardware necesario: conecta el ESP32-CAM, protoboard y cables según las especificaciones.
- Instala las dependencias necesarias en Arduino IDE utilizando el enlace JSON mencionado.

### 2. Adquisición de Datos

- Configura el ESP32-CAM como servidor web usando la biblioteca EloquentEsp32camb.
- Captura imágenes de los objetos (vegetales) utilizando la cámara del ESP32-CAM.

### 3. Uso de Edge Impulse

- **Crear un Proyecto**: Inicia un proyecto en [Edge Impulse](https://www.edgeimpulse.com/).
- **Cargar Imágenes**: Sube las imágenes capturadas.
- **Etiquetar Imágenes**: Dibuja cuadros delimitadores para identificar los objetos en las imágenes.

### 4. Creación del Modelo

- Configura un **impulse** con bloques de procesamiento de imágenes y detección de objetos.
- Genera las características a partir de las imágenes cargadas.

### 5. Despliegue del Modelo

- Exporta el modelo entrenado desde Edge Impulse como una biblioteca para Arduino.
- Carga el modelo al ESP32-CAM utilizando Arduino IDE.

### 6. Prueba del Sistema

- El ESP32-CAM ejecutará el modelo y detectará objetos en tiempo real.
- Visualiza los resultados directamente desde el módulo.

---

## 🛠️ Instalación de Librerías ESP32

1. Abre Arduino IDE y ve a **Archivo > Preferencias**.
2. En el campo "URL adicionales para gestor de tarjetas", pega el siguiente enlace:
   [https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)
3. Dirígete a **Herramientas > Placa > Gestor de tarjetas** e instala las placas ESP32.

---

## 👨‍💻 Autores

- Santiago Rivera
- Oswald Gutiérrez
- Leider Caicedo
