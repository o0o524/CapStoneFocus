// BasicUDPClient.c
// 20131187 ±«øÎ¿œ
//
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "165.194.35.202"
#define BUFLEN 1024  //Max length of buf
#define PORT 31187   //The port on which to send data

void Handle(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	struct sockaddr_in si_other;
	int sock, i, slen = sizeof(si_other);
	int menu = 0;
	char buf[BUFLEN];
	char message[BUFLEN];

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		Handle("socket() error");
	}

	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	// Check whether address is vaild
	if (inet_aton(SERVER, &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	// Display Menu
	while (1) {
		struct timeval start_time, later_time;

		printf("<Menu>\n");
		printf("1) convert text to UPPER-case\n");
		printf("2) convert text to LOWER-case\n");
		printf("3) get my IP address and port number\n");
		printf("4) get server time\n");
		printf("5) exit\n");
		printf("Input option : ");

		scanf("%d", &menu);

		if (menu == 1) {
			strcpy(buf, "1");
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			memset(buf, 0, sizeof(buf));
			// Input sentence 
			printf("Input sentence: ");
			scanf("%s", buf);
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			gettimeofday(&start_time, NULL);
			memset(buf, 0, sizeof(buf));
			// Reply
			recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			gettimeofday(&later_time, NULL);
			printf("Reply from server : %s\n", buf);
			// Caculate Time Diff
			if (later_time.tv_usec - start_time.tv_usec < 1000)
				printf("Response time : 0.%lu ms\n", later_time.tv_usec - start_time.tv_usec);
			else
				printf("Response time : %lu.%lu ms\n", (later_time.tv_usec - start_time.tv_usec) / 1000, (later_time.tv_usec - start_time.tv_usec) % 1000);
			memset(buf, 0, sizeof(buf));
		}
		else if (menu == 2) {
			strcpy(buf, "2");
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			memset(buf, 0, sizeof(buf));
			// Input sentence 
			printf("Input sentence: ");
			scanf("%s", buf);
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			gettimeofday(&start_time, NULL);
			memset(buf, 0, sizeof(buf));
			// Reply
			recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			gettimeofday(&later_time, NULL);
			printf("Reply from server : %s\n", buf);
			// Caculate Time Diff
			if (later_time.tv_usec - start_time.tv_usec < 1000)
				printf("Response time : 0.%lu ms\n", later_time.tv_usec - start_time.tv_usec);
			else
				printf("Response time : %lu.%lu ms\n", (later_time.tv_usec - start_time.tv_usec) / 1000, (later_time.tv_usec - start_time.tv_usec) % 1000);
			memset(buf, 0, sizeof(buf));
		}
		else if (menu == 3) {
			// Send
			strcpy(buf, "3");
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			gettimeofday(&start_time, NULL);
			memset(buf, 0, sizeof(buf));
			// Reply
			recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			gettimeofday(&later_time, NULL);
			printf("Reply from server : %s\n", buf);
			// Caculate Time Diff
			if (later_time.tv_usec - start_time.tv_usec < 1000)
				printf("Response time : 0.%lu ms\n", later_time.tv_usec - start_time.tv_usec);
			else
				printf("Response time : %lu.%lu ms\n", (later_time.tv_usec - start_time.tv_usec) / 1000, (later_time.tv_usec - start_time.tv_usec) % 1000);
		}
		else if (menu == 4) {
			// Send 
			strcpy(buf, "4");
			sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
			gettimeofday(&start_time, NULL);
			memset(buf, 0, sizeof(buf));
			// Reply
			recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
			gettimeofday(&later_time, NULL);
			printf("Reply from server : %s\n", buf);
			// Caculate Time Diff
			if (later_time.tv_usec - start_time.tv_usec < 1000)
				printf("Response time : 0.%lu ms\n", later_time.tv_usec - start_time.tv_usec);
			else
				printf("Response time : %lu.%lu ms\n", (later_time.tv_usec - start_time.tv_usec) / 1000, (later_time.tv_usec - start_time.tv_usec) % 1000);
		}
		else if (menu == 5) {
			printf("Bye bye~\n");
			close(sock);
			return 0;
		}
		// Exception 
		else {
			printf("One more check your input\n");
		}
		// Processing error related buffer
		while (getchar() != '\n');
		menu = -1;
	}
	close(sock);
	return 0;
}