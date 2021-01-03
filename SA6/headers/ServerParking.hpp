#ifndef SERVERPARKING_HPP
#define SERVERPARKING_HPP
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
#include "../headers/Parking.hpp"
#include "../headers/Sockets.hpp"
#include <algorithm>
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

using namespace std;

namespace ServerP
{
    bool Receive(SOCKET socket, string &_buffer);
    bool Server(int port, Parking *parking);
}; // namespace ServerP

#endif