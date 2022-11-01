#ifndef DETAILED_H
#define DETAILED_H
#include <QtSql>
#include <QWidget>
#include <QTableView>

namespace Ui {
class detailed;
}

class detailed : public QWidget
{
    Q_OBJECT

public:
    explicit detailed(QWidget *parent = 0);
    ~detailed();

private slots:
    void on_pushButton_clicked();
public:
    QSqlTableModel *model= new QSqlTableModel();
private:
    Ui::detailed *ui;
};

#endif // DETAILED_H
