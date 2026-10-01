#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    connect(ui->btnA, &QPushButton::clicked, this, [&, this]() {
        a++;
        ui->labVoteResult->setText(QString("A:%1  B:%2  C:%3").arg(a).arg(b).arg(c));
    });

    connect(ui->btnB, &QPushButton::clicked, this, [&, this]() {
        b++;
        ui->labVoteResult->setText(QString("A:%1  B:%2  C:%3").arg(a).arg(b).arg(c));
    });

    connect(ui->btnC, &QPushButton::clicked, this, [&, this]() {
        c++;
        ui->labVoteResult->setText(QString("A:%1  B:%2  C:%3").arg(a).arg(b).arg(c));
    });

    connect(ui->btnReset, &QPushButton::clicked, this, [&, this]() {
        a = 0;
        b = 0;
        c = 0;
        ui->labVoteResult->setText(QString("A:%1  B:%2  C:%3").arg(a).arg(b).arg(c));
    });
}

mainWindow::~mainWindow()
{
    delete ui;
}
