#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<Qpainter>
#include<QPixmap>
#include<QDial>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QPushButton   *find;
     QPushButton   *picture;
      QPushButton   *next;
      QPushButton   *before;
      QPushButton   *result[40];
      QDial *dl;
      int present_PID;
      int picture_num;
      int num_of_result;
      int result_of_r[40];
      QString picture_ID[10000];
   public slots:

    void beforep();
    void nextp();
    void change(int num);
    void loadimage();
    void showresult();
    void findsimilar();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
