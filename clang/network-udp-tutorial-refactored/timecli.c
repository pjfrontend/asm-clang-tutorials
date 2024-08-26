/* timecli.c */
/* Gets the current time from a UDP server */
/* Last modified: September 23, 2005 */
/* http://www.gomorgan89.com */
/* Link with library file wsock32.lib */
#include "variables.h"

int main(int argc, char **argv)
{
	/* Make sure command line is correct */
	if (argc != 3 && argc != 4)
	{
		client_usage();
	}
	if (sscanf(argv[1], "%d.%d.%d.%d", &a1, &a2, &a3, &a4) != 4)
	{
		client_usage();
	}
	if (sscanf(argv[2], "%u", &port_number) != 1)
	{
		client_usage();
	}
	if (argc == 4)
	{
		if (sscanf(argv[3], "%d.%d.%d.%d", &b1, &b2, &b3, &b4) != 4)
		{
			client_usage();
		}
	}

	/* Open windows connection */
	if (WSAStartup(WINSOCK_VERSION_1_1, &w) != 0)
	{
		fprintf(stderr, "Could not open Windows connection.\n");
		exit(0);
	}

	/* Open a datagram socket */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == INVALID_SOCKET)
	{
		fprintf(stderr, "Could not create socket.\n");
		clean_up_and_shutdown(sd);
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

	/* Clear out client struct */
	memset((void *)&client, '\0', sizeof(struct sockaddr_in));

	/* Set family and port */
	client.sin_family = AF_INET;
	client.sin_port = htons(0);

	if (argc == 3)
	{
		/* Get host name of this computer */
		gethostname(host_name, sizeof(host_name));
		hp = gethostbyname(host_name);

		/* Check for NULL pointer */
		if (hp == NULL)
		{
			fprintf(stderr, "Could not get host name.\n");
			clean_up_and_shutdown(sd);
		}

		/* Assign the address */
		client.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
		client.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
		client.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
		client.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
	}
	else
	{
		client.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)b1;
		client.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)b2;
		client.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)b3;
		client.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)b4;
	}

	/* Bind local address to socket */
	if (bind(sd, (struct sockaddr *)&client, sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Cannot bind address to socket.\n");
		clean_up_and_shutdown(sd);
	}

	/* Tranmsit data to get time */
	server_length = sizeof(struct sockaddr_in);
	if (sendto(sd, send_buffer, (int)strlen(send_buffer) + 1, 0, (struct sockaddr *)&server, server_length) == -1)
	{
		fprintf(stderr, "Error transmitting data.\n");
		clean_up_and_shutdown(sd);
	}

	/* Receive time */
	if (recvfrom(sd, (char *)&current_time, (int)sizeof(current_time), 0, (struct sockaddr *)&server, &server_length) < 0)
	{
		fprintf(stderr, "Error receiving data.\n");
		clean_up_and_shutdown(sd);
	}

	/* Display time */
	printf("Current time: %s", ctime(&current_time));
	clean_up_and_shutdown(sd);
}
