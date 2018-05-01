#include "addstretch.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

AddStretch::AddStretch(QWidget *parent) : QWidget(parent)
{

    /*
     * addStretch是将空白区域按比例分配，比例的计算是
     *          该stretch的数值/设置的所有stretch的总和数
    */
    this->setMinimumHeight(500);
    this->setMaximumHeight(500);
    QLabel *test[2];
    for(int i = 0 ; i < 2 ; i++){
           test[i] = new QLabel("test",this);
           test[i]->setStyleSheet("border:2px solid red");
    }
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    QGroupBox *addstretch = new QGroupBox("addStretch", this);
    QVBoxLayout *lay = new QVBoxLayout(this);
    test[0]->setText(tr("上部分设置的stretch为2"));
    lay->addStretch(2);
    lay->addWidget(test[0]);
    test[1]->setText(tr("下部分设置的stretch为1"));
    lay->addWidget(test[1]);
    lay->addStretch(1);
    addstretch->setLayout(lay);

    QPushButton *button = new QPushButton("return", this);
    connect(button, &QPushButton::clicked, this, &AddStretch::EmitReturn);

    mainlayout->addWidget(addstretch);
    mainlayout->addWidget(button);
    this->setLayout(mainlayout);
}

void AddStretch::EmitReturn(){
    emit Return();
}

void AddStretch::closeEvent(QCloseEvent *event){
    emit Close();
}
