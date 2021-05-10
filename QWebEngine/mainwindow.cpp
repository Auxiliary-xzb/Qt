#include "mainwindow.h"

#include "ui_mainwindow.h"

static QVector<QString> getDataFiled(const QString &tableNmae);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /*
   * 在所有的QWebEngineView没有加载完之前，主窗口的resizeEvent事件
   * 不会调用JS的setSize。
   */
  this->changedEchartCount = 0;
  this->doEchartChange = false;

  //添加要访问的数据库中的表名
  dbTableNames.push_back("mail");
  dbTableNames.push_back("lol");
  dbTableNames.push_back("video");
  dbTableNames.push_back("direct");
  dbTableNames.push_back("find");

  //将ui中的控件放在数组中，这样好操作
  urls.push_back(QUrl("qrc:///html/src/line-stack.html"));
  urls.push_back(QUrl("qrc:///html/src/multiple-y-axis.html"));
  urls.push_back(QUrl("qrc:///html/src/pie-simple.html"));
  urls.push_back(QUrl("qrc:///html/src/radar-aqi.html"));
  urls.push_back(QUrl("qrc:///html/src/sunburst-visualMap.html"));

  webs.push_back(ui->web_1);
  webs.push_back(ui->web_2);
  webs.push_back(ui->web_3);
  webs.push_back(ui->web_4);
  webs.push_back(ui->web_5);

  tableViews.push_back(ui->tableView_1);
  tableViews.push_back(ui->tableView_2);
  tableViews.push_back(ui->tableView_3);
  tableViews.push_back(ui->tableView_4);
  tableViews.push_back(ui->tableView_5);

  /*
   * js: Uncaught ReferenceError : setSize is not defined
   * 在第一次主窗口显示时就会有有reszieEvent事件，此时就需要
   * js调用setSize函数，因为在html中的div一开始写死了echarts
   * 的大小，所以需要上述加载完成后立马进行setSize。
   * 出现上述情况是因为第一次主窗口在加载完时上述的load操作没
   * 有完成。所以就需要一个标志判断上述加载完成，然后调用resizeEvent。
   *
   * 但显然不能调用resizeEvent，所以必须提供一个额外的槽函数，
   * 使得resizeEvent通过判断标志来通知echarts改变大小。
   */
  //加载表格，并注册信号
  for (int i = 0; i < urls.size(); i++) {
    webs[i]->load(urls[i]);
    connect(webs[i], &QWebEngineView::loadFinished, this,
            &MainWindow::resizeEcharts);
  }
  /*
   * 链接数据库，这里要先建立链接才能设置model，因为它的构造需要
   * 一个数据库
   */

  connectDataBase();

  /*
   *   初始化数据表模式，并将tableView设置为该模式，然后存
   *   储这个model用于后面数据处理时候用。
   */
  for (int i = 0; i < tableViews.size(); i++) {
    QSqlTableModel *model = new QSqlTableModel(tableViews[i]);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableViews[i]->setModel(model);
    dbModels.push_back(model);
  }

  //初始化用来传送数据的JSON数组
  data = QVector<QJsonArray>(5, QJsonArray());
}

MainWindow::~MainWindow() { delete ui; }

/*
 * 设置本次数据库链接，并开启数据库
 */
void MainWindow::connectDataBase() {
  db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName("../data.db");

  if (!db.open()) {
    QMessageBox::warning(this, tr("警告"), tr("访问数据库失败。"));
    return;
  }
}

/*
 * 使用JSON传递当前QWebEngineView的大小给
 * setSize函数，从而修改echarts的大小。
 */
void MainWindow::resizeEcharts() {
  /*
   * 每加载完一个QWebEngineView就记录，只有全部加载完后才会
   * 让resizeEvent接受Echarts的改变大小工作。
   */
  if (this->doEchartChange == false) {
    this->changedEchartCount++;
    if (this->changedEchartCount == ui->stackedWidget->count()) {
      this->doEchartChange = true;
    }
  }

  QJsonObject sender;
  sender.insert("width", ui->stackedWidget->currentWidget()->width());
  sender.insert("height", ui->stackedWidget->currentWidget()->height());

  QString str = QJsonDocument(sender).toJson();
  QString js = QString("setSize(%1)").arg(str);

  /*
   * 每次更改时都要提醒其他的所有窗口都更改
   */
  int total = ui->stackedWidget->count();
  for (int i = 0; i < total; i++) {
    QWebEngineView *view =
        dynamic_cast<QWebEngineView *>(ui->stackedWidget->widget(i));
    view->page()->runJavaScript(js);
  }
}

