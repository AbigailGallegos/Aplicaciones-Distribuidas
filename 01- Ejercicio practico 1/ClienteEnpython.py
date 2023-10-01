import socket
import threading

def recibir_mensajes(sock):
    while True:
        mensaje = sock.recv(1024).decode("utf-8")
        if not mensaje:
            break
        print("Servidor: " + mensaje)

try:
    # Configura el cliente
    host = '127.0.0.1'
    portJava = 12345
    portPython = 6789
    portC= 1011

    # Crea un socket TCP y conecta al servidor
    client_socket_java = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket_java.connect((host, portJava))
    client_socket_python = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket_python.connect((host, portPython))
    client_socket_c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket_c.connect((host, portC))



    print('Conectado al servidor')

    # Inicia un hilo para recibir mensajes del servidor
    recibir_thread_java = threading.Thread(target=recibir_mensajes, args=(client_socket_java,))
    recibir_thread_java.start()
    recibir_thread_python = threading.Thread(target=recibir_mensajes, args=(client_socket_python,))
    recibir_thread_python.start()
    recibir_thread_c = threading.Thread(target=recibir_mensajes, args=(client_socket_c,))
    recibir_thread_c.start()

    # Lee mensajes del usuario y los envía al servidor
    while True:
        mensaje_usuario = input()
        client_socket_java.send(mensaje_usuario.encode("utf-8"))
        client_socket_python.send(mensaje_usuario.encode("utf-8"))
        client_socket_c.send(mensaje_usuario.encode("utf-8"))

except Exception as e:
    print("Error: " + str(e))
finally:
    client_socket_c.close()
    client_socket_java.close()
    client_socket_python.close()


