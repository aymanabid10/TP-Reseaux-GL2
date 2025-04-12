//gcc client_udp_windows.c -lws2_32 -o client_udp_windows.exe
// ./client_udp_windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 12346
#define BUFFER_SIZE 128

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    int n;

    WSAStartup(MAKEWORD(2,2), &wsa);
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Envoi d’un message initial
    char *init_msg = "Bonjour serveur";
    sendto(sock, init_msg, strlen(init_msg), 0, (struct sockaddr*)&server, sizeof(server));

    while ((n = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, NULL, NULL)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
