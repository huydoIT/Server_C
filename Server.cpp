#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <time.h>
#include <time.h>

#define BUFFER_SIZE 256

int check(char data[BUFFER_SIZE]) {
	int i = 0;
	while (data[i] != '\0')
	{
		if (data[0] != data[i]) {
			return 0;
		}
		i++;
	}
	return 1;
}

void randStr(char result[10], int number)
{
	int i = 0;
	//srand(time(NULL));
	for (; i < number; i++) {
		result[i] = char((rand() % 26) + 65);
	}
	result[i] = '\0';
}
int
main() {
	/* 繝昴・繝育分蜿ｷ縲√た繧ｱ繝・ヨ */
	unsigned short port = 9876;
	int srcSocket;  // 閾ｪ蛻・
	int dstSocket;  // 逶ｸ謇・

	/* sockaddr_in 讒矩菴・*/
	struct sockaddr_in srcAddr;
	struct sockaddr_in dstAddr;
	int dstAddrSize = sizeof(dstAddr);

	/* 蜷・ｨｮ繝代Λ繝｡繝ｼ繧ｿ */
	int numrcv;
	char buffer[BUFFER_SIZE] = { 0 };
	srand(time(NULL));
	/************************************************************/
	/* Windows 迢ｬ閾ｪ縺ｮ險ｭ螳・*/
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* sockaddr_in 讒矩菴薙・繧ｻ繝・ヨ */
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 繧ｽ繧ｱ繝・ヨ縺ｮ逕滓・ */
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* 繧ｽ繧ｱ繝・ヨ縺ｮ繝舌う繝ｳ繝・*/
	bind(srcSocket, (struct sockaddr*) & srcAddr, sizeof(srcAddr));

	/* 謗･邯壹・險ｱ蜿ｯ */
	listen(srcSocket, 1);

	/* 謗･邯壹・蜿嶺ｻ倥￠ */
	printf("============= SERVER =============\n");
	printf("Waiting for connection ...\n");

	dstSocket = accept(srcSocket, (struct sockaddr*) & dstAddr, &dstAddrSize);
	printf("Client IP: %s\n", inet_ntoa(dstAddr.sin_addr));

	/* 繝代こ繝・ヨ蜿嶺ｿ｡ */
	while (1) {
		numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
		if (numrcv == -1 || numrcv == 0) {
			printf("Client Exit!!\n");
			closesocket(dstSocket);
			break;
		} else
		if (strcmp(buffer, "END") == 0) {
			closesocket(dstSocket);
			printf("Client Disconnected!!\n");
			break;
		}
		else {
			printf("From client: %s\n", buffer);
			char str[3] = {0};
			randStr(str, 3);
			send(dstSocket, str, strlen(str), 0);
		}
	}
	closesocket(dstSocket);
	printf("Exit!\n");
	/* Windows 迢ｬ閾ｪ縺ｮ險ｭ螳・*/
	WSACleanup();
}