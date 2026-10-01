#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

class MyWindow : public QMainWindow//继承
{
    Q_OBJECT//发信号的身份证

public:
    explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow() override;
};
#endif // MYWINDOW_H