/*
 * 切换stackWidget的内容，并且切换comboBox的内容
 */
void MainWindow::on_pushButton_clicked() {
  int total = ui->stackedWidget->count();
  int currentIndex = ui->stackedWidget->currentIndex();

  currentIndex++;
  if (currentIndex >= total) currentIndex = 0;
  ui->stackedWidget->setCurrentIndex(currentIndex);
  ui->comboBox->setCurrentIndex(currentIndex);
}

/*
 * 显示数据并发送给图表
 */
void MainWindow::on_openButton_clicked() {
  //准备图表的字段栏并且读取数据
  for (int m = 0; m < dbModels.size(); m++) {
    //设置表名
    ui->tabWidget->setTabText(m, dbTableNames[m]);
    //获取当前model处理的表格的字段
    QVector<QString> field = getDataFiled(dbTableNames[m]);

    int j = 1;
    for (auto i = field.begin() + 1; i != field.end(); i++) {
      dbModels[m]->setHeaderData(j, Qt::Horizontal, *i);
      j++;
    }

    //每个model负责读取一张表
    dbModels[m]->setTable(dbTableNames[m]);
    dbModels[m]->select();

    //每个表格都不显示第一列
    tableViews[m]->hideColumn(0);
  }

  //保存所有获取到的数据
  QVector<int> tmp = {0, 0, 0, 0, 0, 0, 0};
  //遍历每一个表
  for (int tableIndex = 0; tableIndex < dbModels.size(); tableIndex++) {
    //遍历每一个表中的行
    for (int tableLine = 0; tableLine < dbModels[tableIndex]->rowCount();
         tableLine++) {
      //遍历每一个表中的列
      for (int tableRow = 0; tableRow < tmp.size(); tableRow++) {
        //将第i个表的第j行的第row+1列的值自增到tmp的第row个元素中
        tmp[tableRow] +=
            dbModels[tableIndex]->record(tableLine).value(tableRow + 1).toInt();
      }
    }

    //每个表的数据增加完成后就放入到要JSON数组中
    for (int c = 0; c < tmp.size(); c++) {
      data[tableIndex].push_back(tmp[c]);
    }
    tmp = {0, 0, 0, 0, 0, 0, 0};
  }

  //向所有的表格中发送数据
  QJsonObject sender;

  for (int i = 0; i < data.size(); i++) {
    sender.insert(QString("data%1").arg(i + 1), data[i]);
  }
  QString str = QJsonDocument(sender).toJson();
  QString js = QString("init(%1)").arg(str);
  qDebug() << sender;

  for (int i = 0; i < webs.size(); i++) {
    webs[i]->page()->runJavaScript(js);
  }
}

void MainWindow::on_newButton_clicked() {
  qDebug() << tableViews.size();
  //创建一个新的Widget用于存放TableView
  QWidget *newPage = new QWidget(ui->tabWidget);
  QTableView *newTableView = new QTableView(newPage);
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(newTableView);
  newPage->setLayout(layout);

  //将新的widget放入新插的tab中
  ui->tabWidget->insertTab(tableViews.size(), newPage,
                           QString::fromLocal8Bit("表"));

  //设置新的tableView的model
  QSqlTableModel *model = new QSqlTableModel();
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  newTableView->setModel(model);

  //保存新的tableView和model的信息
  tableViews.push_back(newTableView);
  dbModels.push_back(model);
}

