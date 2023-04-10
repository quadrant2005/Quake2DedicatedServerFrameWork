#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "log.h"

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 27910
#define MAX_CLIENTS 16
#define BUFFER_SIZE 4096

typedef struct 
{
    SOCKET socket;
    char name[32];
} Client;


int main() 
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    Client clients[MAX_CLIENTS];
    fd_set readSet;
    int numClients = 0;
    int maxfd = 0;
    int i = 0;
    char buffer[BUFFER_SIZE];

    printf("\nSimple Quake 2 Dedicated Server Framework:\n\n\tVersion 1.0 Beta\n\tBuild: %s\n\n\tCoded By: [QBS]Quadrant\n\n",__DATE__);
    Log_Printf("\nSimple Quake 2 Dedicated Server Framework:\n\n\tVersion 1.2 Beta\n\tBuild: %s\n\n\tCoded By: [QBS]Quadrant\n",__DATE__);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("socket failed with error code %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Bind server socket to port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(DEFAULT_PORT);
    if (bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) 
    {
        printf("bind failed with error code %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("listen failed with error code %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Quake 2 server started on port %d\n", DEFAULT_PORT);

    while (1)
    {
        // Initialize read set
        FD_ZERO(&readSet);
        FD_SET(serverSocket, &readSet);
        for (i = 0; i < numClients; i++) 
        {
            FD_SET(clients[i].socket, &readSet);
        }

        // Wait for activity on one of the sockets
        maxfd = serverSocket;
        for (i = 0; i < numClients; i++) 
        {
            if (clients[i].socket > maxfd)
            {
                maxfd = clients[i].socket;
            }
        }
        if (select(maxfd + 1, &readSet, NULL, NULL, NULL) == SOCKET_ERROR) 
        {
            printf("select failed with error code %d\n", WSAGetLastError());
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // Handle incoming connection requests
        if (FD_ISSET(serverSocket, &readSet)) 
        {
            int clientAddrLen = sizeof
		}
		        // Add new client to list
        if (numClients < MAX_CLIENTS) 
		{
            printf("New client connected: %s\n", inet_ntoa(clientAddr.sin_addr));
            Log_Printf("New client connected: %s\n", inet_ntoa(clientAddr.sin_addr));
            clients[numClients].socket = clientSocket;
            strcpy(clients[numClients].name, "");
            numClients++;
        }
        else 
		{
            printf("Too many clients, connection rejected: %s\n", inet_ntoa(clientAddr.sin_addr));
            Log_Printf("Too many clients, connection rejected: %s\n", inet_ntoa(clientAddr.sin_addr));
            closesocket(clientSocket);
        }
    }

    // Handle activity on existing connections
    for (i = 0; i < numClients; i++) 
	{
        if (FD_ISSET(clients[i].socket, &readSet)) 
		{
            int bytesReceived = recv(clients[i].socket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived <= 0) 
			{
                printf("Client disconnected: %s\n", inet_ntoa(clientAddr.sin_addr));
                Log_Printf("Client disconnected: %s\n", inet_ntoa(clientAddr.sin_addr));
                closesocket(clients[i].socket);
                if (i < numClients - 1) 
				{
                    clients[i] = clients[numClients - 1];
                }
                numClients--;
            }
            else 
			{
                // Handle incoming message
            }
        }
    }
}

// Cleanup
closesocket(serverSocket);
//WSACleanup();
return 0;
}