#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;
//20201206 upload
void ShowErrorMessage(string message)
{
	cout<<"[Error]"<<message<<endl;
	system("pause");
	exit(1);

}

int main(){
	WSADATA wsdata;
	if (WSAStartup(MAKEWORD(2,2), &wsdata) != 0)
	{
		ShowErrorMessage("WSStartup() Error");
	}
	
	SOCKET serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serverSocket == INVALID_SOCKET)
	{
		ShowErrorMessage("socket() Error");
	}

	SOCKADDR_IN serverAddress;
	memset(&serverAddress,0, sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	int serverPort=9876;
	serverAddress.sin_port=htons(serverPort);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		ShowErrorMessage("bind() Error");
	}
	cout<<"bind() ing\n";

	if (listen(serverSocket, 5) == SOCKET_ERROR)
	{
		ShowErrorMessage("listen() Error");
	}
	cout<<"listen() ing\n";

	SOCKET clientSocket;
	SOCKADDR_IN clientAddress;
	int clientAddressSize = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &clientAddressSize);
	if (clientSocket == INVALID_SOCKET)
	{
		ShowErrorMessage("accpet() error");
	}
	cout<<"accpet() ing\n";

	char receiveMessage[1024];
	while(1){
		int length = recv(clientSocket,receiveMessage,sizeof(receiveMessage),0);
		receiveMessage[length] =NULL;
		cout<<"[R]:"<<receiveMessage<<endl;
		cout<<"[S]:"<<receiveMessage<<endl;
		if (strcmp(receiveMessage,"[exit]") == 0)
		{
			send(clientSocket,receiveMessage,sizeof(receiveMessage)-1,0);
			cout<<"server exit";
			break;
		}
		send(clientSocket,receiveMessage,sizeof(receiveMessage)-1,0);
	}
	
	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();


	system("pause");
	return 0;
}