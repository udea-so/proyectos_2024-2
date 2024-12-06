# Titulo del proyecto

> **Importante** 
> * El formato del README es libre.
> * Lo importante es que sea claro y que quien lo lea pueda replicar los pasos en su maquina.

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


### STEPS FOR REPRODUCE
#Configurar la maquina para Hardening.

 Deshabilitar el inicio de sesión root mediante SSH mediante la edicion de la carpeta etc mediante la ruta:
 sudo nano /etc/ssh/sshd_config
 Buscamos la opcion -> PermitRootLogin no
 
- [ ] Mantén Kali actualizado
 sudo apt install unattended-upgrades
 sudo dpkg-reconfigure --priority=low unattended-upgrade
 
 #Cortafuegos Firewall
 
- sudo apt install ufw
- sudo ufw enable
- sudo ufw allow ssh
- sudo ufw deny 80
 ###Cambia el puerto por defecto de SSH en /etc/ssh/sshd
- Port 2222

Deshabilita la autenticación por contraseña 
 
- PasswordAuthentication no
  
 
Genera una clave SSH con

 ssh-keygen -t rsa -b 4096
 
Ajusta parámetros del kernel en /etc/sysctl.conf par
 
- net.ipv4.tcp_syncookies = 1
- net.ipv4.conf.all.rp_filter = 1
- net.ipv4.conf.default.rp_filter = 1
- net.ipv4.conf.all.accept_redirects = 0
- net.ipv4.conf.default.accept_redirects = 0
  
Deshabilita USB automontado para evitar la ejecución
- sudo apt install xscreensaver
