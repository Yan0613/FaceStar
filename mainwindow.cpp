#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDate>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1040,750);

    //识别准确度
    QLabel* lable = new QLabel(this);
    lable->setText("识别结果");
    //设置字体
    QFont ft("Mulish");
    ft.setBold(200);
    ft.setPointSize(15);
    lable->setStyleSheet("Qlabel {font:28;color:black}");
    lable->setFont(ft);
    lable->adjustSize();
    lable->setGeometry(10,20,300,60);
    lable->show();

    //设置主窗体颜色
    this->setStyleSheet("QMainWindow {background-color:rgb(255, 252, 248)}");

    //message
    QImage detail(QString(":/image/BMI (1).png"));
    QLabel* result = new QLabel(this);
    result->setGeometry(640,0,400,750);
    detail.scaled(result->size(),Qt::KeepAspectRatio);
    result->setScaledContents(true);
    result->setPixmap(QPixmap::fromImage(detail));
    result->show();

    //message text
    QLabel* name = new QLabel(result);
    QFont name_font("Mullish");
    name->setFont(name_font);
    QString str_name = "姓名：\n";
    QString str_name_append = "魏正阳";
    str_name+=str_name_append;
    name->setText(str_name);
    name->setStyleSheet("font:5;color:black;font:bold");
    name->setGeometry(35,90,100,80);
    name->show();

    QLabel* age = new QLabel(result);
    QFont age_font("Mullish");
    age->setFont(age_font);
    QString str_age = "人员信息：\n";
    QString str_age_append = "居民";
    str_age += str_age_append;
    age->setText(str_age);
    age->setStyleSheet("font:5;color:black;font:bold");
    age->setGeometry(35,165,100,80);
    age->show();

    QLabel* ok = new QLabel (result);
    QFont ok_font("Mullish",15,75);
    ok->setFont(ok_font);
    ok->setStyleSheet("font:10;color:white;font:bold");
    QString strok = "检测结果：\n";
    QString strok_append="识别成功";
    strok+=strok_append;
    ok->setText(strok);
    ok->setGeometry(180,100,100,80);
    ok->show();

    //message picture
    QLabel* image = new QLabel(result);
    QImage picture(QString(":/image/wzy.jpg"));
    image->setGeometry(25,260,350,450);
    picture.scaled(image->size(),Qt::KeepAspectRatio);
    image->setScaledContents(true);
    image->setPixmap(QPixmap::fromImage(picture));
    image->show();

    //vedio window
    camera  = new QLabel(this);
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(vedio_update()));
//    camera->setGeometry(35,300,550,300);
    if (capture.isOpened())
        return;

    if (capture.open(200)) {
        cout<<"cam is  opened"<<endl;
        //从摄像头捕获视频
        srcImage = Mat::zeros(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(33);
    }else {
        cout<<"cam is not opened"<<endl;
        capture.release();
    }
    //打开视频流



    //appointment
    QImage appo(QString(":/image/Upcoming.png"));
    QLabel* appointment = new QLabel(this);
    appointment->setGeometry(5,600,600,120);
    appo.scaled(appointment->size(),Qt::KeepAspectRatio);
    appointment->setScaledContents(true);
    appointment->setPixmap(QPixmap::fromImage(appo));
    appointment->show();


    QLabel* phone = new QLabel(appointment);
    QFont phone_font("Mullish");
    phone_font.setBold(100);
    phone_font.setPointSize(10);
    phone->setFont(name_font);
    phone->setFont(name_font);
    phone->setText("188-9191-1199");
    phone->setStyleSheet("Qlabel {font:10;color:black}");
    phone->setGeometry(250,40,200,40);
    phone->show();

    QDate date= QDate::currentDate();//获取系统当前的时间
    QString str_date = date.toString("MM-dd");//格式化时间
    QLabel* date_label = new QLabel(appointment);
    date_label->setText(str_date);
    date_label->setStyleSheet("font:2;color:gray;font:bold");
    date_label->setGeometry(500,43,200,40);
    date_label->show();

    //acuuracy
    QImage acc1(QString(":/image/Blood Pressure.png"));
    QLabel* accuracy = new QLabel(this);
    accuracy->setGeometry(15,40,200,240);
    acc1.scaled(accuracy->size(),Qt::KeepAspectRatio);
    accuracy->setScaledContents(true);
    accuracy->setPixmap(QPixmap::fromImage(acc1));
    accuracy->show();

    QImage acc2(QString(":/image/Blood Sugar.png"));
    QLabel* accuracy2 = new QLabel(this);
    accuracy2->setGeometry(220,40,200,240);
    acc1.scaled(accuracy2->size(),Qt::KeepAspectRatio);
    accuracy2->setScaledContents(true);
    accuracy2->setPixmap(QPixmap::fromImage(acc2));
    accuracy2->show();

    QImage acc3(QString(":/image/Heart Rate.png"));
    QLabel* accuracy3 = new QLabel(this);
    accuracy3->setGeometry(425,40,200,240);
    acc1.scaled(accuracy3->size(),Qt::KeepAspectRatio);
    accuracy3->setScaledContents(true);
    accuracy3->setPixmap(QPixmap::fromImage(acc3));
    accuracy3->show();

    //accuracy text
    QLabel* fps = new QLabel(accuracy);
    QFont fps_font("Mullish");
    fps_font.setBold(100);
    fps_font.setPointSize(15);
    fps->setFont(fps_font);
    fps->setFont(fps_font);
    QString str_fps = "刷新率：\n";
    QString str_fps_append = "97";
    str_fps+=str_fps_append;
    fps->setText(str_fps);
    fps->setStyleSheet("Qlabel {font:14;color:black}");
    fps->setGeometry(35,30,100,80);
    fps->show();

    QLabel* percent = new QLabel(accuracy2);
    QFont percent_font("Mullish");
    percent_font.setBold(100);
    percent_font.setPointSize(15);
    percent->setFont(fps_font);
    percent->setFont(fps_font);
    QString str_percent = "准确率：\n";
    QString str_percent_append = "98.6%";
    str_percent+=str_percent_append;
    percent->setText(str_percent);
    percent->setStyleSheet("Qlabel {font:14;color:black}");
    percent->setGeometry(35,30,100,80);
    percent->show();

    QLabel* flow = new QLabel(accuracy3);
    QFont flow_font("Mullish");
    flow_font.setBold(100);
    flow_font.setPointSize(15);
    flow->setFont(fps_font);
    flow->setFont(fps_font);
    QString str_flow = "人流量：\n";
    QString str_flow_append = "13";
    str_flow+=str_flow_append;
    flow->setText(str_flow);
    flow->setText(str_flow);
    flow->setStyleSheet("Qlabel {font:14;color:black}");
    flow->setGeometry(35,30,100,80);
    flow->show();
//admin
    setting = new QPushButton("button",this);
    setting->setGeometry(570,15,40,40);
    setting->show();
    connect(setting, SIGNAL(clicked()), this, SLOT(setting_pushed()));
    setting->setIcon(QPixmap(":/image/setting.png"));//给按钮设置图片
    setting->setIconSize(QSize(40,40));//设置图片大小，前面是长（x），后面是宽（y）
    setting->setText("");//要设置图标，先要把按钮调成没有字的
    setting->setFlat(true);//设置按钮为透明，这样才能显示出图片
//open camera
    QLabel* open = new QLabel(this);
    open->setText("打开摄像头");
    open->setGeometry(500,60,100,25);
    open_camera = new QPushButton("button",this);
    open_camera->setGeometry(495,15,40,40);
    open_camera->show();
    connect(open_camera, SIGNAL(clicked()), this, SLOT(open_camera_pushed()));
    open_camera->setIcon(QPixmap(":/image/camera_icon.png"));//给按钮设置图片
    open_camera->setIconSize(QSize(40,40));//设置图片大小，前面是长（x），后面是宽（y）
    open_camera->setText("");//要设置图标，先要把按钮调成没有字的
    open_camera->setFlat(true);//设置按钮为透明，这样才能显示出图片
//close camera
    QLabel* close = new QLabel(this);
    close->setText("关闭摄像头");
    close->setGeometry(425,60,100,25);
    close_camera = new QPushButton("button",this);
    close_camera->setGeometry(430,15,40,40);
    close_camera->show();
    connect(close_camera, SIGNAL(clicked()), this, SLOT(close_camera_pushed()));
    close_camera->setIcon(QPixmap(":/image/close_camera.png"));//给按钮设置图片
    close_camera->setIconSize(QSize(40,40));//设置图片大小，前面是长（x），后面是宽（y）
    close_camera->setText("");//要设置图标，先要把按钮调成没有字的
    close_camera->setFlat(true);//设置按钮为透明，这样才能显示出图片
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QImage image1 = QImage((uchar*)(image_fliped.data), image_fliped.cols, image_fliped.rows, QImage::Format_RGB888);
    camera->setPixmap(QPixmap::fromImage(image1));
    camera->setGeometry(35,300,550,300);
    image1.scaled(camera->size(), Qt::KeepAspectRatio);
    camera->show();
}

void MainWindow::setting_pushed(){
    capture.release();
    login* log = new login;
    log->show();
    log->setWindowTitle("管理员登录");
}

void MainWindow::open_camera_pushed(){
    capture.open(200);
}

void MainWindow::close_camera_pushed(){
    capture.release();
}

void MainWindow::vedio_update(){
    capture>>srcImage;
    cv::flip(srcImage, image_fliped, 1);

    if(image_fliped.data)
    {
        cvtColor(image_fliped, image_fliped, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        this->update();  //发送刷新消息
    }
}

MainWindow::~MainWindow()
{
    if(capture.isOpened())
        capture.release();
    delete ui;
}

