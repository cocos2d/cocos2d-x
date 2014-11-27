
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "cocos2d.h"
using namespace std;

string getIPAddress()
{
    WSADATA wsaData;  
    char name[155]={0};
    char *ip=nullptr;
    PHOSTENT hostinfo;

    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
    {  
        if( gethostname ( name, sizeof(name)) == 0)   
        { 
            if((hostinfo = gethostbyname(name)) != NULL)   
            { 
                ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
            }   
        }   
        WSACleanup( );
    }   
    return ip;
}
