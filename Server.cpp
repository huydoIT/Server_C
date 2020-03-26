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
	int srcSocket;  // 閾�E�蛻・
	int dstSocket;  // 逶�E�謁E�E

	struct sockaddr_in srcAddr;
	struct sockaddr_in dstAddr;
	int dstAddrSize = sizeof(dstAddr);

	/* 蜷・�E��E�繝代Λ繝｡繝ｼ繧�E� */
	int numrcv;
	char buffer[BUFFER_SIZE] = { 0 };
	srand(time(NULL));
	/************************************************************/
	/* Windows 迢�E�閾�E�縺�E�險�E�螳・*/
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);


	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 繧�E�繧�E�繝�Eヨ縺�E�逕滓�E */
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* 繧�E�繧�E�繝�Eヨ縺�E�繝�EぁE��ｳ繝�E*/
	bind(srcSocket, (struct sockaddr*) & srcAddr, sizeof(srcAddr));

	/* 謗･邯壹・險�E�蜿�E� */
	listen(srcSocket, 1);

	/* 謗･邯壹・蜿嶺�E�倥�E� */
	printf("============= SERVER =============\n");
	printf("Waiting for connection ...\n");

	dstSocket = accept(srcSocket, (struct sockaddr*) & dstAddr, &dstAddrSize);
	printf("Client IP: %s\n", inet_ntoa(dstAddr.sin_addr));

	/* 繝代こ繝�Eヨ蜿嶺�E��E� */
	int a = 1000, b = 500;
	char rs[100] = { 0 };
	while (1) {
		numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
		printf("From client: %s\n", buffer);
		//strncpy(rs, buffer + 2, strlen(buffer) - 2);
		//printf("Value = %d\n", atoi(rs));
		if (buffer[0] == 'R') {
			switch (buffer[1])
			{
			case 'A':
				//sprintf(rs, "%d", a);
				itoa(a, rs, 10);
				send(dstSocket, rs, strlen(rs), 0);
				//break;
			case 'B':
				sprintf(rs, "%d", b);
				itoa(b, rs, 10);
				send(dstSocket, rs, strlen(rs), 0);
				break;
			}
		}
		if (buffer[0] == 'W') 
		{
			switch (buffer[1])
			{
			case 'A':
				a += atoi(buffer + 2);
				
				//sprintf(rs, "%d", a);
				itoa(a, rs, 10);
				printf("a = %d || rs = %s\n", a, rs);
				send(dstSocket, rs, strlen(rs), 0);
				break;
			case 'B':
				b += atoi(buffer + 2);
				
				//sprintf(rs, "%d", b);
				itoa(b, rs, 10);
				printf("b = %d || rs = %s\n", b, rs);
				send(dstSocket, rs, strlen(rs), 0);
				break;
			}
		}
		//send(dstSocket, rs, strlen(rs), 0);
		//printf("Result: %s || a = %d\n", rs, a);
		//memset(rs, '\0', sizeof(rs));
	}
	closesocket(dstSocket);
	printf("Exit!\n");
	/* Windows 迢�E�閾�E�縺�E�險�E�螳・*/
	WSACleanup();
}
