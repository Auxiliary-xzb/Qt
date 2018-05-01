#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = 0);

signals:
    void Return();

public slots:
    void returnPage();

protected:
    void closeEvent(QCloseEvent *);

private:
    QPushButton *button;
};

#endif // MYDIALOG_H
