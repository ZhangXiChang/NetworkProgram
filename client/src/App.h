#pragma once
#include <QApplication>
#include <ConnectServerWindow.h>
#include <ChatWindow.h>

#include <iostream>

class App : public QObject
{
    Q_OBJECT

public:
    App(int argc, char *argv[]);
    ~App();

private:
    QApplication *mApplication = nullptr;
    ConnectServerWindow *mConnectServerWindow = nullptr;
    ChatWindow *mChatWindow = nullptr;
};
