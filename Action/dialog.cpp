#include "dialog.h"
#include <QLayout>
#include <QFormLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    menubar = new QMenuBar(this);
    menu = new QMenu("File");
    action = menu->addAction("Exit");
    menubar->addMenu(menu);

    this->createhorizontal();
    this->creategrid();
    this->createform();

    testedit_2 = new QTextEdit("This widget takes up all"
                               " the remaining space in the "
                               "top-level layout.");

    dialog = new QDialogButtonBox(this);
    dialog->addButton(QDialogButtonBox::Ok);
    dialog->addButton(QDialogButtonBox::Cancel);

    //主布局
    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(horizontal);
    main_layout->addWidget(grid);
    main_layout->addWidget(form);
    main_layout->addWidget(testedit_2);
    main_layout->addWidget(dialog);
    /*
     * 在这里如果没有这一句的话，menubar就设置的不对
     * 为什么能在这里加menubar是因为在帮助里查找menubar时，显示了layout显示格式
    */
    main_layout->setMenuBar(menubar);
    setLayout(main_layout);
}

Dialog::~Dialog()
{

}

void Dialog::createhorizontal(){
    QHBoxLayout *hbox_layout = new QHBoxLayout();
    for(int i = 0 ; i < BUTNUM ; i++ )
        button[i] = new QPushButton(QString("Button_%1").arg(i+1));

    for(int i = 0 ; i < BUTNUM ; i++ )
        hbox_layout->addWidget(button[i]);
    /*
     * 创建一个groupbox，让它的布局为以上布局
    */
    horizontal = new QGroupBox("Horizontal Layout");
    horizontal->setLayout(hbox_layout);

}


void Dialog::creategrid(){
    QGridLayout *grid_1ayout = new QGridLayout();
    for(int i = 0 ; i < LABNUM-3 ; i++)
        label[i] = new QLabel(QString("line %1").arg(i+1));
    for(int i = 0 ; i < LINNUM-1 ; i++)
        lineedit[i] = new QLineEdit();


    testedit_1 = new QTextEdit();
    /*
     * 设置纯文本
    */
    testedit_1->setPlainText("This widget takes up about two thirds of the "
                             "grid layout.");

    for(int i = 0 ; i < 3 ; i++){
        grid_1ayout->addWidget(label[i], i+1, 0);
        grid_1ayout->addWidget(lineedit[i], i+1, 1);
    }
    //从0行2列延伸到4行2列
    grid_1ayout->addWidget(testedit_1, 0, 2, 4, 2);

    grid = new QGroupBox("Grid Layout");
    grid->setLayout(grid_1ayout);
}


void Dialog::createform(){
    QFormLayout *form_layout = new QFormLayout();
    label[3] = new QLabel("line 1:");
    label[4] = new QLabel("line 2, long text:");
    label[5] = new QLabel("line 3:");
    lineedit[3] = new QLineEdit();
    combox = new QComboBox();
    spinbox = new QSpinBox();
    form_layout->addRow(label[3], lineedit[3]);
    form_layout->addRow(label[4], combox);
    form_layout->addRow(label[5],spinbox);

    form = new QGroupBox("Form Layout");
    form->setLayout(form_layout);
}
