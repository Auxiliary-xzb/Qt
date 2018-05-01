#ifndef MYPIECE_H
#define MYPIECE_H

#include <QWidget>

class MyPiece : public QWidget
{
    Q_OBJECT
public:
    explicit MyPiece(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // MYPIECE_H
