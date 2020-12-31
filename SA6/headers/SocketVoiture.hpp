/**SA6 - Intelligent Car-Park**/
#ifndef BOUSK_DVP_SOCKET_COURS_SOCKETVOITURE_HPP
#define BOUSK_DVP_SOCKET_COURS_SOCKETVOITURE_HPP

#include "Sockets.hpp"

class SocketVoiture
{
public:
	SocketVoiture();
	~SocketVoiture();

	bool Connect(const std::string &ipaddress, unsigned short port);
	int Send(const char *data, unsigned int len);
	int Receive(char *buffer, unsigned int len);

private:
	SOCKET mSocket;
};

#endif // BOUSK_DVP_SOCKET_COURS_SOCKETVOITURE_H