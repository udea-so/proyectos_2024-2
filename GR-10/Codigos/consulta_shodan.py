# -*- coding: utf-8 -*-
"""
@author: ACER
"""
import shodan
import time

SHODAN_API_KEY = 'TU_API_KEY'
api = shodan.Shodan(SHODAN_API_KEY)

def medir_tiempo_consulta(query):
    inicio = time.time()
    try:
        resultados = api.search(query)
    except shodan.APIError as e:
        print(f"Error en la consulta: {e}")
    fin = time.time()
    return fin - inicio

query = 'apache'
tiempo_respuesta = medir_tiempo_consulta(query)
print(f"Tiempo de respuesta: {tiempo_respuesta:.2f} segundos")
