#include "detailed.h"
#include "ui_detailed.h"

detailed::detailed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detailed)
{
    ui->setupUi(this);
}

detailed::~detailed()
{
    delete ui;
}

void detailed::on_pushButton_clicked()
{
    if(ui->lineEdit->text().trimmed()!=NULL&&ui->lineEdit_2->text().trimmed()!=NULL){
        model->setTable("entry");
        model->select();
        ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->tableView->setModel(model);
    }
}

