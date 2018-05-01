#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDatabase();
    void initData();

private slots:
    void on_actionA_triggered();

    void on_action2_triggered();

    void on_comboBox_Factory_currentIndexChanged(const QString &arg1);

    void on_comboBox_Brand_currentIndexChanged(const QString &arg1);

    void on_spinBox_Count_valueChanged(int arg1);

    void on_pushButton_Cancle_clicked();

    void on_pushButton_Confirm_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mydatabase;
    int left_number;
};

#endif // MAINWINDOW_H
