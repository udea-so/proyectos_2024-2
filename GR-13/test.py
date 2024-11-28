import threading
import requests
import time

URL = "http://127.0.0.1:8080/"
NUM_REQUESTS = 100  # Total de solicitudes a enviar
CONCURRENT_THREADS = 10  # Número de solicitudes concurrentes

def send_request():
    try:
        response = requests.get(URL)
        print(f"Estado: {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Error en solicitud: {e}")

def run_load_test():
    threads = []
    start_time = time.time()

    for _ in range(NUM_REQUESTS):
        thread = threading.Thread(target=send_request)
        threads.append(thread)
        thread.start()

        if len(threads) >= CONCURRENT_THREADS:
            for t in threads:
                t.join()
            threads = []

    end_time = time.time()
    print(f"Prueba completada en {end_time - start_time:.2f} segundos")

if __name__ == "__main__":
    run_load_test()
