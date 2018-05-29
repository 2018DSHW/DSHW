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

    my_tree = new RTree();

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
    int size = 1000;
    qDebug()<<"size:"<<size;
    int id = 0;
    QVector<int> temp;
    temp.push_back(1);
    temp.push_back(1);
    my_tree.Insert(id,temp);
    id ++;
    for (int i = 2;i < size;i++)
    {
        temp[0] = i;
        temp[1] = i;
        my_tree.Insert(id,temp);
        id ++;
    }
    QVector<int> to_find;
    to_find.push_back(50);
    to_find.push_back(50);
    to_find = my_tree.find(to_find);
    for (int i = 0;i < to_find.size();i++)
    {
        qDebug()<<QString::number(to_find[i])<<"\n";
    }
    qDebug()<<my_tree.access_time<<"times";
    my_tree.Clear();
}
