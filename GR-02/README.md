# Evaluación del rendimiento de un sistema RAID.

> **Importante** 

## Lista de chequeo

### Documentos

Dentro del directorio [documentos](documentos/) agregar los pdf de:
- [x] Propuesta.
- [x] PDF del reporte escrito en formato IEEE ([Plantilla](https://docs.google.com/document/d/1STlifdKxZfG4ckL1YRGXvTSxvrQErKwg9SXYhQl0JYo/edit?usp=sharing)).
- [x] Dispositivas de la presentacion final.


### Archivos y elementos del respositorio

- [x] El repositorio del código implementado con su documentación. 
- [X] Explicación de los requisitos del sistema
- [X] Librerias y dependencias necesarias (pasos necesarios para llevar a cabo la instalación)
- [X] Pasos necesarioas para ejecutar la aplicación.
- [ ] Ademas del código, es deseable que tenga un Notebook de Jupyter como complemento para la parte estadistica.

## Descripción del Proyecto

El proyecto propone implementar y evaluar un sistema RAID utilizando discos duros disponibles, con el objetivo de comparar su rendimiento con el de un solo disco. A través de esta evaluación, se busca comprender cómo la configuración RAID puede mejorar la eficiencia y la seguridad de los datos en entornos de almacenamiento. La implementación se centra en la configuración RAID 1 (reflejado), que prioriza la redundancia y la protección contra fallos de hardware. Este enfoque permitirá analizar los beneficios en términos de velocidad de lectura y escritura, así como la resiliencia frente a fallos de disco.

---

### Requisitos
- **Dos discos duros físicos.**
- **Acceso administrativo a la máquina.**

### Pasos

1. **Abrir la Consola de Comandos como Administrador:**
   - Presiona `Win + X` y selecciona "Símbolo del sistema (Administrador)" o "Windows PowerShell (Administrador)".

2. **Iniciar diskpart:**
   - En la consola, escribe `diskpart` y presiona Enter.

3. **Listar los Discos:**
   - Dentro de diskpart, escribe `list disk` y presiona Enter. Esto mostrará una lista de todos los discos conectados a la máquina.

4. **Seleccionar los Discos:**
   - Selecciona cada disco que deseas incluir en el RAID. Por ejemplo:
     ```bash
     select disk 0
     ```
     Luego:
     ```bash
     select disk 1
     ```

5. **Inicializar los Discos:**
   - Asegúrate de que ambos discos estén en modo MBR o GPT. Para inicializar un disco en modo MBR, escribe:
     ```bash
     clean
     convert mbr
     ```
     Repite este proceso para el segundo disco.

6. **Crear el Volumen Reflejado:**
   - Selecciona uno de los discos (por ejemplo, Disk 0):
     ```bash
     select disk 0
     ```
   - Crea un volumen básico en el disco seleccionado:
     ```bash
     create volume simple size=100%
     ```
   - Selecciona el volumen recién creado:
     ```bash
     select volume 1
     ```
   - Refleja el volumen en el segundo disco:
     ```bash
     add disk=1
     ```

7. **Formatear el Volumen:**
   - Formatea el volumen reflejado con un sistema de archivos (por ejemplo, NTFS):
     ```bash
     format fs=ntfs label="RAID1" quick
     ```

8. **Asignar una Letra de Unidad:**
   - Asigna una letra de unidad al volumen:
     ```bash
     assign letter=R
     ```

9. **Salir de diskpart:**
   - Escribe `exit` y presiona Enter para salir de diskpart.

10. **Verificar el RAID:**
    - Abre el "Administrador de Discos" para verificar que el RAID 1 se ha creado correctamente y que ambos discos están reflejados.
---
## Requisitos de Hardware
- **Procesador multicore.**
- **RAM 16GB o superior.**
  
