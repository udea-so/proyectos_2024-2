import random
import itertools
import multiprocessing
import time

import os
num_cores = os.cpu_count()
print(f"Número de núcleos de CPU disponibles: {num_cores}")

def generar_matriz_distancias(num_ciudades, rango_distancias):
  """Genera una matriz de distancias aleatoria para el TSP.

  Args:
    num_ciudades: Número de ciudades.
    rango_distancias: Rango de valores aleatorios para las distancias.

  Returns:
    Una matriz de distancias de tamaño num_ciudades x num_ciudades.
  """
  matriz = [[0 for _ in range(num_ciudades)] for _ in range(num_ciudades)]
  for i in range(num_ciudades):
    for j in range(i+1, num_ciudades):
      distancia = random.randint(0, rango_distancias)
      matriz[i][j] = distancia
      matriz[j][i] = distancia
  return matriz

def tsp_secuencial(distancias):
    ciudades = list(range(len(distancias)))
    min_dist = float('inf')
    for permutacion in itertools.permutations(ciudades):
        dist_total = 0
        for i in range(len(permutacion) - 1):
            dist_total += distancias[permutacion[i]][permutacion[i+1]]
        dist_total += distancias[permutacion[-1]][permutacion[0]]
        min_dist = min(min_dist, dist_total)
    return min_dist

# Ejemplo de uso
distancias = generar_matriz_distancias(4, 100)

inicio = time.time()
resultado = tsp_secuencial(distancias)
fin = time.time()
print("Distancia mínima (secuencial):", resultado)
print("Tiempo de ejecución:", round(fin - inicio, 7), "segundos")

import multiprocessing
import time

def calcular_distancia(permutacion, distancias):
    dist_total = 0
    for i in range(len(permutacion) - 1):
        dist_total += distancias[permutacion[i]][permutacion[i+1]]
    dist_total += distancias[permutacion[-1]][permutacion[0]]
    return dist_total

def tsp_paralelo(distancias, num_procesos):
    ciudades = list(range(len(distancias)))
    permutaciones = itertools.permutations(ciudades)

    with multiprocessing.Pool(processes=num_procesos) as pool:
        resultados = pool.starmap(calcular_distancia, [(p, distancias) for p in permutaciones])

    return min(resultados)

# Ejemplo de uso
inicio = time.time()
resultado = tsp_paralelo(distancias, 1)  # Ajusta el número de procesos
fin = time.time()
print("Distancia mínima (paralelo):", resultado)
print("Tiempo de ejecución:", round(fin - inicio, 7), "segundos")
