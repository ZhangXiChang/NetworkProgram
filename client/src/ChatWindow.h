#pragma once
#include <QWidget>

#include <hv/TcpServer.h>
#include <hv/TcpClient.h>

#include <iostream>

namespace Ui
{
    class ChatWindow;
} // namespace Ui

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    ChatWindow(QString ip, QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::ChatWindow *mUi = nullptr;
    hv::TcpServer *mTcpServer = nullptr;
    hv::TcpClient *mTcpClient = nullptr;
    hv::SocketChannelPtr mServerSocket;
    std::vector<hv::SocketChannelPtr> mClientSocketList;
    int mLocalPort;

private:
    void InitLibHV();
    void ConnectMediationServer(std::string ip);
    void CreateServer();
};
