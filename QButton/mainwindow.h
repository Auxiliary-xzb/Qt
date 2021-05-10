#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void canChanged(int checkedNum);

public  slots:
    void changeCheckAll(int state);
    void doChange(int checkNum);

private:
    Ui::MainWindow *ui;
    int selected;
};
#endif // MAINWINDOW_H
