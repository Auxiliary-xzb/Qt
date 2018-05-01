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

    connect(action, SIGNAL(triggered()), this, SLOT(close()));

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
    button_1 = new QPushButton("Button_1");
    button_2 = new QPushButton("Button_2");
    button_3 = new QPushButton("Button_3");
    button_4 = new QPushButton("Button_4");
    hbox_layout->addWidget(button_1);
    hbox_layout->addWidget(button_2);
    hbox_layout->addWidget(button_3);
    hbox_layout->addWidget(button_4);

    /*
     * 创建一个groupbox，让它的布局为以上布局
    */
    horizontal = new QGroupBox("Horizontal Layout");
    horizontal->setLayout(hbox_layout);


}


void Dialog::creategrid(){
    QGridLayout *grid_1ayout = new QGridLayout();
    label_1 = new QLabel("line 1:");
    label_2 = new QLabel("line 2:");
    label_3 = new QLabel("line 3:");
    lineedit_1 = new QLineEdit();
    lineedit_2 = new QLineEdit();
    lineedit_3 = new QLineEdit();
    testedit_1 = new QTextEdit();
    /*
     * 设置纯文本
    */
    testedit_1->setPlainText("This widget takes up about two thirds of the "
                             "grid layout.");
    grid_1ayout->addWidget(label_1, 1, 0);
    grid_1ayout->addWidget(label_2, 2, 0);
    grid_1ayout->addWidget(label_3, 3, 0);
    grid_1ayout->addWidget(lineedit_1, 1, 1);
    grid_1ayout->addWidget(lineedit_2, 2, 1);
    grid_1ayout->addWidget(lineedit_3, 3, 1);
    //从0行2列延伸到4行2列
    grid_1ayout->addWidget(testedit_1, 0, 2, 4, 2);

    grid = new QGroupBox("Grid Layout");
    grid->setLayout(grid_1ayout);
}


void Dialog::createform(){
    QFormLayout *form_layout = new QFormLayout();
    label_4 = new QLabel("line 1:");
    label_5 = new QLabel("line 2, long text:");
    label_6 = new QLabel("line 3:");
    lineedit_4 = new QLineEdit();
    combox = new QComboBox();
    spinbox = new QSpinBox();
    form_layout->addRow(label_4, lineedit_4);
    form_layout->addRow(label_5, combox);
    form_layout->addRow(label_6,spinbox);

    form = new QGroupBox("Form Layout");
    form->setLayout(form_layout);
}
