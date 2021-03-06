#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>
#include "CXBOXController.h"
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)



CXBOXController* Player;
int main()
{
	std::cout << "EERover Wi-Fi Application: \n";

	Player = new CXBOXController(1);

	if (Player->IsConnected()) {
		std::cout << "\nXBox Controller Connected: Player 1. \n";
	}
	else {
		std::cout << "XBox Controller not Connected.\nTerminate Program?\n";
		char yes;
		std::cin >> yes;
		if (yes == 'n') {

		}
		else {
			system("pause");
			return 1;
		}

	}
	

	//WinSock2 Initialisation
	WSADATA wsa;
	printf("\nInitialising WinSock2... ");

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0) {
		printf("Failed. Error: %d", WSAGetLastError());//Error Reporting
		return 1;
	}

	printf("Initialised.\n\n");	

	//Create TCP Socket
	SOCKET s;

	iResult = (s = socket(AF_INET, SOCK_STREAM, 0));
	if (iResult == INVALID_SOCKET) {
		printf("Could not create SOCKET: %d", WSAGetLastError());//Error Reporting
	}

	printf("SOCKET Created. \n");

	//Connect to remote server
	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr("192.168.240.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(23);

	iResult = connect(s, (struct sockaddr*) &server, sizeof(server));
	if (iResult < 0)
	{
		puts("Could not Connect to IP. \n");
		system("pause");
		return 1;
	}
	puts("Connected to IP.\nSOCKET Connected.");
	//CONNECTED



	//Recieve DATA
	int recv_size;
	char server_reply[2000];

	iResult = (recv_size = recv(s, server_reply, 2000, 0));
	if (iResult == SOCKET_ERROR) {
		puts("recv Failed");
	}
	puts("Reply Recieved\n");
	std::cout << "recv Size: " << recv_size << '\n';
	std::cout << server_reply << '\n';
	//DATA Recieved



	//Send DATA
	const char *message;
	message = "w";

	if (send(s, message, strlen(message), 0) < 0) {
		puts("Send failed");
		system("pause");
		return 1;
	}

	puts("Data Sent. \n");
	//DATA Sent






	//Custom Send 
	const char* data;
	char data2;

		std::cin >> data2;
		data = &data2;
		std::cout << data << '\n';





	std::cout << "\nEnd of EERover Program. \n";

	system("pause");
	return 0;
}