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

int main(int argc, char **argv){
    if (argc != 2){
        cout << "Please Enter a port to connect" <<endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    int sockfd;
    char buffer[MAXLINE];
    //char *hello = "Hello from Server";
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    socklen_t addr_size;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        cout << "[-]Socket Creation Failed" <<endl;
        return 0;
    }

    servaddr.sin_addr.s_addr = inet_addr("157.230.41.161");
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    socklen_t clientlen = sizeof(cliaddr);
    bzero(&cliaddr, clientlen);
    while (1){
        bzero(&buffer, sizeof(buffer));
        cout << "Going to receive" <<endl;
        int rc = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &clientlen);
        buffer[rc] = '\0';

        if (rc < 0){
            cout << "Error reading from socket" << endl;
        }else{
            char clientIP[256];
            bzero(&clientIP, 256); 
            inet_ntop(AF_INET, &cliaddr.sin_addr, clientIP, 256);
            cout << "[+]Message received from "<< clientIP<<" : "<<buffer <<endl;
        }

        string msg = "Server got your Message";
        int sd = sendto(sockfd, msg.c_str(), msg.size()+1, 0, (struct sockaddr*)&cliaddr, clientlen);

        if (sd < 0){
           cout << "[-]Error writing to socket" << endl;
        }else{
            cout << "[+]Data Sent : " <<msg<< endl;
        }
    }
    close(sockfd);
}