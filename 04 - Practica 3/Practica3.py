import requests

def obtener_datos_meteorologicos(api_key, ciudad):
    url = f"http://api.openweathermap.org/data/2.5/weather?q={ciudad}&appid={api_key}"
    try:
        response = requests.get(url)
        data = response.json()
        if response.status_code == 200 : 
            temperatura = data["main"]["temp"] - 273.15  # Convertir de Kelvin a Celsius
            condiciones_climaticas = data["weather"][0]["description"]
            print(f"Temperatura en {ciudad}: {temperatura:.2f}°C")
            print(f"Condiciones Climáticas en {ciudad}: {condiciones_climaticas}")
        else:
            print("Datos meteorológicos no disponibles.")
    except Exception as e:
        print(f"Error: {str(e)}")
def obtener_informacion_ubicacion(geonames_username, lugar):
    url = f"http://api.geonames.org/searchJSON?name={lugar}&maxRows=1&username={geonames_username}"
    api_key = "6ffac47dcdba11966b4396939b959ffb"
    try:
        response = requests.get(url)
        data = response.json()
        if response.status_code == 200 :
            ubicacion = data["geonames"][0]
            obtener_datos_meteorologicos(api_key, ubicacion['name'])
        else:
            print("Ubicación no encontrada.")
    except Exception as e:
        print(f"Error: {str(e)}")

if __name__ == "__main__":
    #tu_api_key_de_openweathermap
    geonames_username = "zerabi"
    lugar = "Londres"
    obtener_informacion_ubicacion(geonames_username, lugar)
