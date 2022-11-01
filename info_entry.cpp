#include "info_entry.h"
#include "ui_info_entry.h"


info_entry::info_entry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_entry)
{

    arrayModel->setTable("student");
    arrayModel->select();
    ui->setupUi(this);
    //关联信号和槽函数
//    insert_message *son = new insert_message;
//    connect(son, SIGNAL(sendData(QStringList)), this, SLOT(receiveData(QStringList)));
//    son->show();
    ui->inquire_button->setIcon(QIcon(":/image/view.png"));
    ui->delete_button->setIcon(QIcon(":/image/delete.png"));
    ui->insert_button->setIcon(QIcon(":/image/add.png"));
    ui->detail_button->setIcon(QIcon(":/image/menu.png"));
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(arrayModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

info_entry::~info_entry()
{
    delete ui;
}

//查找
void info_entry::on_inquire_button_clicked()
{

    QString name=ui->lineEdit->text();
        if(name.length()==0){
            arrayModel->setTable("student");
            arrayModel->select();
        }else{
            QString str=QString("UserName like '%%1%'").arg(name);
            arrayModel->setFilter(str);
            arrayModel->select();
        }
}

//删除
void info_entry::on_delete_button_clicked()
{

    QItemSelectionModel *oneModel=ui->tableView->selectionModel();
    QModelIndexList oneList=oneModel->selectedRows();
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "删除", "确认是否删除?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        for(int i=0;i<oneList.size();i++){
            arrayModel->removeRow(oneList.at(i).row());
        }
        arrayModel->submitAll();
        QMessageBox::information(this,tr("消息"),tr("删除成功！"));
        arrayModel->setTable("student");
        arrayModel->select();
        RowCont--;
    }else{
        arrayModel->revertAll();
    }
}

//插入
void info_entry::on_insert_button_clicked()
{
    insert_message* insert = new insert_message;
    insert->setWindowTitle("信息录入");
    connect(insert,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    insert->show();
//    int RowCont;
//    RowCont=arrayModel->rowCount();
//    arrayModel->insertRow(RowCont);//增加一行
//    //插入元素
//    arrayModel->setData(arrayModel->index(RowCont,0),RowCont+1);
//    arrayModel->setData(arrayModel->index(RowCont,1),"ymx");
//    arrayModel->setData(arrayModel->index(RowCont,2),"女");
//    arrayModel->setData(arrayModel->index(RowCont,3),"居民");

}

void info_entry::receiveData(QString message){
    QStringList messages = message.split(" ");
    //插入元素
    arrayModel->insertRow(RowCont);//增加一行
    arrayModel->setData(arrayModel->index(RowCont,0),RowCont+1);
    arrayModel->setData(arrayModel->index(RowCont,1),messages[0]);
    arrayModel->setData(arrayModel->index(RowCont,2),messages[1]);
    arrayModel->setData(arrayModel->index(RowCont,3),messages[2]);
    RowCont++;
//调试用
//    ui->lineEdit->setText(message);
}

void info_entry::on_detail_button_clicked()
{
    detailed* de = new detailed;
    de->setWindowTitle("出入记录查询");
    de->show();
}
