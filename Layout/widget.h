#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QGroupBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QGroupBox *groupbox_1, *groupbox_2, *groupbox_3;
    QTextEdit   *content;
    QLabel  *txt_1,*txt_2,*txt_3;
    QLineEdit *line_1,*line_2,*line_3;
    QPushButton *button_1,*button_2,*button_3;
    QIcon *icon;
    QImage *image;
};

#endif // WIDGET_H
