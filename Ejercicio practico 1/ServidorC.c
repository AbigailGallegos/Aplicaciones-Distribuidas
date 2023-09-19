#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

 

#define PORT 1011
#define MAX_CLIENTS 10

 

void handle_client(SOCKET client_socket) {
    char buffer[1024];
    int bytes_received;

 

    while (1) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            // El cliente se desconectó o hubo un error
            break;
        }
        buffer[bytes_received] = '\0'; // Agregar un terminador de cadena
        printf("Cliente dice: %s\n", buffer);

 

        // Enviar el mensaje a todos los clientes (excepto al remitente)
        // Implementa la lógica de envío a todos los clientes aquí

 

        // Ejemplo: Envío de vuelta al cliente
        send(client_socket, buffer, bytes_received, 0);
    }

 

    closesocket(client_socket);
}

 

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

 

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

 

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

 

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

 

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

 

    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

 

    printf("Server listening on port %d\n", PORT);

 

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            perror("Accept failed");
            continue;
        }

 

        printf("Cliente conectado: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

 

        // Crear un hilo o proceso para manejar el cliente
        // Puedes implementar la función 'handle_client' para gestionar la comunicación con el cliente
        // Ejemplo: CreateThread o fork()

 

        // Ejemplo de manejo de cliente en el hilo principal (simplificado)
        handle_client(client_socket);
    }

 

    closesocket(server_socket);
    WSACleanup();

 

    return 0;
}