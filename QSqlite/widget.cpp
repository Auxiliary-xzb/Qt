#include "widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>
#include <QVariantList>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  /*
   * 这里需要区别一下Qt的数据库链接名字和真是数据库名称。
   * 在创建链接是可以给本次链接指定名字的，这个名字也是
   * Qt可以使用该链接区分一个数据库同时存在多个链接的情况。
   * 默认情况下，不给addDatabase传递参数，那么Qt会自己
   * 给本次链接创建一个默认名称。
   */

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

  /*
   * 指定我们需要链接的数据库名称，注意和本次数据库链接的
   * 名称区分开来。
   */
  db.setDatabaseName("../data.db");

  //设置完链接属性后就开启数据库
  if (!db.open()) {
    QMessageBox::warning(this, tr("Warning"), tr("Can't open the database!"));
    return;
  }

  QSqlQuery query, query_1, query_2, query_3, query_4, query_5, query_6;
  query.exec(
      "create table student(id int primary key, name varchar(255),age int, "
      "score int);");
  //插入语句，跟android里的一样的，都是sqlite
  query.exec(
      "insert into student(id, name, age, score) values(1, '二狗', 10, 35)");

  //绑定值的方式，文档中给出了四种方式
  //方式一
  query_1.prepare(
      "insert into student(name, age, score) values(:name, :age, :score)");
  query_1.bindValue(":name", "黄鑫");
  query_1.bindValue(":age", 20);
  query_1.bindValue(":score", 99);
  query_1.exec();

  //方式二
  query_2.prepare(
      "insert into student(name, age, score) values(:name, :age, :score)");
  query_2.bindValue(0, "熊二");
  query_2.bindValue(1, 20);
  query_2.bindValue(2, 99);
  query_2.exec();

  //方法三
  query_3.prepare("insert into student(name, age, score) values(?, ?, ?)");
  query_3.bindValue(0, "熊大");
  query_3.bindValue(1, 20);
  query_3.bindValue(2, 59);
  query_3.exec();

  //方法四
  query_4.prepare("insert into student(name, age, score) values(?, ?, ?)");
  query_4.addBindValue("雄黄");
  query_4.addBindValue(23);
  query_4.addBindValue(60);
  query_4.exec();

  //批量处理数据
  //预处理可以直接提交一批指令而不再是上述的一条语句一条语句的执行
  query_5.prepare("insert into student(name, age, score) values(?, ?, ?)");
  QVariantList nameList_1;
  nameList_1 << "王小二"
             << "王二小"
             << "小熊";
  QVariantList ageList_1;
  ageList_1 << 20 << 23 << 30;
  QVariantList scoreList_1;
  scoreList_1 << 59 << 69 << 79;
  query_5.addBindValue(nameList_1);
  query_5.addBindValue(ageList_1);
  query_5.addBindValue(scoreList_1);
  //执行预处理
  query_5.execBatch();

  query_6.prepare(
      "insert into student(name, age, score) values(:name, :age, :score)");
  QVariantList nameList_2;
  nameList_2 << "王八蛋"
             << "龟孙"
             << "都是";
  QVariantList ageList_2;
  ageList_2 << 20 << 23 << 30;
  QVariantList scoreList_2;
  scoreList_2 << 59 << 49 << 29;
  query_6.bindValue(":name", nameList_2);
  query_6.bindValue(":age", ageList_2);
  query_6.bindValue(":score", scoreList_2);
  query_6.execBatch();

  db.close();

  open_database = QSqlDatabase::database();

  // The QSqlTableModel class provides an editable data model for a single
  // database table. 该类提供一个可操作的数据模型为一个数据库表
  model = new QSqlTableModel(this);
  //选择表
  model->setTable("mail");
  /*
   * QSqlTableModel::OnFieldChange：
   * All changes to the model will be applied immediately to the database.
   * 默认的是只要修改表格中的数据，数据库立即修改
   *
   * QSqlTableModel::OnManualSubmit:
   *      All changes will be cached in the model until either submitAll()
   * or revertAll() is called.
   * 该属性是在调用特定函数后才去改数据库.submitAll()之后才会真实修改数据库
   */
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  //改变属性名字
  model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
  model->setHeaderData(2, Qt::Horizontal, tr("年龄"));

  //设置model
  ui->tableView->setModel(model);
  //不显示第0列
  ui->tableView->hideColumn(0);
  //设置view中的数据不能修改。
  //    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  model->select();
}

