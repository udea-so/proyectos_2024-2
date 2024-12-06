# Análsisi de vulnerabilidades en sistemas operativos mediante shodan

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


# System Hardening on Kali Linux

This guide provides step-by-step instructions to harden a Kali Linux system by configuring SSH, firewall settings, kernel parameters, and disabling unnecessary services to improve security and reduce vulnerabilities.

## 1. Disable Root Login via SSH
To enhance security, disable root login by editing the SSH configuration file:

```bash
sudo nano /etc/ssh/sshd_config
```

PermitRootLogin no
Restart the SSH service to apply the changes:

bash
```
sudo systemctl restart ssh
```
## 2. Keep Kali Updated Automatically
Ensure the system stays updated to receive the latest security patches:

bash
```
sudo apt install unattended-upgrades
sudo dpkg-reconfigure --priority=low unattended-upgrades
```
## 3. Configure Firewall with UFW
Install and enable the Uncomplicated Firewall (UFW) to manage traffic:

bash
```
sudo apt install ufw
sudo ufw enable
```
Firewall Rules:
Allow SSH on the default port (or custom if changed):

bash
```
sudo ufw allow ssh
```
Deny HTTP traffic on port 80:

bash
```
sudo ufw deny 80
```
## 4. Change Default SSH Port
Change the SSH port to a non-standard value for added security:

bash
```
sudo nano /etc/ssh/sshd_config
```
Modify the Port line:

bash
```
Port 2222
```
Restart the SSH service to apply the changes:

bash
```
sudo systemctl restart ssh
```
## 5. Disable Password Authentication for SSH
Enforce the use of SSH keys by disabling password authentication:

bash
```
sudo nano /etc/ssh/sshd_config
```
Set the following parameter:

bash
```
PasswordAuthentication no
```
Restart the SSH service:

bash
```
sudo systemctl restart ssh
```
## 6. Generate a New SSH Key Pair
Create a secure SSH key pair for authentication:

bash
```
ssh-keygen -t rsa -b 4096
```
Follow the prompts to save the key and set a passphrase.

## 7. Adjust Kernel Parameters for Security
Edit the kernel parameters in /etc/sysctl.conf to harden the network stack:

bash
```
sudo nano /etc/sysctl.conf
```
Add the following lines:

bash
```
net.ipv4.tcp_syncookies = 1
net.ipv4.conf.all.rp_filter = 1
net.ipv4.conf.default.rp_filter = 1
net.ipv4.conf.all.accept_redirects = 0
net.ipv4.conf.default.accept_redirects = 0
```
Apply the changes:

bash
```
sudo sysctl -p
```
## 8. Disable USB Automount
Prevent automatic USB mounting to mitigate unauthorized device risks:

bash
```
sudo apt install xscreensaver
```
## 9. Update sources.list and Upgrade Packages
Ensure the correct repositories are configured and upgrade the system:

bash
```
sudo nano /etc/apt/sources.list
```
Add the following line if it is not present:

bash
```
deb http://http.kali.org/kali kali-rolling main non-free contrib
```
Then update and upgrade the system:

bash
```
sudo apt update
sudo apt upgrade
```
## 10. Disable Unnecessary Services
Disable services that are not needed to reduce the attack surface:

Disable Avahi Daemon (network discovery):
```
Copiar código
sudo systemctl disable avahi-daemon
sudo systemctl stop avahi-daemon
```
Disable CUPS (printing service):
bash
```
sudo systemctl disable cups
sudo systemctl stop cups
```
## 11. Apply Default Firewall Policies
Set default deny policies for incoming and outgoing traffic:

bash
```
sudo ufw default deny incoming
sudo ufw default deny outgoing
sudo ufw allow ssh
```
