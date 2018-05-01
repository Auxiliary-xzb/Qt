#include "mydialog.h"
#include "ui_mydialog.h"
#include "calculate.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    connect(ui->button_dengyu, SIGNAL(clicked()), this, SLOT(on_dengyu_clicked()));
    calculate c = new calculate();
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_lineEdit_textEdited(const QString &arg1)
{
    QString text = ui->lineEdit->text();
    int i = arg1.toInt();
    if(i != 0 || text.length() != 0){
        text.append(arg1);
        ui->lineEdit->setText(text);
    }
}

void MyDialog::on_button_0_clicked()
{
    QString text = ui->button_0->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_1_clicked()
{
    QString text = ui->button_1->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_2_clicked()
{
    QString text = ui->button_2->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_3_clicked()
{
    QString text = ui->button_3->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_4_clicked()
{
    QString text = ui->button_4->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_5_clicked()
{
    QString text = ui->button_5->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_6_clicked()
{
    QString text = ui->button_6->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_7_clicked()
{
    QString text = ui->button_7->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_8_clicked()
{
    QString text = ui->button_8->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_button_9_clicked()
{
    QString text = ui->button_9->text();
    emit on_lineEdit_textEdited(text);
}

void MyDialog::on_dengyu_clicked(){
    result = ui->lineEdit->text()
}
