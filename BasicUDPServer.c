// BasicUDPServer.c
// 20131187 ±«øÎ¿œ
//
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <time.h>

#define PORT 31187   //The port on which to listen for incoming data
#define BUFLEN 1024
void Handle(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	struct sockaddr_in si_me, si_other;
	int s_socket, slen = sizeof(si_other), recv_len;
	int menu = 0;
	char buf[BUFLEN];

	//create a UDP socket
	if ((s_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		Handle("socket() error");
	}

	// zero out the structure
	memset((char *)&si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if (bind(s_socket, (struct sockaddr*)&si_me, sizeof(si_me)) == -1)
	{
		Handle("bind() error");
	}

	// Show message when the server is ready
	printf("The server is ready to receive on port %d\n", PORT);

	// Keep listening for data
	while (1)
	{
		recvfrom(s_socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
		if (atoi(buf) >= 1 && atoi(buf) <= 4) {
			printf("Connection requested from ('%s',%d)\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
			printf("Command %d\n\n", atoi(buf));
			menu = atoi(buf);
			memset(buf, 0, sizeof(buf));
		}
		else
			break;
		// Processing different message
		// 1. To Upper
		if (menu == 1) {
			recvfrom(s_socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			int i = 0;
			while (buf[i] != '\0') {
				buf[i] = toupper(buf[i]);
				i++;
			}
			sendto(s_socket, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen);
		}
		// 2. To Lower
		else if (menu == 2) {
			recvfrom(s_socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			int i = 0;
			while (buf[i] != '\0') {
				buf[i] = tolower(buf[i]);
				i++;
			}
			sendto(s_socket, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen);
		}
		// 3. Get my IP address and port number
		else if (menu == 3) {
			char message[1024];
			memset(message, 0, sizeof(message));
			char temp[10];
			snprintf(temp, 10, "%d", ntohs(si_other.sin_port));
			// strcat
			strcat(message, "IP : ");
			strcat(message, inet_ntoa(si_other.sin_addr));
			strcat(message, " Port : ");
			strcat(message, temp);
			// Send
			sendto(s_socket, message, strlen(message), 0, (struct sockaddr*) &si_other, slen);
		}
		// 4. Get server time
		else if (menu == 4) {
			// Get Time
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			char message[1024];
			memset(message, 0, sizeof(message));
			snprintf(message, 1024, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sendto(s_socket, message, strlen(message), 0, (struct sockaddr*) &si_other, slen);
		}
		// Clear buffer
		memset(buf, 0, sizeof(buf));

	}
	close(s_socket);
	return 0;
}