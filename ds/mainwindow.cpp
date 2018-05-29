#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFile>
#include<QDir>
#include<QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,700);
    find=new QPushButton(this);
    find->setText("search!");
    find->setGeometry(330,260,400,80);//
    picture=new QPushButton(this);
    picture->setText(" ");
    picture->setGeometry(20,30,300,300);
    next=new QPushButton(this);
    next->setText("next");
    next->setGeometry(330,50,200,100);
    before=new QPushButton(this);
    before->setText("before");
    before->setGeometry(330,160,200,100);
    for(int i=0;i<8;i++){
   result[i]=new QPushButton(this);
   result[i]->setGeometry(100*i,370,100,100);
   result[i]->setFlat(true);
    }
    for(int i=8;i<16;i++){
   result[i]=new QPushButton(this);
   result[i]->setGeometry(100*(i-8),480,100,100);
     result[i]->setFlat(true);
    }
    for(int i=16;i<24;i++){
   result[i]=new QPushButton(this);
   result[i]->setGeometry(100*(i-16),590,100,100);
     result[i]->setFlat(true);
    }
  //各个button定义
    loadimage();
   // 加载图片，即提取txt中的文件名到pictureid
    present_PID=0;// 当前正在展示的（最大的）图片的ID
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
    QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
    //图片展示
    dl= new QDial(this);
    dl->setRange(0,picture_num-1);
    // 用next before button 进行小调，dial进行大调

    dl->setGeometry(550,70,200,200);
    connect(next,SIGNAL(clicked(bool)),this,SLOT(nextp())); //next 选择下一个图
    connect(before,SIGNAL(clicked(bool)),this,SLOT(beforep()));//before 选择上一个图
    connect(find,SIGNAL(clicked(bool)),this,SLOT(findsimilar()));//开始计算     @xiao@sasa 你们要在这里添加你的函数
    connect(dl,SIGNAL(valueChanged(int)),this,SLOT(change(int)));//选择图片



}

MainWindow::~MainWindow()
{
    delete ui;
}

//选择图片
void MainWindow::nextp()
{
    if(present_PID<picture_num-1)
    present_PID++;
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
     qDebug()<<present_PID;

}
void MainWindow::beforep(){
    if(present_PID>0)
    present_PID--;
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
     qDebug()<<present_PID;
}

void MainWindow::change(int a){
        present_PID=a;
   QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
    qDebug()<<present_PID;
}
//加载图片
/*
      int present_PID;  这个是 现在要找的原图的ID
      int picture_num;   图片的总个数 5613
      int num_of_result;     相似的图的个数
      QString picture_ID[10000];   图的ID对应的文件名
       int result_of_r[40];    把结果得出的ID 输入到这里吧
       再改一改相对文件地址之类应该就可以了
 */
void MainWindow::loadimage()
{
     int i=0;
    QFile file(":/file/image");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        i++;
        QByteArray line = file.readLine();
        QString str(line);
        picture_ID[i-1]=str;
    }
    picture_num=i;
qDebug()<<picture_num-1;

QFile file2(":/file/feature");
if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
{
    qDebug()<<"Can't open the file!"<<endl;
}
int id = -2;
while(!file2.atEnd())
{
    QByteArray line = file2.readLine();
     int tmp[9];
     QString str(line);
     str=str.replace(QString("rect"), QString(""));
     str=str.replace(QString(" "), QString(","));
     QString number;
     for(int j=1;j<10;j++){
     number=str.section(",",j,j);
      tmp[j-1] = number.toInt()/100;

     }
  //  qDebug()<< str<<"bbb";//<<tmp;
    QVector<int> temp;
     for(int i=0;i<9;i++){
    temp.push_back(tmp[i]);
    if(id>=0)
    feature[id].push_back(tmp[i]);
     }
     if(id>=0)
    my_tree.Insert(id,temp);
   qDebug()<< "id:"<<id;
   qDebug()<< temp;
   id++;
}





}
//从这里开始就可以@sasa@xiao
void MainWindow::findsimilar(){
  //  QTime time;
    //  time.start();
      QVector<int> to_find;

      for(int i=0;i<9;i++)
      to_find.push_back(6);
       qDebug() <<to_find;
   //    qDebug() <<feature[present_PID];
      int size = 5613;
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

           QVector<int> find;
  qDebug()<<feature[present_PID];

           find = my_tree.find(feature[present_PID]);
           /*
           for (int i = 0;i < to_find.size();i++)
           {
               qDebug()<<QString::number(to_find[i])<<"\n";
           }
           qDebug()<<my_tree.access_time<<"times";
           my_tree.Clear();*/
   /*   for (int i = 0;i < to_find.size();i++)
      {
          qDebug()<<QString::number(to_find[i])<<"\n";
      }*/
 //     qDebug() << time.elapsed() / 1000.0 << "s";
   //  num_of_result= ?
   //   result_of_r[i]=?;
//  showresult();
}
//显示
void MainWindow::showresult(){

   for(int i=0;i<num_of_result;i++){
    QString temp = picture_ID[result_of_r[i]].left(picture_ID[result_of_r[i]].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    result[i]->setStyleSheet(loadpic);
   }
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
               temp[j] = i;
           }

           my_tree.Insert(id,temp);
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
