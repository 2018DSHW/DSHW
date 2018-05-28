#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTime time;

    time.start();
    test();
    qDebug() << time.elapsed() / 1000.0 << "s";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    int id = 0;
    QVector<int> temp;
    temp.push_back(1);
    temp.push_back(1);
    my_tree.Insert(id,temp);
    id ++;
    for (int i = 2;i < 10000;i++)
    {
        temp[0] = i;
        temp[1] = i;
        my_tree.Insert(id,temp);
        id ++;
    }
}
