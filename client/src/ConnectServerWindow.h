#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

namespace Ui
{
    class ConnectServerWindow;
} // namespace Ui

class ConnectServerWindow : public QWidget
{
    Q_OBJECT

public:
    ConnectServerWindow(QWidget *parent = nullptr);
    ~ConnectServerWindow();

private:
    Ui::ConnectServerWindow *mUi = nullptr;

public:
    QPushButton *GetConnectToServerButton();
    QLineEdit *GetIPLineEdit();
};
