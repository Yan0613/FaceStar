#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QTextCodec>
#include <QDir>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));

//建立图片文件夹，通过index实现与用户信息的通信
    QDir *folder = new QDir;
    bool exist = folder->exists("img");
    if (!exist){
        folder->mkpath("img");
    }

    QFile databaseFile("database.db");
    if (!databaseFile.exists())
    {
        QSqlDatabase database;
        QSqlQuery sql_query;
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("database.db");
        if(!database.open())
           {
               qDebug() << "Error: Failed to connect database." << database.lastError();
           }
           else
           {
               qDebug() << "Succeed to connect database.";
           }
        // 创建表格
        sql_query = database.exec("DROP TABLE student");
        // 先清空一下表，可按需添加此句
        //    sql_query.exec("DROP TABLE student");
        // 创建表格student
        if(!sql_query.exec("create table student(UserId int primary key, UserName text,Gender text,Identity text)"))
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
        // 填充表
        if(!sql_query.exec("INSERT INTO student VALUES(1, '魏正阳', '男','居民')"))
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "add one created!";
        }
        // 批量填充表
        QStringList names;
        names << "小A" << "小B" << "小C" << "小D" << "小E" << "小F" << "小G" << "小H" << "小I";

        QStringList gender;
        gender << "男" << "女" << "女" << "男" << "男" << "男" << "女" << "男" << "女";

        QStringList identity;
        identity << "居民" << "装修工" << "水电工" << "清洁工" << "居民" << "居民" << "居民" << "居民" << "居民";
        sql_query.prepare("INSERT INTO student (UserId, UserName, Gender,Identity) "
                              "VALUES (:UserId, :UserName, :Gender,:Identity)");
            qint8 i = 0;
            foreach (QString name, names) // 从names表里获取每个名字
            {
                sql_query.bindValue(":UserId", i+2); // 向绑定值里加入名字
                sql_query.bindValue(":UserName", name); // 姓名
                sql_query.bindValue(":Gender",gender[i]);
                sql_query.bindValue(":Identity", identity[i]); // 班级

                if(!sql_query.exec())
                {
                    qDebug() << "Error: Fail." << sql_query.lastError();
                }
                i++;
            }

            //进出记录
            // 创建表格
            sql_query = database.exec("DROP TABLE entry");
            // 先清空一下表，可按需添加此句
            //    sql_query.exec("DROP TABLE student");
            // 创建表格student
            if(!sql_query.exec("create table entry(Time text)"))
            {
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
            // 填充表

            QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
            QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");
            sql_query.prepare("INSERT INTO entry (Time) "
                                  "VALUES (:Time)");
            sql_query.bindValue(":Time",str);
            sql_query.exec();
            sql_query.exec("INSERT INTO entry VALUES('2022-07-02 09:47:44')");
            sql_query.exec("INSERT INTO entry VALUES('2022-07-02 10:40:34')");
    }
    QSqlDatabase database;
    QSqlQuery sql_query;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    if(!database.open())
       {
           qDebug() << "Error: Failed to connect database." << database.lastError();
       }
       else
       {
           qDebug() << "Succeed to connect database.";
       }

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("门禁系统");
    w.show();
    return a.exec();
}
