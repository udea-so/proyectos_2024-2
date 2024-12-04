# Análisis de Datos de Monitoreo

Este proyecto analiza datos de monitoreo generados por una API de supervisión de rendimiento de equipos. Los datos se recopilaron y descargaron desde una base de datos PostgreSQL tras realizar pruebas en dos configuraciones diferentes:

- **Equipo 1:** Ryzen 7
- **Equipo 2:** Intel Core i7

Los resultados se consolidaron en archivos `.csv`, los cuales son utilizados para generar gráficos que permiten visualizar y comparar el rendimiento de ambos equipos en distintos escenarios.

---

## Estructura de los Archivos

### Archivos `.csv`
1. **datos_simulados.csv**: Contiene los datos del uso promedio de CPU y memoria en tres escenarios diferentes:
    - **YouTube**
    - **Microsoft Word**
    - **Navegación web**

    Columnas del archivo:
    - `Equipo`: Identifica si los datos provienen del Ryzen 7 o el Core i7.
    - `Escenario`: El contexto donde se tomó la medición.
    - `Uso_CPU`: Porcentaje promedio de uso de la CPU.
    - `Uso_Memoria`: Porcentaje promedio de uso de la memoria.

2. **datos_perfilado.csv**: Incluye datos de perfilado del rendimiento:
    - `Equipo`: Ryzen 7 o Core i7.
    - `Tiempo Promedio (ms)`: Tiempo promedio por llamada en milisegundos.
    - `Tiempo Total (s)`: Tiempo total registrado durante las pruebas.
    - `Número de Llamadas`: Cantidad de llamadas realizadas.

---

## Visualización de Gráficos

El análisis de los datos genera tres gráficos principales:

1. **Uso promedio de CPU por escenario y equipo**: Comparación entre los equipos en distintos escenarios.
2. **Distribución del uso de memoria por escenario y equipo**: Visualización de la distribución de datos con gráficos de violín.
3. **Tiempo promedio por llamada en el perfilado**: Comparación de los tiempos promedio por llamada entre los equipos.

---

## Cómo Ejecutar el Proyecto

### 1. Requisitos Previos
- **Python 3.7 o superior**
- Librerías necesarias:
  - `pandas`
  - `matplotlib`
  - `seaborn`

Instálalas con el siguiente comando:
```bash
pip install pandas matplotlib seaborn
```

Ejecuta linea por linea en Jupyter