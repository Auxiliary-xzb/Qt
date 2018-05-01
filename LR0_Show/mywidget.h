#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QString>

#define L_LENGTH 	 50				//项目集合大小
#define MAX		 20				//状态集大小

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private:
    Ui::MyWidget *ui;
    typedef struct{
        char **source;                                      //源状态
        char road;                                          //路径
        int state_number;                                   //生成的状态号
        int my_state_number;                                //自身的状态号
        char symbol;                                        //生成的状态可以做到动作
        char **destination;                                 //目的状态
    }State_Transition;
/*
    typedef struct{
        char **source;
        int source_state;                                   //源状态编号
        char symbol;                                        //下一个状态做的动作
        char road;                                          //路径
        int destination_state;                              //目标状态标号
        char **destination;
    }Want;
*/

/*
    typedef struct{
        QLabel *label;
        unsigned char number;
    }MyLabel;
*/
    QStringList stringlist;                                 //存储输入的文法
    char *list[L_LENGTH] ;                                  //项目集合
    int Position = 0;                                       //项目集指针
    char s[3] = {'#' , ' ', '\0'};                          //存储文法的拓展项
    State_Transition state[L_LENGTH];                       //存放转换过程
    int Road_Number = 0;                                    //转换过程数组指针
    int Road_Position = 0;                                  //遍历存放转换数组的指针
    int State_Number = 0;                                   //状态号
    char Symbol_Z[20];                                      //存放可能的所有输入终结符号
    char Symbol_F[10];                                      //存放可能的所有输入非终结符
//    Want want[L_LENGTH];                                    //存放状态编号和路径的关系
    QLabel *mylabel[20];

public:
    void Init();                                            //初始化项目集
    void Item_List(char*);                                  //传入产生式，该产生式的项目集
    char **GetGrammer();                                    //从文件中获取文法
    void Start();                                           //开始逻辑处理
    void Result(char **I);                                  //找到状态可以接受的字母，为每一个字母生成下一个状态，放入状态转换数组
    char **Closure(char **I);                               //构造一个项目集规范族的扩展
    char **Goto(char *I[], char ch);                        //通过传送来的项目和点后的字母，建立一个状态
    char **AddItem_Str(char **I, int *Null, char *source);	//新建一个状态
    char **AddItem_First(char **I, int *Null, char ch);     //向一个状态中添加点在字符串首部的项目
    int Check(char **I);                                    //检查，如果该域在原来的结构体数组中的某一个的source中出现过返回1，否则返回0
    int Check_2(char **I, int *position);                   //由于所有的状态都是由上一个状态产生的，所以每次都去查询destination域即可
    int  FindDot(char *str);                                //找到字符串中找点，返回点在字符串中的位置值
    int  Strcmp(char *source, char *destination);           //比较两个串
    void Show_Struct();                                     //格式化显示
    QString *ChangeFormat(char **);                         //改变输出的格式
    void CreateLabels(QString);
    int On(int *, int);
    void Show_Table();

private:
    QGridLayout *layout;

private slots:
        void on_pushButton_Submit_clicked();                //槽函数
        void on_pushButton_Next_clicked();
        void on_pushButton_clicked();
        void on_pushButton_Clear_clicked();
};

#endif // MYWIDGET_H
