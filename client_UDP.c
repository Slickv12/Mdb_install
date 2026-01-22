#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(server_addr);

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

            sendto(sockfd, buffer, sizeof(buffer), 0,
                   (struct sockaddr*)&server_addr, addr_len);

            printf("Exiting...\n");
            break;
        }

        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        sprintf(buffer, "%d %d %d", choice, num1, num2);

        sendto(sockfd, buffer, sizeof(buffer), 0,
               (struct sockaddr*)&server_addr, addr_len);

        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&server_addr, &addr_len);

        printf("%s\n", buffer);
    }

    close(sockfd);
    return 0;
}
