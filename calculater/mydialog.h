#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT
private:
        int result;
public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

signals:
    void dengyu_clicked(QString);
private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_button_0_clicked();

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_dengyu_clicked();
private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
