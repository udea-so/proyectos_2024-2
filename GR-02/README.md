[![Licencia MIT](https://img.shields.io/badge/Licencia-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Python Version](https://img.shields.io/badge/python-3.x-blue.svg)](https://www.python.org/downloads/)
[![GitHub](https://img.shields.io/badge/GitHub-zapata--git-darkgreen.svg)](https://github.com/zapata-git)
[![TQDM](https://img.shields.io/badge/TQDM-latest-orange.svg)](https://github.com/tqdm/tqdm)
# 💾 Evaluación del Rendimiento de un Sistema RAID 1

## 👥 Autores
- Carlos Zapata Arango
- Ferley José Silva Jiménez 
- Manuela Gutiérrez Cano

## 🎯 Objetivo
Implementar y evaluar un sistema RAID 1 (reflejado) utilizando discos duros físicos para comparar rendimiento y redundancia.

## 🛠️ Requisitos
- **Hardware**:
  - Dos discos duros físicos
  - Acceso administrativo a la máquina

## 📋 Pasos de Configuración de RAID 1

### 1. Abrir Consola de Comandos como Administrador
- Presionar `Win + X`
- Seleccionar "Símbolo del sistema (Administrador)" o "Windows PowerShell (Administrador)"

### 2. Iniciar diskpart
```bash
diskpart
```

### 3. Listar Discos
```bash
list disk
```

### 4. Seleccionar Discos
```bash
# Seleccionar primer disco (ejemplo: Disk 0)
select disk 0

# Seleccionar segundo disco (ejemplo: Disk 1)
select disk 1
```

### 5. Inicializar Discos
```bash
# Para cada disco
clean
convert mbr
```

### 6. Crear Volumen Reflejado
```bash
# Seleccionar primer disco
select disk 0

# Crear volumen simple en el primer disco
create volume simple size=100%

# Seleccionar volumen
select volume 1

# Añadir segundo disco al volumen reflejado
add disk=1
```

### 7. Formatear Volumen
```bash
# Formatear con sistema de archivos NTFS
format fs=ntfs label="RAID1" quick
```

### 8. Asignar Letra de Unidad
```bash
assign letter=R
```

### 9. Salir de diskpart
```bash
exit
```

## 🔍 Verificación
- Abrir "Administrador de Discos"
- Confirmar que RAID 1 está correctamente configurado
- Verificar que ambos discos están reflejados

## 📊 Métricas de Evaluación
- Velocidad de lectura
- Velocidad de escritura
- Tolerancia a fallos
- Redundancia de datos

## 🛡️ Beneficios de RAID 1
- Duplicación de datos
- Protección contra fallos de disco
- Mejora en velocidad de lectura
- Alta disponibilidad de datos

## 📚 Referencias
- Microsoft Docs - Administración de discos
- Documentación técnica de RAID

## 🤝 Contribuciones
1. Fork del repositorio
2. Crear rama de feature
3. Implementar mejoras
4. Documentar cambios
5. Solicitar Pull Request

---
© 2024 Grupo de Investigación, Universidad de Antioquia
