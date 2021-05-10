#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x = 0;
}
void Widget::paintEvent(QPaintEvent *event){
    //方法一：
    // QPainter p(this);
    //方法二：
    QPainter q;//定义画家对象
    q.begin(this);//指定当前窗口为绘图设备，并且QPainter为活动状态

    /*
     * 在不想添加资源时，可以将图片放在该项目文件的上一层目录，然后再获取。
     * 因为添加资源每次在编译时都会很慢。
     * 注意，一定要是上层目录。
    */
    //  q.drawPixmap(0, 0, this->width(), this->height(), QPixmap("../image/bk.jpg"));
    //和上面是等价的，第一个参数是直接获取窗口的矩形区域。
    //q.drawPixmap(this->rect(), QPixmap("../image/bk.jpg"));

    //定义画笔
    //QPen pen;
    //pen.setWidth(2);    //设置线宽度
    //pen.setColor(Qt::red);//设置颜色
    //pen.setStyle(Qt::DashDotDotLine);//设置画笔风格

    //定义画刷子
    //QBrush brush;
    //brush.setColor(Qt::blue);
    //brush.setStyle(Qt::Dense7Pattern);

    //将画笔交给画家
   // q.setPen(pen);
    //q.setBrush(brush);

    //画直线
    //q.drawLine(50, 50, 300, 300);
    //画矩形
    //q.drawRect(100, 100, 50, 100);
    /*
     * 以画椭圆的基础来画圆， Ellipse为椭圆。
        */
    //q.drawEllipse(QPoint(50, 50), 40, 40);
    //q.drawEllipse(this->rect());

    //q.drawPixmap(x, 100, 80, 80, QPixmap("../image/bk.jpg"));


    //////////////////////////////////////////////////////////高级操作///////////////////////////////////////////
    //抗锯齿能力
    q.setRenderHint(QPainter::Qt4CompatiblePainting);
    q.drawEllipse(QPoint(100, 100), 20, 20);

    //移动画家
    q.translate(100, 0);
     q.drawEllipse(QPoint(100, 100), 20, 20);

     //保存画家的状态
     q.save();
     q.translate(100, 0);
     q.drawRect(100, 100,  50, 50);

     //恢复画家状态
     q.restore();
     q.drawRect(100, 100,  80, 80);

    q.end();//指定QPainter为不活动。
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    x += 20;
    if(x > this->width()){
        x = 0;
    }
    /*
     *      Updates the widget unless updates are disabled or the widget is hidden.
     *      This function does not cause an immediate repaint; instead it schedules a paint event
     *  for processing when Qt returns to the main event loop. This permits Qt to optimize for
     *  more speed and less flicker than a call to repaint() does.
     *      Calling update() several times normally results in just one paintEvent() call.
     *      Qt normally erases the widget's area before the paintEvent() call. If the Qt::WA_OpaquePaintEvent
     * widget attribute is set, the widget is responsible for painting all its pixels with an opaque color.
     *
     * 大致翻译：
     *      更新widget，除非update不可用或者widget隐藏。
     *      该函数不曹成一个立即重绘，而是安排一个绘图事件为该程序当Qt返回到主事件
     * 循环时。这允许Qt优化更多的速度和更少的闪烁，相对于repaint()函数。
     *      调用update()多次通常在paintEvent()中只有一个结果。
     *      Qt通常在相应paintEvent()之前擦拭widget的区域。如果部件的Qt::WA_OpaquePaintEvent
     * 属性设置了，widget相应绘制所有的像素点用一个不透明的像素点。
    */
    //所有重绘时，调用update()比调用repaint()好，速度会更快，闪烁会更少。
    update();
}
