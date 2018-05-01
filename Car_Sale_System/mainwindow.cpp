#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(900, 650);
    //默认页面
    ui->stackedWidget->setCurrentWidget(ui->Car_Manage);
    ui->Title->setText("车辆管理");

    ui->pushButton_Confirm->setEnabled(false);
    ui->spinBox_Count->setEnabled(false);
    ui->spinBox_Count->setMinimum(0);

    connectDatabase();
    initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDatabase(){
    //开启数据库
    mydatabase = QSqlDatabase::addDatabase("QSQLITE");
    mydatabase.setDatabaseName("../car.db");

    if( !mydatabase.open() ){
        QString error = mydatabase.lastError().text();
        QMessageBox::warning(this, tr("Warning"), tr("%1").arg(error));
        return;
    }
}

//初始化数据
void MainWindow::initData(){
    //读取工厂信息
    QSqlQuery query;
    query.exec("select * from factory");

    //将读取的信息添加到combobox中
    while(query.next()){
        ui->comboBox_Factory->addItem(query.value(1).toString());
    }

    /*
     *  第二种方式添加数据
     * QSqlQueryModel *queryModel = new QSqlQueryModel(this);
     * queryModel->setQuery("select * from factory");
     *
     * ui->comboBox_Factory->setModel(queryModel);
     *
     */
}

//车辆管理
void MainWindow::on_actionA_triggered()
{
    //切换页面
    ui->stackedWidget->setCurrentWidget(ui->Car_Manage);
    //标签改变文字
    ui->Title->setText("车辆管理");
}


//销售管理
void MainWindow::on_action2_triggered()
{
    //切换页面
    ui->stackedWidget->setCurrentWidget(ui->Car_Calculate);
    //标签改变文字
    ui->Title->setText("销售管理");
}

//工厂下拉
void MainWindow::on_comboBox_Factory_currentIndexChanged(const QString &arg1)
{
    //默认是大小写敏感,一样返回0
    //arg1.compare("请选择厂家");
    if(ui->comboBox_Factory->currentIndex() == 0){
        //内容情况
        ui->comboBox_Brand->clear();    //品牌下拉框清空
        ui->lineEdit_Offer->clear();    //报价清空
        ui->lineEdit_Price->clear();    //价格清空
        ui->label_Left_Number->setText("0"); //剩余数量清空
        ui->spinBox_Count->setValue(0);     //数量清空
    }else{
        QString sql = QString("select name from brand where factory = '%1'").arg(arg1);
        //取出数据
        QSqlQuery query;
        query.exec(sql);

        //先将项目清空
        ui->comboBox_Brand->clear();
        //设置品牌
        while(query.next()){
            //获取查询到的品牌名，添加到combox的项目中
            ui->comboBox_Brand->addItem(query.value(0).toString());
        }
        ui->spinBox_Count->setEnabled(true);
        ui->pushButton_Confirm->setEnabled(true);
    }
}

//品牌下拉框
void MainWindow::on_comboBox_Brand_currentIndexChanged(const QString &arg1)
{
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'")
            .arg(ui->comboBox_Factory->currentText())
            .arg(arg1);
    //取出数据
    QSqlQuery query;
    query.exec(sql);

    //设置报价
    while(query.next()){
        int price = query.value("price").toInt();
        int last = query.value("last").toInt();
        ui->lineEdit_Offer->setText( QString::number(price) );
        ui->label_Left_Number->setText( QString::number(last) );
    }

    //保存最大数量
    left_number = ui->label_Left_Number->text().toInt();
    //设置最大值
    ui->spinBox_Count->setMaximum(left_number);
}

//数量框
void MainWindow::on_spinBox_Count_valueChanged(int arg1)
{
    /*
     * 当数量框数字变化时，会将报价乘上数量，得到金额。
     * 剩余的数量也会改变
     */

    //获取报价
    int price = ui->lineEdit_Offer->text().toInt();
    //求出金额
    int total_price = price*arg1;
    //设置总金额
    ui->lineEdit_Price->setText( QString::number(total_price) );

    //每次用总剩余数量减去当前选中数量即为剩余数量
    int rest_number = left_number - arg1;
    //设置剩余值
    ui->label_Left_Number->setText( QString::number(rest_number) );
}

//直接改变厂家下拉框的索引号
void MainWindow::on_pushButton_Cancle_clicked()
{
    //设置当前的次序
    ui->comboBox_Factory->setCurrentIndex(0);
    //情况剩余量，因为当恢复到“请选择厂家”页面时，你的品牌也变了，所以在品牌中调用了。
    ui->label_Left_Number->setText("0");
}

void MainWindow::on_pushButton_Confirm_clicked()
{

}
