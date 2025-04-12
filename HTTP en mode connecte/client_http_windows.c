//gcc client_http_windows.c -lws2_32 -o client_http_windows.exe
// ./client_http_windows.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "10.250.101.1"
#define PORT 80
#define BUFFER_SIZE 2048

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    int bytesReceived;

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(PORT);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    // Envoi requête HTTP
    char *request = "GET / HTTP/1.1\r\nHost: 10.250.101.1\r\nConnection: close\r\n\r\n";
    send(sock, request, strlen(request), 0);

    // Réception
    while ((bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        printf("%s", buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
