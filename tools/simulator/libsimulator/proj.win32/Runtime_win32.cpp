
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma  comment(lib,"ws2_32.lib")

#include "cocos2d.h"
#include "runtime/ConfigParser.h"
using namespace std;

string getIPAddress()
{
    WSADATA wsaData;  
    char name[155]={0};
    char ip[16];
	struct addrinfo hints;
	struct addrinfo *res = nullptr;
	int ret;
	struct sockaddr_in *addr;

    // customized by user
    auto &bindAddress = ConfigParser::getInstance()->getBindAddress();
    if (!bindAddress.empty())
    {
        return bindAddress;
    }

	memset(ip, 0, sizeof(ip));
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
    {  
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET; /* Allow IPv4 */
		hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
		hints.ai_protocol = 0; /* Any protocol */
		hints.ai_socktype = SOCK_STREAM;

		ret = getaddrinfo(name, NULL, &hints, &res);
		if (ret == 0 && res)
        { 
			addr = (struct sockaddr_in *)res->ai_addr;
			inet_ntop(AF_INET, &addr->sin_addr, ip, 16);
        }   
        WSACleanup( );
    }   
    return ip;
}
