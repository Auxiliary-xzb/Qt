#ifndef ADDSTRETCH_H
#define ADDSTRETCH_H

#include <QWidget>
#include <QCloseEvent>

class AddStretch : public QWidget
{
    Q_OBJECT
public:
    explicit AddStretch(QWidget *parent = 0);

virtual void closeEvent(QCloseEvent *event);

signals:
    void Return();
    void Close();

private slots:
    void EmitReturn();
};

#endif // ADDSTRETCH_H
