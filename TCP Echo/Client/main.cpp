#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void ShowErrorMessage(string message){
	cout<<"[Error]"<<message<<endl;
	system("pause");
	exit(1);
}

int main(){
	WSADATA wsData;
	if(WSAStartup(MAKEWORD(2,2), &wsData) != 0)
		ShowErrorMessage("WSAStartup() Error");

	SOCKET clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		ShowErrorMessage("socket() Error");
	}

	int serverPort = 9876;
	SOCKADDR_IN serverAddress;
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(serverPort);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(clientSocket, (SOCKADDR*) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		ShowErrorMessage("connect() Error");
	}
	cout<<"connect() ing\n";
	string sent;
	char received[1024];
	while (1)
	{
		cout<<"[S]:";
		getline(cin,sent);
		if(sent == "")
			continue;
		send(clientSocket, sent.c_str(), sent.length(),0);
		int length = recv(clientSocket, received,sizeof(received),0);
		received[length]=NULL;
		if (strcmp(received,"[exit]") == 0)
		{
			cout<<"server exit"<<endl;
				break;
		}
		cout<<"[R]:"<<received<<endl;
	}
	closesocket(clientSocket);
	WSACleanup();

	system("pause");
	return 0;
}