Widget::~Widget() { delete ui; }

void Widget::on_pushButton_Delete_clicked() {
  if (!open_database.isOpen()) {
    return;
  }

  QString name = ui->lineEdit->text();
  QString sql = QString("delete from student where name = '%1'").arg(name);

  //开启事务的好处是可以回滚事务。
  /*
   * Returns the database connection called connectionName.
   * The database connection must have been previously added with addDatabase().
   * If open is true (the default) and the database connection is not already
   * open it is opened now.
   *
   * 返回数据库连接，该数据库链接必须已经使用addDatabase()添加过了的。如果连接没开启参数open
   * 为true，则开启该数据库链接.
   */
  QMessageBox::StandardButton button =
      QMessageBox::question(this, tr("Hint"), tr("Do is right now?"));
  if (open_database.transaction()) {
    qDebug() << "transaction finished!";
  } else {
    qDebug() << open_database.lastError().text();
  }
  QSqlQuery query;
  query.exec(sql);
  if (button == QMessageBox::Yes) {
    //开启事务后还需要提交事务,事务一旦提交就无法回滚了。持久性是事务的特性。
    if (open_database.commit()) {
      qDebug() << "commit finished!";
    } else {
      qDebug() << open_database.lastError().text();
    }
  } else if (button == QMessageBox::No) {
    //回滚事务
    if (!open_database.rollback()) {
      qDebug() << open_database.lastError().text();
    } else {
      qDebug() << "rollback finished!";
    }
  }
}

void Widget::on_pushButton_Open_clicked() {
  if (!open_database.isOpen()) {
    bool isOK = open_database.open();
    if (isOK) {
      //如果打开则显示数据库
      //选择表
      model->setTable("student");
      model->setEditStrategy(QSqlTableModel::OnManualSubmit);
      //显示表
      model->select();
      //改变属性名字
      model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
      model->setHeaderData(2, Qt::Horizontal, tr("年龄"));

      //设置model
      ui->tableView->setModel(model);
      //不显示第0列
      ui->tableView->hideColumn(0);
      //设置view中的数据不能修改。
      //    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
      qDebug() << "database open!";
    }
  } else {
    qDebug() << "database has already open!";
  }
}

void Widget::on_pushButton_Close_clicked() {
  if (open_database.isOpen()) {
    open_database.close();
    //关闭数据库后清屏
    this->model->clear();
    qDebug() << "database close!";
  }
}

void Widget::on_pushButton_Traverse_clicked() {
  if (!open_database.isOpen()) {
    return;
  }

  QSqlQuery query;
  qDebug() << query.exec("select * from student");
  /*
   * To access the data returned by a query, use value(int)
   * 使用value(int)去获得查询语句返回的数据。
   */
  while (query.next()) {
    qDebug() << query.value(1).toString().toUtf8().data()
             << query.value(2).toString().toInt()
             << query.value(3).toString().toInt();
  }
}

void Widget::on_pushButton_Add_clicked() {
  //根据当前表创建空记录
  QSqlRecord record = model->record();
  //获取记录数
  int rowCount = model->rowCount();
  //在显示时，输入完了数据后，左侧是'*'表示没保存，只有在数据保存后才显示行号
  model->insertRecord(rowCount, record);
}

void Widget::on_pushButton_Submit_clicked() { model->submitAll(); }

void Widget::on_pushButton_Select_clicked() {
  if (ui->lineEdit_2->text().isEmpty()) {
    return;
  }

  /*
   * setFilter()方法更简单，只需要输入where语句即可。
   * 上诉函数在调用完select()函数后生效
   */
  QString sql = QString("select * from student where name = '%1'")
                    .arg(ui->lineEdit_2->text());
  QSqlQuery query;
  query.exec(sql);
  while (query.next()) {
    qDebug() << query.value(1).toString().toUtf8().data()
             << query.value(2).toString().toInt()
             << query.value(3).toString().toInt();
  }
}

void Widget::on_pushButton_Cancle_clicked() {
  //取消所有动作
  model->revertAll();
}

void Widget::on_pushButton_Delete_view_clicked() {
  //获取选中的模型
  QItemSelectionModel *sModel = ui->tableView->selectionModel();
  //取出模型的索引
  QModelIndexList list = sModel->selectedIndexes();
  qDebug() << list.size();
  //删除给出索引的行
  for (int i = 0; i < list.size(); i++) {
    model->removeRow(list[i].row());
  }
}
