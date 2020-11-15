// Lic:
// Source/GetHTTP.cpp
// Get HTTP
// version: 20.11.15
// Copyright (C) 2020 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#ifdef _WIN32

#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

#endif

namespace TrickyUnits {
    static string HTTP_Error{ "" };

    string GetHTTP(string url) {
        HTTP_Error = {};
#ifdef _WIN32

        WSADATA wsaData;
        SOCKET Socket;
        SOCKADDR_IN SockAddr;
        int lineCount = 0;
        int rowCount = 0;
        struct hostent* host;
        locale local;
        char buffer[10000];
        int i = 0;
        int nDataLength;
        string website_HTML;

        // website url
        // string url = "www.google.com";

        //HTTP GET
        string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";


        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            //cout << "WSAStartup failed.\n";
            //system("pause");
            //return 1;
            HTTP_Error = "WSAStartup failed.";
            return "";
        }

        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        host = gethostbyname(url.c_str());        
        if (!host) {
            HTTP_Error = "host became null";
            return "";
        }

        SockAddr.sin_port = htons(80);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            //cout << "Could not connect";
            //system("pause");
            //return 1;
            HTTP_Error = "Could not connect";
            return "";
        }

        // send GET / HTTP
        send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

        // recieve html
        while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
            int i = 0;
            while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

                website_HTML += buffer[i];
                i += 1;
            }
        }

        closesocket(Socket);
        WSACleanup();

        // Display HTML source 
        // cout << website_HTML;

        // pause
        //cout << "\n\nPress ANY key to close.\n\n";
        // cin.ignore(); cin.get();


        //return 0;
        return website_HTML;
#else
        HTTP_Error = "No support yet for this platform!";
        return "";
#endif
    }

    string HTTP_GetError() { return HTTP_Error; }
}