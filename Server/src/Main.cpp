/**SA6 - Intelligent Car-Park**/
#include "../headers/Sockets.h"
#include "../headers/TCPSocket.h"

#include <iostream>

int main()
{
	if ( !Sockets::Start() )
	{
		std::cout << "Error starting sockets : " << Sockets::GetError() << std::endl;
		return -1;
	}
	TCPSocket client;
	int port;
	std::cout << "Port du serveur ? ";
	std::cin >> port;
	if (!client.Connect("127.0.0.1", port))
	{
		std::cout << "Impossible de se connecter au serveur [127.0.0.1:" << port << "] : " << Sockets::GetError() << std::endl;
	}
	else
	{
		std::cin.ignore();
		std::cout << "Connecte!" << std::endl;
		std::cout << "Entrez une phrase >";
		std::string phrase;
		std::getline(std::cin, phrase);
		if ( client.Send(phrase.c_str(), phrase.length()) == SOCKET_ERROR )
		{
			std::cout << "Erreur envoi : " << Sockets::GetError() << std::endl;
		}
		else
		{
			char buffer[512] = {0};
			int len = client.Receive(buffer, 512);
			if ( len == SOCKET_ERROR )
			{
				std::cout << "Erreur reception : " << Sockets::GetError() << std::endl;
			}
			else
			{
				std::string reply(buffer, len);
				std::cout << "Reponse du serveur : " << reply << std::endl;
			}
		}
	}
	Sockets::Release();
	return 0;
}