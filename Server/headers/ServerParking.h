#ifndef SERVERPARKING_H
#define SERVERPARKING_H
#ifdef _WIN32
#if _MSC_VER >= 1800
#include <WS2tcpip.h>
#else
#define inet_pton(FAMILY, IP, PTR_STRUCT_SOCKADDR) (*(PTR_STRUCT_SOCKADDR)) = inet_addr((IP))
typedef int socklen_t;
#endif
#include <WinSock2.h>
#ifdef _MSC_VER
#if _WIN32_WINNT >= _WIN32_WINNT_WINBLUE
//!< Win8.1 & higher
#pragma comment(lib, "Ws2_32.lib")
#else
#pragma comment(lib, "wsock32.lib")
#endif
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
#include <arpa/inet.h> // hton*, ntoh*, inet_addr
#include <unistd.h>  // close
#include <fcntl.h>
#include <cerrno> // errno
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

#include <string>
#include <vector>
#include <iostream>
#include <algorithm> 

using namespace std;

namespace ServerP
{
	bool Start();
	void End();
    int GetError();
    void CloseSocket(SOCKET s);
    bool SetNonBlocking(SOCKET s);
    string ConvertAddr(const sockaddr_in& addr);
    bool Receive(SOCKET socket, string& _buffer);
    vector<string> Split(const string& str, const string& separator);
    string Merge(const vector<string>& parts, const string& aggregator);
    string ShuffleSentence(const string& sentence);
        
    bool Server(int port);
};

#endif