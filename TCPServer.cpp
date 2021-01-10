#include "TCPServer.h"
#include <exception>

TCPServer::TCPServer(int port)
{
#ifdef _WIN32
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif // _WIN32

    ADDR server;
    mServerSock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;
    if (bind(mServerSock, (struct sockaddr*)&server, sizeof(server)) == -1)
        throw std::runtime_error("bind error");

    listen(mServerSock, 5);
}

TCPServer::~TCPServer()
{
#ifdef _WIN32
    close(mServerSock);
    WSACleanup();
#endif
}

std::pair<SOCKET, TCPServer::ADDR> TCPServer::Accept()
{
    ADDR client;
    int nlen = sizeof(ADDR);
#ifdef _WIN32
    SOCKET sock = accept(mServerSock, (struct sockaddr*)&client, &nlen);
#else
    SOCKET sock = accept(mServerSock, (struct sockaddr*)&client, (socklen_t*)&nlen);
#endif
    if (sock == -1)
        throw std::runtime_error("accept error");
    return std::make_pair(sock, client);
}

void TCPServer::close(SOCKET sock)
{
#ifdef _WIN32
    closesocket(sock);
#else
    ::close(sock);
#endif
}
