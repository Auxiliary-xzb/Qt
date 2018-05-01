#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_Delete_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Traverse_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Submit_clicked();

    void on_pushButton_Select_clicked();

    void on_pushButton_Cancle_clicked();

    void on_pushButton_Delete_view_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase open_database;
    QSqlTableModel *model;
};

#endif // WIDGET_H
