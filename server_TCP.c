#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_socket, 5);

    printf("Server is running on Ubuntu...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

    while (1) {
        int num1, num2, choice, result;

        recv(client_socket, buffer, sizeof(buffer), 0);
        sscanf(buffer, "%d %d %d", &choice, &num1, &num2);

        if (choice == 3) {
            printf("Client disconnected.\n");
            break;
        }

        if (choice == 1)
            result = gcd(num1, num2);
        else if (choice == 2)
            result = lcm(num1, num2);
        else
            result = -1;

        sprintf(buffer, "Result: %d", result);
        send(client_socket, buffer, sizeof(buffer), 0);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
