/* timecli.c */
/* Gets the current time from a TCP server */
/* Last modified: July 16, 2024 */
/* http://www.gomorgan89.com */
/* Link with library file wsock32.lib */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock.h>

#define SIZE 500

void usage(void);

int main(int argc, char **argv)
{
	WSADATA w;								 /* Used to open Windows connection */
	unsigned short port_number;				 /* The port number to use */
	SOCKET sd;								 /* The socket descriptor */
	char send_buffer[SIZE] = "GET TIME\r\n"; /* Data to send */
	time_t current_time;					 /* Time received */
	struct hostent *hp;						 /* Information about the server */
	struct sockaddr_in server;				 /* Information about the server */
	int a1, a2, a3, a4;						 /* Server address components in xxx.xxx.xxx.xxx form */
	char host_name[256];					 /* Host name of this computer */

	/* Make sure command line is correct */
	if (argc != 3)
	{
		usage();
	}
	if (sscanf(argv[1], "%d.%d.%d.%d", &a1, &a2, &a3, &a4) != 4)
	{
		usage();
	}
	if (sscanf(argv[2], "%u", &port_number) != 1)
	{
		usage();
	}

	/* Open windows connection */
	if (WSAStartup(0x0101, &w) != 0)
	{
		fprintf(stderr, "Could not open Windows connection.\n");
		exit(0);
	}

	/* Open a stream socket */
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == INVALID_SOCKET)
	{
		fprintf(stderr, "Could not create socket.\n");
		WSACleanup();
		exit(0);
	}

	/* Clear out server struct */
	memset((void *)&server, '\0', sizeof(struct sockaddr_in));

	/* Set family and port */
	server.sin_family = AF_INET;
	server.sin_port = htons(port_number);

	/* Set server address */
	server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)a1;
	server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)a2;
	server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)a3;
	server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)a4;

	/* Connect to the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Could not connect to server.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Transmit data to get time */
	if (send(sd, send_buffer, (int)strlen(send_buffer) + 1, 0) == -1)
	{
		fprintf(stderr, "Error transmitting data.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Receive time */
	if (recv(sd, (char *)&current_time, (int)sizeof(current_time), 0) < 0)
	{
		fprintf(stderr, "Error receiving data.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Display time */
	printf("Current time: %s", ctime(&current_time));

	closesocket(sd);
	WSACleanup();

	return 0;
}

void usage(void)
{
	fprintf(stderr, "Usage: timecli server_address port\n");
	exit(0);
}
