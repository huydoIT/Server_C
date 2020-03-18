#include <stdio.h>
#include <string.h>
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
	/* IP 繧｢繝峨Ξ繧ｹ縲√・繝ｼ繝育分蜿ｷ縲√た繧ｱ繝・ヨ */
	char destination[80];
	unsigned short port = 9876;
	int dstSocket;

	/* sockaddr_in 讒矩菴・*/
	struct sockaddr_in dstAddr;

	/* 蜷・ｨｮ繝代Λ繝｡繝ｼ繧ｿ */
	int status;
	int numsnt;
	/************************************************************/

	/* Windows 迢ｬ閾ｪ縺ｮ險ｭ螳・*/
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* 逶ｸ謇句・繧｢繝峨Ξ繧ｹ縺ｮ蜈･蜉・*/
	printf("Connect to ? : (name or IP address) ");
	scanf("%s", destination);

	/* sockaddr_in 讒矩菴薙・繧ｻ繝・ヨ */
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_port = htons(port);
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_addr.s_addr = inet_addr(destination);

	/* 繧ｽ繧ｱ繝・ヨ逕滓・ */
	dstSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* 謗･邯・*/
	printf("Trying to connect to %s: \n", destination);
	connect(dstSocket, (struct sockaddr*) & dstAddr, sizeof(dstAddr));

	/* 繝代こ繝・ヨ騾∝・ */
	char str[BUFFER_SIZE] = { 0 };
	char buffer[4] = { 0 };
	int numrcv;
	int cnt = 0;
	while (1) {
		printf("Input messages: ");
		scanf("%s", &str);
		int cnt = 0;
		while (cnt <= 45)
		{
			send(dstSocket, str, strlen(str) + 1, 0);
			Sleep(10);
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
		printf("OK\n");
	}

	/* Windows 迢ｬ閾ｪ縺ｮ險ｭ螳・*/
	WSACleanup();
}
