#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFile>
#include<QDir>

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
    present_PID=1;// 当前正在展示的（最大的）图片的ID
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
    QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
    //图片展示
    dl= new QDial(this);
    dl->setRange(1,picture_num);
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
    if(present_PID<picture_num)
    present_PID++;
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);

}
void MainWindow::beforep(){
    if(present_PID>2)
    present_PID--;
    QString temp = picture_ID[present_PID].left(picture_ID[present_PID].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    picture->setStyleSheet(loadpic);
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
    QFile file("/Users/imjs/imageindex/imagelist.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        i++;
        QByteArray line = file.readLine();
        QString str(line);
        picture_ID[i]=str;
    }
    picture_num=i;
qDebug()<<picture_num;
}
//从这里开始就可以@sasa@xiao
void MainWindow::findsimilar(){









   //  num_of_result= ?
   //   result_of_r[i]=?;
  showresult();
}
//显示
void MainWindow::showresult(){

   for(int i=0;i<num_of_result;i++){
    QString temp = picture_ID[result_of_r[i]].left(picture_ID[result_of_r[i]].length()-1);
     QString loadpic= "QPushButton{border-image:url(/Users/imjs/imageindex/image/"+temp+");}";
    result[i]->setStyleSheet(loadpic);
   }
}

