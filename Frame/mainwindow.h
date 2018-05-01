#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QLabel>
#include <QIcon>
#include <QStatusBar>
#include <QAction>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void dealmodal();
    void dealmodeless();

private:
    QMenuBar *menubar;
    QMenu *menu_1, *menu_2;
    QToolBar *toolbar;
    QStatusBar *statusbar;
    QLabel *label, *label_2, *label_3;
    QIcon *icon;
    QPushButton *button_1, *button_2;
    QAction *action_1, *action_2, *action_3;
    QDockWidget *dockwidget[4];
};

#endif // MAINWINDOW_H
