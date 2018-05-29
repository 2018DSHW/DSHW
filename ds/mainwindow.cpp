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
    int size = 100;
    int spl = 3;
    qDebug()<<"size:"<<size;
    int id = 0;
    QVector<int> temp;
    QVector<QVector<int>> num;
    int featurenum = 9;
    for (int i = 0;i < featurenum;i++)
    {
        temp.push_back(1);
    }
    num.push_back(temp);
    my_tree.SetFeatureNum(featurenum);
    my_tree.SetSplitNum(spl);
    my_tree.Insert(id,temp);
    id ++;
    for (int i = 2;i < size;i++)
    {
        for(int j = 0;j < featurenum;j++)
        {
            temp[j] = rand() % 10;
        }
        num.push_back(temp);
        my_tree.Insert(id,temp);
        id ++;
        qDebug()<<"id:"<<id<<temp;
    }
    QVector<int> to_find;
    for (int i = 0;i < featurenum;i++)
    {
        to_find.push_back(1);
    }
    qDebug()<<"to find:"<<to_find<<"\n";

    to_find = my_tree.find(to_find,0);


    for (int i = 0;i < to_find.size();i++)
    {
        qDebug()<<to_find[i]<<" "<<num[to_find[i]]<<"\n";
    }
    qDebug()<<my_tree.access_time<<"times";
    my_tree.Clear();
}
