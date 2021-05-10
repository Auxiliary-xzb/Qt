#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileInfo>
#include <QItemSelectionModel>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndexList>
#include <QNetworkProxyFactory>
#include <QResizeEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QString>
#include <QTableView>
#include <QVector>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void connectDataBase();

 protected:
  virtual void resizeEvent(QResizeEvent *event) override;

 private slots:
  void on_pushButton_clicked();

  void resizeEcharts(void);

  void on_comboBox_currentIndexChanged(int index);

  void on_actionDataView_triggered();

  void on_actionDataBase_triggered();

  void on_openButton_clicked();

  void on_newButton_clicked();

  void on_addRecordButton_clicked();

  void on_submitButton_clicked();

  void on_queryButton_clicked();

  void on_deleteRecordButton_clicked();

  void on_undoButton_clicked();

 private:
  Ui::MainWindow *ui;
  int changedEchartCount;
  bool doEchartChange;

  QSqlDatabase db;
  QVector<QUrl> urls;
  QVector<QTableView *> tableViews;
  QVector<QWebEngineView *> webs;
  QVector<QString> dbTableNames;
  QVector<QJsonArray> data;
  QVector<QSqlTableModel *> dbModels;
};
#endif  // MAINWINDOW_H
