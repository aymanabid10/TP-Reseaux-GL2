//gcc serveur_udp_windows.c -lws2_32 -o serveur_udp_windows.exe
// ./serveur_udp_windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 12346
#define BUFFER_SIZE 128

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buffer[BUFFER_SIZE];
    time_t now;

    WSAStartup(MAKEWORD(2,2), &wsa);
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sock, (struct sockaddr*)&server, sizeof(server));

    // Attente d'une requête initiale
    recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client, &client_len);
    printf("Received from client: %s\n", buffer);
    
    for (int i = 0; i < 60; i++) {
        time(&now);
        snprintf(buffer, BUFFER_SIZE, "Il est %s", ctime(&now));
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client, client_len);
        Sleep(1000);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
