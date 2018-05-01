#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>         //加数字的框
#include <QComboBox>        //下拉的框
#include <QDialogButtonBox> //确定和取消的组合

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    void createhorizontal();
    void creategrid();
    void createform();

private:
    #define BUTNUM 4
    #define LABNUM 6
    #define LINNUM 4

private:
    QMenuBar *menubar;
    QMenu *menu;
    QAction *action;
    QGroupBox *horizontal, *grid, *form;
    QPushButton *button[BUTNUM];
    QLabel *label[LABNUM];
    QLineEdit *lineedit[LINNUM];
    QTextEdit *testedit_1 , *testedit_2;
    QSpinBox *spinbox;
    QComboBox *combox;
    QDialogButtonBox *dialog;
};

#endif // DIALOG_H
