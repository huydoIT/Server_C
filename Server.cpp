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
	unsigned short port = 9876;
	int srcSocket;  // 髢ｾ・ｪ陋ｻ繝ｻ
	int dstSocket;  // 騾ｶ・ｸ隰・・

	struct sockaddr_in srcAddr;
	struct sockaddr_in dstAddr;
	int dstAddrSize = sizeof(dstAddr);

	/* 陷ｷ繝ｻ・ｨ・ｮ郢昜ｻ｣ﾎ帷ｹ晢ｽ｡郢晢ｽｼ郢ｧ・ｿ */
	int numrcv;
	char buffer[BUFFER_SIZE] = { 0 };
	srand(time(NULL));
	/************************************************************/
	/* Windows 霑｢・ｬ髢ｾ・ｪ邵ｺ・ｮ髫ｪ・ｭ陞ｳ繝ｻ*/
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);


	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 郢ｧ・ｽ郢ｧ・ｱ郢昴・繝ｨ邵ｺ・ｮ騾墓ｻ薙・ */
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* 郢ｧ・ｽ郢ｧ・ｱ郢昴・繝ｨ邵ｺ・ｮ郢晁・縺・ｹ晢ｽｳ郢昴・*/
	bind(srcSocket, (struct sockaddr*) & srcAddr, sizeof(srcAddr));

	/* 隰暦ｽ･驍ｯ螢ｹ繝ｻ髫ｪ・ｱ陷ｿ・ｯ */
	listen(srcSocket, 1);

	/* 隰暦ｽ･驍ｯ螢ｹ繝ｻ陷ｿ蠍ｺ・ｻ蛟･・ */
	printf("============= SERVER =============\n");
	printf("Waiting for connection ...\n");

	dstSocket = accept(srcSocket, (struct sockaddr*) & dstAddr, &dstAddrSize);
	printf("Client IP: %s\n", inet_ntoa(dstAddr.sin_addr));

	/* 郢昜ｻ｣縺鍋ｹ昴・繝ｨ陷ｿ蠍ｺ・ｿ・｡ */
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
	/* Windows 霑｢・ｬ髢ｾ・ｪ邵ｺ・ｮ髫ｪ・ｭ陞ｳ繝ｻ*/
	WSACleanup();
}
