#include "App.h"

App::App(int argc, char *argv[])
{
    mApplication = new QApplication(argc, argv);

    mConnectServerWindow = new ConnectServerWindow;
    connect(mConnectServerWindow->GetConnectToServerButton(), QPushButton::pressed, this,
            [this]()
            {
                mConnectServerWindow->close();
                mChatWindow = new ChatWindow(mConnectServerWindow->GetIPLineEdit()->text());
                mChatWindow->show();
            });
    //
    mConnectServerWindow->show();

    mApplication->exec();
}
App::~App()
{
    if (mConnectServerWindow != nullptr)
    {
        delete mConnectServerWindow;
    }
    if (mChatWindow != nullptr)
    {
        delete mChatWindow;
    }
    if (mApplication != nullptr)
    {
        delete mApplication;
    }
}
