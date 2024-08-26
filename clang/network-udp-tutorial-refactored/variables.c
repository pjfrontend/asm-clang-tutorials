#include "variables.h"

void server_usage(void)
{
    fprintf(stderr, "timeserv [server_address] port\n");
    exit(0);
}

void client_usage(void)
{
    fprintf(stderr, "Usage: timecli server_address port [client_address]\n");
    exit(0);
}

char send_buffer[SIZE] = "GET TIME\r\n";

void clean_up_and_shutdown(SOCKET sd)
{
    if (sd != INVALID_SOCKET)
    {
        closesocket(sd);
    }
    WSACleanup();
    exit(0);
}