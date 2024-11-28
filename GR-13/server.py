import socket
import threading
import time

# Configuración del servidor
HOST = '127.0.0.1'  # Dirección localhost
PORT = 8080         # Puerto en el que escucha el servidor
MAX_CONNECTIONS = 50  # Número máximo de conexiones en la cola de espera

# Variables para análisis de desempeño
response_times = []  # Almacena los tiempos de respuesta
error_counts = {"404": 0, "500": 0}  # Contador de errores HTTP

# Manejo de cada conexión de cliente
def handle_client(client_socket):
    start_time = time.time()
    try:
        request = client_socket.recv(1024).decode()
        print(f"Solicitud recibida:\n{request}")

        # Responder con una página HTML simple
        http_response = """\
HTTP/1.1 200 OK
Content-Type: text/html

<html>
  <body>
    <h1>¡Hola, Mundo!</h1>
  </body>
</html>
"""
        client_socket.sendall(http_response.encode())
    except Exception as e:
        # Contabilizar errores 500 internos del servidor
        error_counts["500"] += 1
        print(f"Error interno del servidor: {e}")
    finally:
        end_time = time.time()
        response_time = end_time - start_time
        response_times.append(response_time)
        client_socket.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(MAX_CONNECTIONS)
    print(f"Servidor escuchando en {HOST}:{PORT}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Conexión desde {client_address}")
        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()

# Iniciar el servidor
if __name__ == "__main__":
    start_server()
