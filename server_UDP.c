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
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("UDP Server is running...\n");

    addr_len = sizeof(client_addr);

    while (1) {
        int num1, num2, choice, result;

        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&client_addr, &addr_len);

        sscanf(buffer, "%d %d %d", &choice, &num1, &num2);

        if (choice == 3) {
            printf("Client requested exit.\n");
            break;
        }

        if (choice == 1)
            result = gcd(num1, num2);
        else if (choice == 2)
            result = lcm(num1, num2);
        else
            result = -1;

        sprintf(buffer, "Result: %d", result);

        sendto(sockfd, buffer, sizeof(buffer), 0,
               (struct sockaddr*)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
