# FastAPI Project

Este es un proyecto de ejemplo usando **FastAPI** y **PostgreSQL**. El objetivo de este proyecto es proporcionar una API RESTful que implemente diferentes mecanismos para analizar el rendimiento de una aplicación en un conjunto acotado de parámetros, tales como el uso de CPU, memoria y dispositivos de E/S, pero también el análisis del uso de recursos de una función determinada de la aplicación (creación de perfiles).

## Requisitos

- Para ejecutar este proyecto, asegúrate de tener instalado **Python 3.7+** y tener un entorno virtual configurado.
- Puede ser ejecutado desde cualquier sistema operativo según corresponda.
- Este proyecto se diseño en VScode

## Instalación

### **Clonar el repositorio:**

```bash
   git clone https://github.com/tu_usuario/tu_repositorio.git
   cd tu_repositorio
```
## Estructura del Proyecto

```
performance_monitoring/
├── app/
│   ├── __init__.py
│   ├── main.py
│   ├── core/
│   │   ├── config.py
│   │   ├── database.py
│   ├── controllers/
│   │   ├── __init__.py
│   │   ├── monitor.py
│   │   ├── profile.py
│   ├── schemas/
│   │   ├── __init__.py
│   │   ├── monitor.py
│   │   ├── profile.py
│   ├── models/
│   │   ├── __init__.py
│   │   ├── monitor.py
│   │   ├── profile.py
│   ├── services/
│   │   ├── __init__.py
│   │   ├── monitor.py
│   │   ├── profile.py
├── .env
├── requirements.txt
├── alembic.ini
├── README.md

```

### Configuración archivo .env

Crea un archivo llamado *.env* y pega su configuración
```bash
DATABASE_URL=postgresql://username:password@localhost:5432/monitoring_db
```

### Configuración archivo alembic.ini
Crea y configura el archivo alembic.ini para que apunte a la URL de la base de datos especificada en el archivo .env

```bash
[alembic]
script_location = alembic
sqlalchemy.url = postgresql://username:password@localhost:5432/monitoring_db
```

### **Crear un entorno virtual: En Linux/Mac:**
```bash
python3 -m venv myVirtualEnvironment
```

- **En Windows:**
```bash
python -m venv myVirtualEnvironment
```

### Activar el entorno virtual: En Linux/Mac:
```bash
source venv/bin/activate
```

- **En Windows:**
```bash
venv\Scripts\activate
```

## Instalar las dependencias:
```bash
pip install -r requirements.txt
```

## Ejecución

Para iniciar el servidor de desarrollo de FastAPI, ejecuta:
```bash
uvicorn main:app --reload
```

### Documentación interactiva de la API:

Swagger UI: http://127.0.0.1:8000/docs
Redoc: http://127.0.0.1:8000/redoc
Prueba los endpoints:
Desde Swagger puedes hacer llamadas a los endpoints creados (por ejemplo, /monitor o /profile).

## Prueba del Endpoint:
### Iniciar la monitorización:

Método: POST
URL: http://127.0.0.1:8000/monitor/start

### Detener la monitorización y obtener datos:
Método: POST
URL: http://127.0.0.1:8000/monitor/stop

### Consultar el monitoreo guardado en base de datos
Método: GET
URL: http://127.0.0.1:8000/monitor

### Perfilado:

Llama a /profile/start para iniciar.
Ejecuta código que quieras analizar (por ejemplo, sample_function).
Llama a /profile/stop para obtener los resultados.

### Consultar el perfilado guardado
Método: GET
URL: http://127.0.0.1:8000/profile
