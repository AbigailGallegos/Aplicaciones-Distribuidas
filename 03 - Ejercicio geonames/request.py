import requests 

api_key = 'zerabi'

base_url = 'http://api.geonames.org/countryCodeJSON'


params = {
        'lat': '47.0',
        'lng': '10.2',
        'username' : api_key
        }

response = requests.get(base_url,params=params)


if response.status_code == 200 :
    data = response.json()
    country_code = data['countryCode']
    
    print(f" El código de país para la ubicación proporcionada es: {country_code}")
else : 
    print(f"Error en la solicitud HTTP, Código de estado: {response.status_code} ")
