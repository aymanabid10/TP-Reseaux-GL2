//gcc serveur_tcp_windows.c -lws2_32 -o serveur_tcp_windows.exe
// ./serveur_tcp_windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 12345
#define BUFFER_SIZE 128

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buffer[BUFFER_SIZE];
    time_t now;

    WSAStartup(MAKEWORD(2,2), &wsa);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr*)&server, sizeof(server));
    listen(server_socket, 5);

    printf("En attente de connexion...\n");
    client_socket = accept(server_socket, (struct sockaddr*)&client, &client_len);

    for (int i = 0; i < 60; i++) {
        time(&now);
        snprintf(buffer, BUFFER_SIZE, "Il est %s", ctime(&now));
        send(client_socket, buffer, strlen(buffer), 0);
        Sleep(1000);
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
