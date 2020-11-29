#include "../headers/SocketVoiture.hpp"
#include <stdexcept>
#include <sstream>

/**
 * @brief Construct a new SocketVoiture::SocketVoiture object.
 */
SocketVoiture::SocketVoiture() {
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
	{
		std::ostringstream error;
		error << "Erreur initialisation socket [" << Sockets::GetError() << "]";
		throw std::runtime_error(error.str());
	}
}

/**
 * @brief Destroy the SocketVoiture::SocketVoiture object.
 */
SocketVoiture::~SocketVoiture() {
	Sockets::CloseSocket(mSocket);
}

/**
 * @brief Connects an IP Adress to a specific port.
 * @param ipaddress 
 * @param port 
 * @return true if the connection was succesfull, false otherwise.
 */
bool SocketVoiture::Connect(const std::string& ipaddress, unsigned short port) {
	sockaddr_in server;
	inet_pton(AF_INET, ipaddress.c_str(), &server.sin_addr.s_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	return connect(mSocket, (const sockaddr*)&server, sizeof(server)) == 0;
}

/**
 * @brief Sends a message trough the socket.
 * @param data 
 * @param len 
 * @return int 
 */
int SocketVoiture::Send(const char* data, unsigned int len) {
	return send(mSocket, data, len, 0);
}

/**
 * @brief Recieves a message trough the socket.
 * @param buffer 
 * @param len 
 * @return int 
 */
int SocketVoiture::Receive(char* buffer, unsigned int len) {
	return recv(mSocket, buffer, len, 0);
}