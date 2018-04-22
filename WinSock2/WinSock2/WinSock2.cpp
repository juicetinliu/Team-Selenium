//#include <Windows.h>
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>
#include <iostream>


#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

int main()
{
	std::cout << "EERover Wi-Fi Application: \n";

	//Initialisation
	WSADATA wsa;
	
	printf("\nInitialising WinSock2...");

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error: %d", WSAGetLastError());//Error Reporting
		return 1;
	}

	printf("Initialised.\n\n");
	//Winsock Finished Initialising

	/*
	std::cout << "Enter name: \n";
	std::string name;
	std::cin >> name;
	std::cout << "Your name is: " << name << std::endl;
	*/

	//Create TCP Socket
	SOCKET s;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create SOCKET: %d", WSAGetLastError());//Error Reporting
	}
	
	printf("SOCKET Created. \n");
		//Arguments of socket() function:
		//Address Family: AF_INET = IPv4
		//Type: SOCK_STREAM = (Means connection oriented TCP Protocol); SOCK_DGRAM = (indicates UDP Protocol)
		//Protocol: 0 [or IPPROTOCO_TCP, IPPROTOCO_UDP]
	//Socket Created



	//Connect to remote server
	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr("192.168.240.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(23);

	//std::cout << server.sin_addr.s_addr << '\n';

	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Could not Connect to IP. \n");
		//std::cout << server.sin_addr.s_addr << '\n';
		system("pause");
		return 1;
	}

	puts("Connected to IP.\nSOCKET Connected.");
	//CONNECTED



	//Recieve DATA
	int recv_size;
	char server_reply[2000];

	if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR) {
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
	std::string more = "y";
	const char *data;
	char data2;

	while (more == "y") {
		std::cout << "Please enter Message: \n";
		std::cin >> data2;
		data = &data2;
		std::cout << data << '\n';

		if (data == "break") {
			break;
		}

		if (send(s, data, strlen(data), 0) < 0) {
			puts("Send Failed");
			system("pause");
			return 1;
		}

		//puts("Message Sent. \n");
		//std::cout << "More?\n";
		//std::cin >> more;
	}
	
	



	std::cout << "\nEnd of EERover Program. \n";
	
	system("pause");
	return 0;
}