/**SA6 - Intelligent Car-Park**/
#include "../headers/ServerParking.h"


int main()
{
	if(!ServerP::Start())
	{
		std::cout << "Erreur initialisation sockets : " << ServerP::GetError() << std::endl;
		return -1;
	}
	int port;
	std::cout << "Port du serveur > ";
	std::cin >> port;
	if (!ServerP::Server(port))
	{
		std::cout << "Serveur termine avec l'erreur " << ServerP::GetError() << std::endl;
	}
	ServerP::End();
	return 0;
}