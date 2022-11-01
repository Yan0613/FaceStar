#ifndef INFO_ENTRY_H
#define INFO_ENTRY_H
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QMessageBox>
#include "insert_message.h"
#include "detailed.h"

class insert_message;

namespace Ui {
class info_entry;
}

class info_entry : public QWidget
{
    Q_OBJECT

public:
    explicit info_entry(QWidget *parent = 0);
    ~info_entry();

public:
    Ui::info_entry *ui;

private slots:
    void on_inquire_button_clicked();
    void on_delete_button_clicked();
    void on_insert_button_clicked();
    void receiveData(QString);   //接收传递过来的数据的槽

    void on_detail_button_clicked();

public :
    QSqlTableModel *arrayModel= new QSqlTableModel();
    int RowCont=10;
};

#endif // INFO_ENTRY_H
