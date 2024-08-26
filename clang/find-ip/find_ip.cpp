#include <windows.h>
#include <wininet.h>
#include <string>
#include <iostream>

std::string real_ip()
{
    LPCWSTR ipr = (const WCHAR *)"IP retriever";
    LPCWSTR rawsite = (const WCHAR *)"http://myexternalip.com/raw";
    HINTERNET net = InternetOpen(ipr,
                                 INTERNET_OPEN_TYPE_PRECONFIG,
                                 NULL,
                                 NULL,
                                 0);

    HINTERNET conn = InternetOpenUrl(net,
                                     rawsite,
                                     NULL,
                                     0,
                                     INTERNET_FLAG_RELOAD,
                                     0);

    char buffer[4096];
    DWORD read;

    InternetReadFile(conn, buffer, sizeof(buffer) / sizeof(buffer[0]), &read);
    InternetCloseHandle(net);

    return std::string(buffer, read);
}

int main()

{
    std::cout << real_ip() << "\n";
}