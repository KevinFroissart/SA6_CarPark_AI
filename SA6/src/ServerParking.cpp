#include "../headers/ServerParking.hpp"
#include "../headers/parking.hpp"

bool ServerP::Start()
	{
#ifdef _WIN32
		WSAData wsaData;
		return WSAStartup(MAKEWORD(2,2), &wsaData) == 0;
#else
		return true;
#endif
	}
	void ServerP::End()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}
	int ServerP::GetError()
	{
#ifdef _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif
	}
	void ServerP::CloseSocket(SOCKET s)
	{
#ifdef _WIN32
		closesocket(s);
#else
		close(s);
#endif
	}
	bool ServerP::SetNonBlocking(SOCKET s)
	{
#ifdef _WIN32
		unsigned long iMode = 1;
		return ioctlsocket(s, FIONBIO, &iMode) == 0;
#else
		return fcntl(s, F_SETFL, O_NONBLOCK) == 0;
#endif
	}

	std::string ServerP::ConvertAddr(const sockaddr_in& addr)
	{
#if defined(_WIN32) && _MSC_VER >= 1800
		char buff[32] = {0};
		InetNtop(addr.sin_family, (void*)&(addr.sin_addr), buff, 31);
		return std::string(buff, 32);
#else
		return inet_ntoa(addr.sin_addr);
#endif
	}

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
		int error = GetError();
		if ( error == Errors::WOULDBLOCK )
			return true;
		return false;
	}
}

vector<string> ServerP::Split(const string& str, const string& separator)
{
	vector<string> parts;
	int start = 0;
	size_t end;
	while ( (end = str.find(separator, start)) != string::npos )
	{
		parts.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	parts.push_back(str.substr(start));
	return parts;
}

string ServerP::Merge(const vector<string>& parts, const string& aggregator)
{
	if ( parts.empty() )
		return "";
	string result = parts[0];
	for ( size_t i = 1; i < parts.size(); ++i )
		result += aggregator + parts[i];
	return result;
}

string ServerP::ShuffleSentence(const string& sentence)
{
	vector<string> words = Split(sentence, " ");
	random_shuffle(words.begin(), words.end());
	return Merge(words, " ");
}

struct Client {
	SOCKET socket;
	string ip;
	int port;
	Client(SOCKET _socket, const string& _ip, int _port)
		: socket(_socket)
		, ip(_ip)
		, port(_port)
	{}
	void Close() { ServerP::CloseSocket(socket); socket = INVALID_SOCKET; }
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
	SetNonBlocking(server);
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
				cout << "Nouveau client, Impossible de retrouver son IP : " << GetError() << " (deconnexion)" << endl;
				CloseSocket(newClient);
				continue;
			}
			Client client(newClient, ConvertAddr(from), ntohs(from.sin_port));
			cout << "Connexion de " << client.ip.c_str() << ":"<< client.port << endl;
			SetNonBlocking(newClient);
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
					string reply = parking->protocoleCommunication(buffer); //on pointe vers la fonction présente dans notre instance de parking
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