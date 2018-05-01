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

private:
    QMenuBar *menubar;
    QMenu *menu;
    QAction *action;
    QGroupBox *horizontal, *grid, *form;
    QPushButton *button_1, *button_2, *button_3, *button_4;
    QLabel *label_1, *label_2, *label_3, *label_4, *label_5, *label_6;
    QLineEdit *lineedit_1, *lineedit_2, *lineedit_3, *lineedit_4;
    QTextEdit *testedit_1 , *testedit_2;
    QSpinBox *spinbox;
    QComboBox *combox;
    QDialogButtonBox *dialog;
};

#endif // DIALOG_H
