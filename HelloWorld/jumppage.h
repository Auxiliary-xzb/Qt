#ifndef JUMPPAGE_H
#define JUMPPAGE_H

#include <QWidget>
#include <QPushButton>

class JumpPage : public QWidget
{
  Q_OBJECT
public:
  explicit JumpPage(QWidget *parent = 0);

signals:
    /*
     * 信号必须有signals关键字修饰
     * 信号没有返回值，但是可以有参数
     * 信号就是函数的什么，只需声明，无需定义
     * 使用：emit ReturnPage()来产生信号
    */
    void ReturnPage();

public slots:

public:
      void DealSolts();

private:
  QPushButton return_button;
};

#endif // JUMPPAGE_H
