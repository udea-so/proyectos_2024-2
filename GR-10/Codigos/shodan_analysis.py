# -*- coding: utf-8 -*-
"""

"""
 import shodan
 SHODAN_API_KEY = 'TU CLAVE AQUI'
 # Inicializa la API de Shodan
 api = shodan.Shodan(SHODAN_API_KEY)
 Proyecto Final
 7
# Parámetros de búsqueda
 query = 'apache'
 page_size = 100  
max_results = 10  # Número máximo de resultados a most
 # Obtén el número total de resultados
 total_results = api.count(query)['total']
 print(f"Número total de resultados estimados: {total_r
 # Variable para contar los resultados procesados
 results_shown = 0
 # Itera sobre las páginas de resultados
 for page in range(1, (total_results // page_size) + 2)
    try:
        # Realiza la búsqueda en la página actual
        results = api.search(query, page=page)
        # Procesa los resultados de la página
        for result in results['matches']:
            if results_shown < max_results:
                print(f"IP: {result['ip_str']}")
                print(f"Puerto: {result['port']}")
                print(f"Data: {result['data']}")
                results_shown += 1
            else:
                break
        if results_shown >= max_results:
            break
    except shodan.APIError as e:
        print(f"Error en la página {page}: {e}")
 print("Fin de la búsqueda")