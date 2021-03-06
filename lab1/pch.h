// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H

#include <iostream>

using namespace std;

#include <tchar.h>	// _tmain
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <string.h>

#pragma comment(lib,"Ws2_32.lib")	//	链接Ws2 （WinSock） 库文件

#define MAXSIZE 65507	// 发送数据报文的最大长度
#define HTTP_PORT 80 // http 服务器端口号



/* http 重要头部数据 */
struct HttpHeader
{
	char method[4]; // POST 或者 GET（本实验暂不考虑CONNECT	）
	char url[1024];	// 请求的url
	char host[1024];	//目标主机
	char cookie[1024 * 10];	// cookie

	/* 
		ZeroMemory: MS宏，调用 memset 用0填充该结构体内存 
		this：指针，指向该结构体
		*/

	HttpHeader() {
		ZeroMemory(this, sizeof(HttpHeader));	
	}
};

BOOL InitSocket();

void ParseHttpHead(char *buffer, HttpHeader *httpHeader);

BOOL ConnectToServer(SOCKET* serverSocket, char* host);

/*
	unsigned int : 返回值类型
	__stdcall：一种函数调用协议
	*/
unsigned int __stdcall ProxyThread(LPVOID lpParameter);


struct ProxyParam {
	SOCKET clientSocket;
	SOCKET serverSocket;
};



#endif //PCH_H
