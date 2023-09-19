#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT_JAVA 12345
#define PORT_PYTHON 6789
#define PORT_C 1011

int main() {
    WSADATA wsaData;
    SOCKET client_socket_java, client_socket_python, client_socket_c;
    struct sockaddr_in server_addr_java, server_addr_python, server_addr_c;
    char message[1024];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    // Crear socket para la conexión a Java
    client_socket_java = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_java == INVALID_SOCKET) {
        perror("Socket creation (Java) failed");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor Java
    server_addr_java.sin_family = AF_INET;
    server_addr_java.sin_addr.s_addr = inet_addr("127.0.0.1"); // Cambia a la dirección del servidor
    server_addr_java.sin_port = htons(PORT_JAVA);

    // Conectar al servidor Java
    if (connect(client_socket_java, (struct sockaddr *)&server_addr_java, sizeof(server_addr_java)) == SOCKET_ERROR) {
        perror("Connection to Java failed");
        exit(EXIT_FAILURE);
    }

    // Crear socket para la conexión a Python
    client_socket_python = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_python == INVALID_SOCKET) {
        perror("Socket creation (Python) failed");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor Python
    server_addr_python.sin_family = AF_INET;
    server_addr_python.sin_addr.s_addr = inet_addr("127.0.0.1"); // Cambia a la dirección del servidor
    server_addr_python.sin_port = htons(PORT_PYTHON);

    // Conectar al servidor Python
    if (connect(client_socket_python, (struct sockaddr *)&server_addr_python, sizeof(server_addr_python)) == SOCKET_ERROR) {
        perror("Connection to Python failed");
        exit(EXIT_FAILURE);
    }

    // Crear socket para la conexión a C
    client_socket_c = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_c == INVALID_SOCKET) {
        perror("Socket creation (C) failed");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor C
    server_addr_c.sin_family = AF_INET;
    server_addr_c.sin_addr.s_addr = inet_addr("127.0.0.1"); // Cambia a la dirección del servidor
    server_addr_c.sin_port = htons(PORT_C);

    // Conectar al servidor C
    if (connect(client_socket_c, (struct sockaddr *)&server_addr_c, sizeof(server_addr_c)) == SOCKET_ERROR) {
        perror("Connection to C failed");
        exit(EXIT_FAILURE);
    }

    printf("Conectado a los servidores. Escribe 'exit' para salir.\n");

    while (1) {
        printf("Tú: ");
        fgets(message, sizeof(message), stdin);

        // Enviar mensaje a Java
        if (send(client_socket_java, message, strlen(message), 0) == SOCKET_ERROR) {
            perror("Send to Java failed");
            break;
        }

        // Enviar mensaje a Python
        if (send(client_socket_python, message, strlen(message), 0) == SOCKET_ERROR) {
            perror("Send to Python failed");
            break;
        }

        // Enviar mensaje a C
        if (send(client_socket_c, message, strlen(message), 0) == SOCKET_ERROR) {
            perror("Send to C failed");
            break;
        }

        if (strcmp(message, "exit") == 0) {
            printf("Cerrando cliente...\n");
            break;
        }
    }

    closesocket(client_socket_java);
    closesocket(client_socket_python);
    closesocket(client_socket_c);
    WSACleanup();

    return 0;
}
