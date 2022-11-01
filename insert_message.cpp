#include "insert_message.h"
#include "ui_insert_message.h"


insert_message::insert_message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insert_message)
{
    ui->setupUi(this);
    info  = new info_entry () ;
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(vedio_update()));
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
}

insert_message::~insert_message()
{
    delete ui;
}


//确认按钮，现在完成的功能：提取用户输入的文字信息，并发送给父窗口
//文字信息（message）是一串字符串，姓名，性别，身份信息用空格隔开
//完整功能还需添加保存图片
void insert_message::on_pushButton_clicked()
{
    QString name  = ui->lineEdit->text();
    QString gender  = ui->lineEdit_2->text();
    QString identify  = ui->lineEdit_3->text();
    QString message;
    message=name+" "+gender+" "+identify;
    emit sendData(message);
    QMessageBox::information(this,tr("消息"),tr("添加成功！"));
    close();
}


//拍照按钮，需要一个工具人图片展示拍照结果
void insert_message::on_pushButton_2_clicked()
{
    //写图片
    cv::Point text_lb = cv::Point(largestRect.x, largestRect.y);
    int lt_x = min(text_lb.x, srcImage.cols);
    lt_x = max(0, text_lb.x);
    int lt_y = min(text_lb.y, srcImage.rows);
    lt_y = max(0, text_lb.y);
    int h = min(largestRect.height, srcImage.rows - lt_y - 1);
    int w = min(largestRect.width, srcImage.cols - lt_x - 1);

    largestRect = Rect(lt_x, lt_y, w, h);
    cv::Mat show_temp;
    src(largestRect).copyTo(show_temp);
    cv::flip(show_temp, show_temp, 1);
    cv::imwrite("img/show_temp.png", show_temp);
    cv::Mat  show_src;
    cv::flip(src, show_src, 1);
    cv::imwrite("img/show_src.png", show_src);

    QImage image1 = QImage("img/show_temp.png");
    ui->picture->setPixmap(QPixmap::fromImage(image1));
    ui->picture->show();
}

void insert_message::paintEvent(QPaintEvent *event)
{
    QImage image1 = QImage((uchar*)(image_fliped.data), image_fliped.cols, image_fliped.rows, QImage::Format_RGB888);
    ui->camera->setPixmap(QPixmap::fromImage(image1));
    //照片自适应label大小↓
    image1.scaled(ui->camera->size(), Qt::KeepAspectRatio);
    ui->camera->show();
}

void insert_message::vedio_update(){
    capture>>srcImage;
    src = srcImage.clone();//保存RGB原始图像

    cv::flip(srcImage, image_fliped, 1);

    if(image_fliped.data)
    {
        cvtColor(image_fliped, image_fliped, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        this->update();  //发送刷新消息
    }
}

cv::Rect insert_message::findLargestRect(std::vector<cv::Rect>faces)
{
    int largestIndex = 0;
    int largestArea = faces[largestIndex].width * faces[largestIndex].height;

    for (int i = 0;i < faces.size();i++)
    {
        int nowArea = faces[i].width * faces[i].height;
        if (nowArea > largestArea)
        {
            largestArea = nowArea;
            largestIndex = i;
        }
    }

    return faces[largestIndex];
}
