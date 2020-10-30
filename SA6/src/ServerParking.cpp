#include "../headers/ServerParking.hpp"
#include "../headers/Parking.hpp"

	namespace Errors
	{
		enum Type
		{
#ifdef _WIN32
			WOULDBLOCK = WSAEWOULDBLOCK,
#else
			WOULDBLOCK = EWOULDBLOCK,
#endif
		};
	}

#define BUFFER_MAX 1024
bool ServerP::Receive(SOCKET socket, string& _buffer)
{
	char buffer[BUFFER_MAX + 1] = { 0 };
	int iLastRecievedBufferLen = 0;
	do {
		iLastRecievedBufferLen = recv(socket, buffer, BUFFER_MAX, 0);
		_buffer += buffer;
	} while (iLastRecievedBufferLen == BUFFER_MAX);
	if (iLastRecievedBufferLen > 0)
		return true;
	else
	{
		int error = Sockets::GetError();
		if ( error == Errors::WOULDBLOCK )
			return true;
		return false;
	}
}

struct Client {
	SOCKET socket;
	string ip;
	int port;
	int etape_client;
	Client(SOCKET _socket, const string& _ip, int _port)
		: socket(_socket)
		, ip(_ip)
		, port(_port)
	{}
	void Close() { Sockets::CloseSocket(socket); socket = INVALID_SOCKET; }
};

bool ServerP::Server(int port, Parking *parking)
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
		return false;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les adresses sont accept�es
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
		return false;
	res = listen(server, SOMAXCONN);
	if (res != 0)
		return false;
	Sockets::SetNonBlocking(server);
	cout << "Server demarre sur le port " << port << endl;
	vector<Client> clients;
	for (;;)
	{
		for (;;)
		{
			SOCKET newClient;
			sockaddr addr = { 0,0 };
			socklen_t len = sizeof(addr);
			newClient = accept(server, &addr, &len);
			if (newClient == INVALID_SOCKET)
				break;
			sockaddr_in from;
			socklen_t addrlen = sizeof(from);
			if (getpeername(newClient, (sockaddr*)&from, &addrlen) != 0)
			{
				cout << "Nouveau client, Impossible de retrouver son IP : " << Sockets::GetError() << " (deconnexion)" << endl;
				Sockets::CloseSocket(newClient);
				continue;
			}
			Client client(newClient, Sockets::ConvertAddr(from), ntohs(from.sin_port));
			//cout << "Connexion de " << client.ip.c_str() << ":"<< client.port << endl;
			Sockets::SetNonBlocking(newClient);
			client.etape_client = 1; // A chaque connexion l'etape client est a 1
			clients.push_back(client);
		}
		vector<Client>::iterator client = clients.begin();
		while (client != clients.end())
		{
			string buffer;
			if (Receive(client->socket, buffer))
			{
				if ( !buffer.empty() )
				{
// C'est ici qu'on gère la communication, à voir si on peux pas le séparer de la classe					
					cout << "Recu de [" << client->ip.c_str() << ":" << client->port << "] : " << buffer << endl;
					string reply = parking->protocoleCommunication(buffer, client->etape_client++); //on pointe vers la fonction présente dans notre instance de parking
					cout << "Reponse a [" << client->ip.c_str() << ":" << client->port << "] > " << reply << endl;
					send(client->socket, reply.c_str(), reply.length(), 0);
				}
				++client;
			}
			else
			{
				client->Close();
				cout << "[" << client->ip.c_str() << ":" << client->port << "] " << " Deconnexion" << endl;
				client = clients.erase(client);
			}
		}
	}
}