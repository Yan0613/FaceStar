#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <login.h>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDate>


using namespace cv;
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);


private:
    Ui::MainWindow *ui;
    cv::VideoCapture capture;
    QLabel* camera;
    QTimer theTimer;
    cv::Mat srcImage;
    cv::Mat image_fliped;
    int index = 0;
private:
    QPushButton *setting;
    QPushButton *open_camera;
    QPushButton *close_camera;

private slots:
    void setting_pushed();
    void vedio_update();
    void open_camera_pushed();
    void close_camera_pushed();

};


#endif // MAINWINDOW_H
