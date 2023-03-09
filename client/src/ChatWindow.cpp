#include "ChatWindow.h"
#include "ui_ChatWindow.h"

ChatWindow::ChatWindow(QString ip, QWidget *parent)
    : QWidget(parent), mUi(new Ui::ChatWindow)
{
    mUi->setupUi(this);

    InitLibHV();
    ConnectMediationServer(ip.toStdString());

    connect(mUi->SendButton, QPushButton::pressed, this,
            [this]()
            {
                const char *str = mUi->TextInputBox->toPlainText().toStdString().c_str();
                mServerSocket->write(str, sizeof(str));
                mUi->TextInputBox->clear();
            });
    //
}
ChatWindow::~ChatWindow()
{
    if (mTcpClient != nullptr)
    {
        delete mTcpClient;
    }
    if (mTcpServer != nullptr)
    {
        delete mTcpServer;
    }
    if (mUi != nullptr)
    {
        delete mUi;
    }
}

void ChatWindow::InitLibHV()
{
    // 关闭log
    hlog_disable();
}
void ChatWindow::ConnectMediationServer(std::string ip)
{
    mTcpClient = new hv::TcpClient;
    int socketfd = mTcpClient->createsocket(10270, ip.c_str());
    if (socketfd < 0)
    {
        throw std::runtime_error("Socket creation failed");
    }
    so_reuseaddr(socketfd);
    mTcpClient->onConnection = [this](const hv::SocketChannelPtr &channel)
    {
        if (channel->isConnected())
        {
            std::string localPort;
            bool isPortStr = false;
            for (auto &&i : channel->localaddr())
            {
                if (isPortStr)
                {
                    localPort += i;
                }
                if (i == ':')
                {
                    isPortStr = true;
                }
            }
            mLocalPort = std::stoi(localPort);
            mServerSocket = channel;
            CreateServer();
        }
        else
        {
        }
    };
    mTcpClient->onMessage = [this](const hv::SocketChannelPtr &channel, hv::Buffer *buffer)
    {
        mUi->MessageBrowserBox->append((const char *)buffer->data());
    };
    reconn_setting_t reconn;
    reconn_setting_init(&reconn);
    reconn.min_delay = 1000;
    reconn.max_delay = 10000;
    reconn.delay_policy = 2;
    mTcpClient->setReconnect(&reconn);
    mTcpClient->start();
}
void ChatWindow::CreateServer()
{
    mTcpServer = new hv::TcpServer;
    if (mTcpServer->createsocket(mLocalPort) < 0)
    {
        throw std::runtime_error("Socket creation failed");
    }
    mTcpServer->onConnection = [this](const hv::SocketChannelPtr &channel)
    {
        if (channel->isConnected())
        {
            mClientSocketList.push_back(channel);
        }
        else
        {
            mClientSocketList.erase(std::remove(mClientSocketList.begin(), mClientSocketList.end(), channel), mClientSocketList.end());
        }
    };
    mTcpServer->onMessage = [this](const hv::SocketChannelPtr &channel, hv::Buffer *buffer) {
    };
    mTcpServer->setThreadNum(4);
    mTcpServer->start();
}
