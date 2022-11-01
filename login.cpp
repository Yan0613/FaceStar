#include "login.h"
#include "ui_login.h"
#include <QDialog>
#include <QMessageBox>
#include <info_entry.h>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    if(ui->lineEdit->text().trimmed()==tr("admin")
            &&ui->lineEdit_2->text().trimmed()==tr("123456")){
        is_admin = true;
        close();
        info_entry* info = new info_entry();
        info->show();
        info->setWindowTitle("信息管理");

    }else{
       QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);

        // 清空输入框内容
       ui->lineEdit->clear();
       ui->lineEdit_2->clear();

       //光标定位
       ui->lineEdit->setFocus();

    }
}

void login::on_pushButton_2_clicked()
{
    close();
}
