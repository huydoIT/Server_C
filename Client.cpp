#include <stdio.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define MAX_LIMIT 256
#define BUFFER_SIZE 256

void randStr(char result[10], int number)
{
	int i = 0;
	for (; i < number; i++) {
		result[i] = char((rand() % 26) + 65);
	}
	result[i] = '\0';
}

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

int
main() {
	/* IP アドレス、�Eート番号、ソケチE�� */
	char destination[80];
	unsigned short port = 9876;
	int dstSocket;

	/* sockaddr_in 構造佁E*/
	struct sockaddr_in dstAddr;

	/* 吁E��パラメータ */
	int status;
	int numsnt;
	/************************************************************/
	double time_spent = 0.0;


	/* Windows 独自の設宁E*/
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* 相手�Eアドレスの入劁E*/
	printf("Connect to ? : (name or IP address) ");
	scanf("%s", destination);

	/* sockaddr_in 構造体�EセチE�� */
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_port = htons(port);
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_addr.s_addr = inet_addr(destination);

	/* ソケチE��生�E */
	dstSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* 接綁E*/
	printf("Trying to connect to %s: \n", destination);
	connect(dstSocket, (struct sockaddr*) & dstAddr, sizeof(dstAddr));

	/* パケチE��送�E */
	char str[BUFFER_SIZE] = { 0 };
	char buffer[4] = { 0 };
	int numrcv;
	int cnt = 0;
	while (1) {
		printf("Input messages: ");
		scanf("%s", &str);
		int cnt = 0;
		clock_t begin = clock();
		while (cnt <= 90)
		{
			for (int i = 0; i < 10; i++) {
				send(dstSocket, str, strlen(str) + 1, 0);
				Sleep(10);
			}
			numrcv = recv(dstSocket, buffer, 3, 0);
			cnt += numrcv;
			if (strcmp(buffer, "MHK") == 0) {
				strcat(buffer, "@@@");
				printf("%s\n", buffer);
			}
			else if (check(buffer) == 1) {
				strcat(buffer, "OOO");
				printf("%s\n", buffer);
			}
			else {
				printf("From server: %s\n", buffer);
				printf("Number of char: %d\n", cnt);
			}
		}
		clock_t end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Time excuted: %f seconds\n", time_spent);
		printf("OK\n");
	}

	/* Windows 独自の設宁E*/
	WSACleanup();
}
