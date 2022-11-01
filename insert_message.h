#ifndef INSERT_MESSAGE_H
#define INSERT_MESSAGE_H

#include <QWidget>

#include <QSqlQuery>
#include <mainwindow.h>
#include <QMessageBox>
#include <info_entry.h>
#include <ui_info_entry.h>


class info_entry;


namespace Ui {
class insert_message;
}

class insert_message : public QWidget
{
    Q_OBJECT

public:
    explicit insert_message(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    cv::Rect findLargestRect(std::vector<cv::Rect>faces);
    ~insert_message();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private slots:
    void vedio_update();
private:
    Ui::insert_message *ui;
    info_entry* info;
signals:
    void sendData(QString); //用来传递数据的信号
private:
    cv::VideoCapture capture;
    QTimer theTimer;
    cv::Mat srcImage;
    cv::Mat image_fliped;
    //检测出的人脸
    std::vector<cv::Rect> faces;
    int count = 0;
    cv::Rect largestRect;
    cv::Mat src;
    //retinaface
};

#endif // INSERT_MESSAGE_H
