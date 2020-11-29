/**SA6 - Intelligent Car-Park**/
#include "../headers/Sockets.hpp"
#include <string>
namespace Sockets
{
	bool Start()
	{
#ifdef _WIN32
		WSAData wsaData;
		return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
#else
		return true;
#endif
	}
	void Release()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}
	int GetError()
	{
#ifdef _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif
	}
	void CloseSocket(SOCKET s)
	{
#ifdef _WIN32
		closesocket(s);
#else
		close(s);
#endif
	}
	bool SetNonBlocking(SOCKET s)
	{
#ifdef _WIN32
		unsigned long iMode = 1;
		return ioctlsocket(s, FIONBIO, &iMode) == 0;
#else
		return fcntl(s, F_SETFL, O_NONBLOCK) == 0;
#endif
	}
	std::string ConvertAddr(const sockaddr_in& addr)
	{
#if defined(_WIN32) && _MSC_VER >= 1800
		char buff[32] = {0};
		InetNtop(addr.sin_family, (void*)&(addr.sin_addr), buff, 31);
        return string(buff, 32);
#else
		return inet_ntoa(addr.sin_addr);
#endif
	}
}