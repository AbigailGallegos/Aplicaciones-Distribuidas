import http.server
import socketserver
import requests

# Tu API Key de OpenWeatherMap
geonames_username = "zerabi"

# Función para obtener datos meteorológicos
def obtener_datos_meteorologicos(ciudad):
    url = f"http://api.geonames.org/searchJSON?name={ciudad}&maxRows=1&username={geonames_username}"
    api_key = "6ffac47dcdba11966b4396939b959ffb"
    try:
        response = requests.get(url)
        data = response.json()
        if response.status_code == 200:
            ubicacion = data["geonames"][0]
            obtener_datos_meteorologicos(api_key, ubicacion['name'])
        else:
            print("Ubicación no encontrada.")
    except Exception as e:
        print(f"Error: {str(e)}")

# Clase personalizada para manejar las solicitudes
class MyHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith('/weather/'):
            ciudad = self.path[9:]
            resultado = obtener_datos_meteorologicos(ciudad)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(resultado.encode())
        else:
            super().do_GET()

# Configuración del servidor
with socketserver.TCPServer(("",9090), MyHandler) as httpd:
    print("Servidor web en el puerto 9090 para openweathermap")
    httpd.serve_forever()