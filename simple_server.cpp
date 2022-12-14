#include <cerrno>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[]) {

    //Creating a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1)
    {
        std::cout << "Failed to create a socket: errno " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    //Listen to port 9999 on any address
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(9999);

    if(bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cout << "Failed to bind to port 9999: errno" << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    //Start listening, hold at most 10 connections in the queue
    if (listen(sockfd, 10) < 0) {
        std::cout << "Failed to listen on a socket: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    //Grab a connection from the queue
    auto addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if(connection < 0) {
        std::cout << "Failed to grab connection" << errno << "\n";
        exit(EXIT_FAILURE);
    }

    //Read from the connection
    char buffer[100];
    auto bytesRead = read(connection, buffer, 100);
    std::cout << "The message was:" << buffer;

    //Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);

    //Closing connections
    close(connection);
    close(sockfd);


    return 0;
}
