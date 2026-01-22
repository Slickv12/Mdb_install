#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    int choice, num1, num2;

    while (1) {
        printf("\n---- MENU ----\n");
        printf("1. Find GCD\n");
        printf("2. Find LCM\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            sprintf(buffer, "%d 0 0", choice);
            send(client_socket, buffer, sizeof(buffer), 0);
            printf("Exiting...\n");
            break;
        }

        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        sprintf(buffer, "%d %d %d", choice, num1, num2);
        send(client_socket, buffer, sizeof(buffer), 0);

        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
    }

    close(client_socket);

    return 0;
}
