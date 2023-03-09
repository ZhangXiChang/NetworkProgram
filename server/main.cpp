#include <hv/TcpServer.h>

#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<hv::SocketChannelPtr> ClientList;
    hlog_disable();
    hv::TcpServer server;
    if (server.createsocket(10270) < 0)
    {
        std::cout << "Socket creation failed" << std::endl;
        return -1;
    }
    server.onConnection = [&ClientList](const hv::SocketChannelPtr &channel)
    {
        if (channel->isConnected())
        {
            ClientList.push_back(channel);
        }
        else
        {
            ClientList.erase(std::remove(ClientList.begin(), ClientList.end(), channel), ClientList.end());
        }
    };
    server.onMessage = [&ClientList](const hv::SocketChannelPtr &channel, hv::Buffer *buffer)
    {
        for (auto &&i : ClientList)
        {
            i->write(buffer);
        }
    };
    server.setThreadNum(4);
    server.start();
    while (getchar() != '\n')
        ;
    return 0;
}
