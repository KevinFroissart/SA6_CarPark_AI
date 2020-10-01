/**SA6 - Intelligent Car-Park**/
#ifndef BOUSK_DVP_SOCKET_COURS_TCPSOCKET_H
#define BOUSK_DVP_SOCKET_COURS_TCPSOCKET_H

#pragma once

#include "Sockets.h"

#include <string>

class TCPSocket
{
	public:
		TCPSocket();
		~TCPSocket();

		bool Connect(const std::string& ipaddress, unsigned short port);
		int Send(const char* data, unsigned int len);
		int Receive(char* buffer, unsigned int len);

	private:
		SOCKET mSocket;
};


#endif // BOUSK_DVP_SOCKET_COURS_TCPSOCKET_H