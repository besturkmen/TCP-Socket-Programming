#include<iostream>
#include<string>
#include<WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

void main() {

	std::string serverIP = "127.0.0.1"; //Server IP Address
	int serverPort = 58000;             //Server listening Port number

										//Initialize WinSock
	WSADATA winSockData;
	WORD version = MAKEWORD(2, 2);


	int  winSockOk = WSAStartup(version, &winSockData);
	if (winSockOk != 0) {
		std::cerr << "ERROR: [" << winSockOk << "] Could not Initialize WinSocket" << '\n';
		return;
	}


	//Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); //TCP IPV4
	if (sock == INVALID_SOCKET) {
		std::cerr << "ERROR: [" << WSAGetLastError() << "] Could not create a Socket" << '\n';
		WSACleanup();
		return;
	}

	//Fill in addr structure
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIP.c_str(), &addr.sin_addr);

	//Connect to a server
	int connectionStatus = connect(sock, (sockaddr*)&addr, sizeof(addr));

	if (connectionStatus == SOCKET_ERROR) {
		std::cerr << "ERROR: [" << WSAGetLastError() << "] Could not connect to the server" << '\n';
		closesocket(sock);
		WSACleanup();
		return;
	}

	char buf[512];
	ZeroMemory(buf, 512);
	//Receive Default Message from the Server
	int receivedBytes = recv(sock, buf, 512, 0);
	if (receivedBytes > 0) {

		std::cout << std::string(buf, 0, receivedBytes) << '\n';
	}

	std::string userInput;
	do {
		std::cout << "> ";
		std::getline(std::cin, userInput);
		if (userInput.size() > 0) {

			//sent data
			int sendResults = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResults != SOCKET_ERROR) {
				//Wait for response
				ZeroMemory(buf, 512);
				int receivedBytes = recv(sock, buf, 512, 0);
				if (receivedBytes > 0) {
					//Echo back to console
					std::cout << std::string(buf, 0, receivedBytes) << '\n';
				}
			}
		}


	} while (userInput.size() > 0);

	closesocket(sock);
	WSACleanup();


}