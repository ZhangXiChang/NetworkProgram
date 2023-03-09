#include "ConnectServerWindow.h"
#include "ui_ConnectServerWindow.h"

ConnectServerWindow::ConnectServerWindow(QWidget *parent)
    : QWidget(parent), mUi(new Ui::ConnectServerWindow)
{
    mUi->setupUi(this);
}
ConnectServerWindow::~ConnectServerWindow()
{
    if (mUi != nullptr)
    {
        delete mUi;
    }
}

QPushButton *ConnectServerWindow::GetConnectToServerButton()
{
    return mUi->ConnectToServerButton;
}

QLineEdit *ConnectServerWindow::GetIPLineEdit()
{
    return mUi->IPLineEdit;
}
