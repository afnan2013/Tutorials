#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#define MAXLINE 1024

using namespace std;

int main(int argc, char** argv){
    if (argc != 2){
        cout << "Please Enter a port to connect" <<endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    socklen_t addr_size;

    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        cout << "Socket Creation Failed" <<endl;
        return 0;
    }

    fgets(buffer, 1024, stdin);
    int sd = sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(sd < 0){
        cout << "[-]Can't send data to the server" <<endl;
    }else{
        cout << "[+]Data send successfully : " << buffer<<endl;
    }

    addr_size = sizeof(servaddr);
    bzero(&buffer, sizeof(buffer));
    int rc = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, &addr_size);
    if(sd < 0){
        cout << "[-]Can't send data to the server" <<endl;
    }else{
        cout << "[+]Data received successfully : " << buffer<<endl;
    }
    close(sockfd);
}