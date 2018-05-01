#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*
     * QImage在QPixmap的基础上还可以加入图片的格式，
     * QImage::Format_ARGB32该属相中的A表示的透明度。
     * 该属性表示背景为透明。
    */
    QImage image(400, 400, QImage::Format_ARGB32);

    QPainter painter;
    painter.begin(&image);
    //绘图
    painter.drawPixmap(0, 0, 200, 200, QPixmap(":/new/prefix1/picture/a.jpeg"));
   //对绘图设备的前50个像素点进行修改
    for(int i = 0; i < 50; i++){
        for(int j = 0 ; j < 50; j++){
            image.setPixel(QPoint(i, j), qRgb(0, 255, 0));
            //   image.setPixelColor(i, j, QColor(0, 255, 0));
        }
    }

    painter.end();

    //可以看见最后图片中只有200*200大小的图片为原图片，其余区域为透明。
    image.save("../change.png");
}

Widget::~Widget()
{
    delete ui;
}
