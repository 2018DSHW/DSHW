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
    int size = 1000;
    int spl = 3;
    qDebug()<<"size:"<<size;
    int id = 0;
    QVector<int> temp;
    int featurenum = 9;
    for (int i = 0;i < featurenum;i++)
    {
        temp.push_back(1);
    }
    my_tree.SetFeatureNum(featurenum);
    my_tree.SetSplitNum(spl);
    my_tree.Insert(id,temp);
    id ++;
    for (int i = 2;i < size;i++)
    {
        for(int j = 0;j < featurenum;j++)
        {
            temp[j] = 2 * i;
        }


        my_tree.Insert(id,temp);
        qDebug()<<id<<"\n";
        if(id == 568)
        {
            int a = 0;
        }
        id ++;
    }
    QVector<int> to_find;
    for (int i = 0;i < featurenum;i++)
    {
        to_find.push_back(50);
    }
    to_find = my_tree.find(to_find,2);
    for (int i = 0;i < to_find.size();i++)
    {
        qDebug()<<QString::number(to_find[i])<<"\n";
    }
    qDebug()<<my_tree.access_time<<"times";
    my_tree.Clear();
}