void MainWindow::on_addRecordButton_clicked() {
  int modelIndex = ui->tabWidget->currentIndex();
  //没有数据时就不添加了。
  if (dbModels[modelIndex]->rowCount() == 0) {
    return;
  }
  //根据当前表创建空记录
  QSqlRecord record = dbModels[modelIndex]->record();
  //获取记录数
  int rowCount = dbModels[modelIndex]->rowCount();
  //在显示时，输入完了数据后，左侧是'*'表示没保存，只有在数据保存后才显示行号
  dbModels[modelIndex]->insertRecord(rowCount, record);
}

void MainWindow::on_submitButton_clicked() {
  int modelIndex = ui->tabWidget->currentIndex();
  //开始当前表格对应数据库的事务操作
  dbModels[modelIndex]->database().transaction();
  if (dbModels[modelIndex]->submitAll()) {
    if (dbModels[modelIndex]->database().commit())  //提交
    {
      QMessageBox::information(this, tr("tableModel"),
                               QString::fromLocal8Bit("数据库修改成功！"));
    } else {
      dbModels[modelIndex]->database().rollback();  //回滚
      QMessageBox::warning(this, tr("tableModel"),
                           QString::fromLocal8Bit("数据库错误：%1")
                               .arg(dbModels[modelIndex]->lastError().text()),
                           QMessageBox::Ok);
    }
  }
}

void MainWindow::on_queryButton_clicked() {
  QString query = ui->lineEdit->text();
  if (query.isEmpty()) {
    return;
  }

  int modelIndex = ui->tabWidget->currentIndex();
  dbModels[modelIndex]->setFilter(QString("Monday = %1").arg(query));
  dbModels[modelIndex]->select();
}

void MainWindow::on_deleteRecordButton_clicked() {
  int modelIndex = ui->tabWidget->currentIndex();
  //获取当前TableView的选择模型
  QItemSelectionModel *currentModel = tableViews[modelIndex]->selectionModel();
  //获取选中的行
  QModelIndexList selectRecord = currentModel->selectedRows();

  //遍历选中行
  for (auto i = selectRecord.begin(); i != selectRecord.end(); i++) {
    //删除行
    dbModels[modelIndex]->removeRow((*i).row());
    //隐藏行
    tableViews[modelIndex]->setRowHidden((*i).row(), true);
  }
}

void MainWindow::on_undoButton_clicked() {
  int modelIndex = ui->tabWidget->currentIndex();
  dbModels[modelIndex]->revertAll();

  //这里偷懒了，这里只有200条数据所以就拿个循环将就下
  //但是如果数据一多的话，这这种方法肯定不好，可以考虑
  //为每个model保存一个因为删除而隐藏的数组，在非此撤销
  //时重现即可，那样虽然不是很优，但是比这种遍历好。
  for (int i = 0; i < dbModels[modelIndex]->rowCount(); i++) {
    if (tableViews[modelIndex]->isRowHidden(i)) {
      tableViews[modelIndex]->setRowHidden(i, false);
    }
  }
}
void MainWindow::on_comboBox_currentIndexChanged(int index) {
  ui->stackedWidget->setCurrentIndex(index);
}

/*
 * 在第一此主窗口加载时QWebEngineView肯定是没加载好的
 * 所以此时就不需要resizeEvent同时Echarts改变大小了，
 *
 * 所以第一次Echarts的改变大小就只能靠他们自己的加载
 * 完成信号来完成了。之后的修改就需要resizeEvent来负责了。
 */
void MainWindow::resizeEvent(QResizeEvent *event) {
  if (this->doEchartChange) {
    resizeEcharts();
  }
}

void MainWindow::on_actionDataView_triggered() {
  ui->mianStackWidget->setCurrentWidget(ui->page_1);
}

void MainWindow::on_actionDataBase_triggered() {
  ui->mianStackWidget->setCurrentWidget(ui->page_2);
}

/*
 * 获取表中的字段名
 */
QVector<QString> getDataFiled(const QString &tableNmae) {
  QVector<QString> v;

  QSqlQuery query;
  QString str = "PRAGMA table_info(" + tableNmae + ")";
  query.prepare(str);
  if (query.exec()) {
    while (query.next()) {
      v.push_back(
          QString(QString::fromLocal8Bit("%1")).arg(query.value(1).toString()));
    }
  }
  return v;
}
