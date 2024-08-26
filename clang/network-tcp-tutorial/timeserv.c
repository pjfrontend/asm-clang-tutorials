/* timeserv.c */
/* A simple TCP server that sends the current date and time to the client */
/* Last modified: July 16, 2024 */
/* http://www.gomorgan89.com */
/* Link with library file wsock32.lib */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define BUFFER_SIZE 4096

void usage(void);

int main(int argc, char **argv)
{
	WSADATA w;					/* Used to open windows connection */
	unsigned short port_number; /* Port number to use */
	int a1, a2, a3, a4;			/* Components of address in xxx.xxx.xxx.xxx form */
	int client_length;			/* Length of client struct */
	SOCKET sd, client_sd;		/* Socket descriptors */
	struct sockaddr_in server;	/* Information about the server */
	struct sockaddr_in client;	/* Information about the client */
	char buffer[BUFFER_SIZE];	/* Where to store received data */
	struct hostent *hp;			/* Information about this computer */
	char host_name[256];		/* Name of the server */
	time_t current_time;		/* Current time */

	/* Interpret command line */
	if (argc == 2)
	{
		/* Use local address */
		if (sscanf(argv[1], "%u", &port_number) != 1)
		{
			usage();
		}
	}
	else if (argc == 3)
	{
		/* Copy address */
		if (sscanf(argv[1], "%d.%d.%d.%d", &a1, &a2, &a3, &a4) != 4)
		{
			usage();
		}
		if (sscanf(argv[2], "%u", &port_number) != 1)
		{
			usage();
		}
	}
	else
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

	/* Set address automatically if desired */
	if (argc == 2)
	{
		/* Get host name of this computer */
		gethostname(host_name, sizeof(host_name));
		hp = gethostbyname(host_name);

		/* Check for NULL pointer */
		if (hp == NULL)
		{
			fprintf(stderr, "Could not get host name.\n");
			closesocket(sd);
			WSACleanup();
			exit(0);
		}

		/* Assign the address */
		server.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
		server.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
		server.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
		server.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
	}
	/* Otherwise assign it manually */
	else
	{
		server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)a1;
		server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)a2;
		server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)a3;
		server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)a4;
	}

	/* Bind address to socket */
	if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Could not bind name to socket.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Listen for connections */
	if (listen(sd, 5) == -1)
	{
		fprintf(stderr, "Error listening on socket.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Print out server information */
	printf("Server running on %u.%u.%u.%u\n", (unsigned char)server.sin_addr.S_un.S_un_b.s_b1,
		   (unsigned char)server.sin_addr.S_un.S_un_b.s_b2,
		   (unsigned char)server.sin_addr.S_un.S_un_b.s_b3,
		   (unsigned char)server.sin_addr.S_un.S_un_b.s_b4);
	printf("Press CTRL + C to quit\n");

	/* Loop and get data from clients */
	while (1)
	{
		client_length = (int)sizeof(struct sockaddr_in);

		/* Accept a connection from a client */
		client_sd = accept(sd, (struct sockaddr *)&client, &client_length);
		if (client_sd == INVALID_SOCKET)
		{
			fprintf(stderr, "Could not accept connection.\n");
			closesocket(sd);
			WSACleanup();
			exit(0);
		}

		/* Receive bytes from client */
		int bytes_received = recv(client_sd, buffer, BUFFER_SIZE, 0);
		if (bytes_received < 0)
		{
			fprintf(stderr, "Could not receive data.\n");
			closesocket(client_sd);
			continue;
		}

		/* Check for time request */
		if (strcmp(buffer, "GET TIME\r\n") == 0)
		{
			/* Get current time */
			current_time = time(NULL);

			/* Send data back */
			if (send(client_sd, (char *)&current_time, (int)sizeof(current_time), 0) != (int)sizeof(current_time))
			{
				fprintf(stderr, "Error sending data.\n");
				closesocket(client_sd);
				continue;
			}
		}

		closesocket(client_sd);
	}
	closesocket(sd);
	WSACleanup();

	return 0;
}

void usage(void)
{
	fprintf(stderr, "timeserv [server_address] port\n");
	exit(0);
}
