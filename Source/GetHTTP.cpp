// Lic:
// Source/GetHTTP.cpp
// Get HTTP
// version: 20.11.17
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

//#include "../Headers/GetHTTP.hpp"
#include "../Headers/QuickString.hpp"

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

	string GetHTTP(string url, bool cutprotocol) {
		HTTP_Error = {};
#ifdef _WIN32
		string HostName{ "" };
		string PageName{ "" };
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
		{ int i;
		for (i = 0; i < url.size() && url[i] && url[i] != '/'; i++) HostName += url[i];
		for (i++; i < url.size() && url[i]; i++) PageName += url[i];
		}


		//HTTP GET
		//string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
		string get_http = "GET /" + PageName + " HTTP/1.1\r\nHost: " + HostName + "\r\nAccept: text/html\r\nConnection: close\r\n\r\n";


		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			//cout << "WSAStartup failed.\n";
			//system("pause");
			//return 1;
			HTTP_Error = "WSAStartup failed.";
			return "";
		}

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//host = gethostbyname(url.c_str());        
		host = gethostbyname(HostName.c_str());
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
		if (!cutprotocol)
			return website_HTML;
		else {
			string _ret{ "" };
			string _line{ "" };
			bool header{ true };
			int i = 0;
			// cout << "<PREVIEW>\n" << website_HTML << "\n</PREVIEW>\n";
			do {
				auto c = website_HTML[i++];
				//cout << i << ":" << (int)c <<":"<<_line<<":"<<(int)header<< endl;
				if (i >= website_HTML.size()) {
					HTTP_Error = "Immature termination of header";
					return "";
				}
				switch (c) {
				case 0:
					HTTP_Error = "Immature termination of header";
					return "";
				case 13:
					break;
				case 10:
					header = Trim(_line).size()>0;
					_line = "";
					break;
				default:
					_line += c;
				}
			} while (header);
			for (; i < website_HTML.size(); i++) _ret += website_HTML[i];
			return _ret;
		}
#else
		HTTP_Error = "No support yet for this platform!";
		return "";
#endif
	}

	string HTTP_GetError() { return HTTP_Error; }
}