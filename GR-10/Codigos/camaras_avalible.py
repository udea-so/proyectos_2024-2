 import shodan
 SHODAN_API_KEY = 'TU CLAVE AQUI'
 # Inicializa la API de Shodan
 api = shodan.Shodan(SHODAN_API_KEY)
 # Parámetros de búsqueda
 query = 'title:"webcamXP"'
 page_size = 100  # Número de resultados por página
 Proyecto Final
 9
try:
    # Obtener el número total de resultados
    total_results = api.count(query)['total']
    print(f"Número total de resultados estimados: {tot
    # Iterar sobre las páginas de resultados
    for page in range(1, (total_results // page_size) 
        try:
            # Realizar la búsqueda en la página actual
            results = api.search(query, page=page)
            # Procesar los resultados de la página
            for result in results['matches']:
                print(f"IP: {result['ip_str']}")
                print(f"Puerto: {result['port']}")
                print(f"Data: {result['data']}")
                print("-" * 20)
        except shodan.APIError as e:
            print(f"Error en la página {page}: {e}")
 except shodan.APIError as e:
    print(f"Error al obtener el número total de result