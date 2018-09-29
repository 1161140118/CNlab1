// lab1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"


/*
_tmain: 为支持unicode所使用的main别名，宏定义于<tchar.h>中
预编译后_tmain 即为 main
*/
int _tmain(int argc,  _TCHAR* argv[]	)
{
	cout << "代理服务器正在启动" << endl;
	cout << "初始化..." << endl;

	if (!InitSocket())
	{
		printf("socket 初始化失败\n");
		return -1;
	}

	printf("代理服务器正在运行，监听端口 %d\n", ProxyPort);

	SOCKET	acceptSocket = INVALID_SOCKET;
	ProxyParam	*lpProxyParam;
	HANDLE	hThread;
	DWORD	dwThreadID;


	// 代理服务器不断监听
	while (true)
	{
		acceptSocket = accept(ProxyServer, NULL, NULL);
		lpProxyParam = new ProxyParam;

		if (lpProxyParam == NULL)
		{
			continue;
		}

		lpProxyParam->clientSocket = acceptSocket;
		// 创建新线程，处理
		hThread = (HANDLE)_beginthreadex(NULL, 0, &ProxyThread, (LPVOID)lpProxyParam, 0, 0);
		CloseHandle(hThread);
		Sleep(200);
	}

	closesocket(ProxyServer);
	WSACleanup();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
