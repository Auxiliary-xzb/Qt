#include "mywidget.h"
#include "ui_mywidget.h"
#include <QMessageBox>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);


    this->setWindowTitle(QString("构造LR0分析表"));
    this->setWindowIcon(QIcon(":/new/prefix1/icon/icon.jpg"));

    ui->tableWidget_Show->setColumnCount(10);
    ui->tableWidget_Show->setRowCount(10);
    ui->textEdit->setPlaceholderText(QString("请输入文法"));

    layout = new QGridLayout;
    layout->setHorizontalSpacing(50);
    layout->setVerticalSpacing(75);
    ui->widget->setLayout(layout);

 //   mylabel = new QList<MyLabel>();
    unsigned char count = 0;
    for(count = 0; count < 20; count++){
        mylabel[count] = NULL;
    }

    ui->pushButton_Clear->setEnabled(false);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::Init(){
        int count;
        for(count = 0 ; count < L_LENGTH ; count++){
            list[count] = NULL;
            state[count].destination = NULL;
            state[count].road = '\0';
            state[count].source = NULL;
            state[count].symbol = '\0';
            state[count].my_state_number = 0;
            Symbol_Z[count] = '\0';
            Symbol_F[count] = '\0';
//            want[count].destination_state = 0;
//            want[count].source_state = 0;
//            want[count].road = '\0';
        }
}

//获取文法
char **MyWidget::GetGrammer(){
        int count, n , j, times;
        char **I = (char **)malloc(sizeof(char *)*L_LENGTH);
        for(count = 0 ; count < L_LENGTH ; count++)
            *(I+count) = NULL;

        //将每一行的内容到QStringList中
        stringlist = ui->textEdit->toPlainText().split("\n");
        int size = stringlist.size();
        times = 0;
        count = 0;
        while( times < size){
                    QString string = stringlist.at(count);
                    char *str = string.toUtf8().data();
                    //规定了文法的非终结符是大写字母，然后是推出符号，由‘-’和‘>’组成
                    if( !(str[0] >= 'A' && str[0] <= 'Z') || str[1] != '-' || str[2] != '>' || str[3] == ' '){
                        QMessageBox::StandardButton  button = QMessageBox::warning(this, tr("warning"), tr("你输入的不是二型文法"));
                        if( button == QMessageBox::Ok){
                            ui->textEdit->clear();
                            ui->textEdit->setPlaceholderText(QString("请输入文法"));
                        }
                    }
                    //获取字符串的长度，因为fgets先放换行符，所以这里的判断条件为换行符
                    for(n = 0; str[n] != '\0' ; n++)
                        ;
                    //构造等大的空间，减2是因为，字符串长度中算入了'-'和'>'
                    I[count] = (char *)malloc(sizeof(char)*(n-2));
                    //只复制产生式左端的符号和右端的符号
                    *(*(I+count)) = str[0];
                    Symbol_F[0] = *(I[0]+0);

                    //获取所有的符号
                    for(n = 3 ; str[n] != '\0' ; n++){
                        //在开始时已经存储了产生式左端的符号，不存储'-'和'>'所以要减2
                        *(*(I+count)+n-2) = str[n];
                        j = 0;
                        //终结符则加入到Symbol数组
                        if( !(str[n] >= 'A' && str[n] <= 'Z') ){
                            //判断该符号是否在终结符数组中
                            while(Symbol_Z[j] != '\0'){
                                if(Symbol_Z[j] == str[n])
                                    break;
                                j++;
                            }
                            //不在终结符数组则将其加入到终结符数组中
                            if(Symbol_Z[j] == '\0')
                                Symbol_Z[j] = str[n];
                        }else{
                            //判断符号是否在非终结符数组中
                            while(Symbol_F[j] != '\0'){
                                if(Symbol_F[j] == str[n])
                                    break;
                                j++;
                            }
                            //不在非终结符数组中则将其加入到非终结符数组中
                            if(Symbol_F[j] == '\0')
                                Symbol_F[j] = str[n];
                        }
                    }

                    *(*(I+count)+n-2) = '\0';
                    //下标下移一个
                    count++;
                    times++;
                }

                //设置指针数组的最后一位为空，其实可以省略，因为已经初始化全空了
                I[count] = NULL;

                //将两个数组构造成一个数组，前部分为终结符，后半部分为非终结符，结果存放在Symbol_Z数组中
                count = 0;
                while(Symbol_Z[count] != '\0')
                    count++;
                Symbol_Z[count++] = '#';
                j = 0;
                while(Symbol_F[j] != '\0'){
                    Symbol_Z[count] = Symbol_F[j];
                    j++;
                    count++;
                }
                return I;
}

//产生项目集
void MyWidget::Item_List(char *str){
         //最好不要赋值，如果在后面又出现赋值初始化语句那么程序就会产生两条一样的汇编指令。
        int count_s = 0, count_t = 0, dot_position = 0,sum = 0;
        char *temp;

        for(count_s = 0 ; *(str+count_s) != '\0'; count_s++)
                ;

        //这里加1是为了在这下面的复制中将最后的'\0'也复制进去
        sum = count_s+1;

        //输入串只省略了推出符号没有省略产生式左端的非终结符，所以点的位置从字符串的下标为1的位置开始
        dot_position = 1;
        do{
            //count_s传入参数字符串的指针，count_t转换后的字符串指针
            temp = (char *)malloc(sizeof(char)*sum);                            //创建一个字符串长度大小一样的字符串指针
            for(count_s = 0, count_t = 0; count_s < sum; count_s++,count_t++){
                if(count_t != dot_position)
            //没有到指定的点的位置，则复制字符，
                    *(temp+count_t) = *(str+count_s);
                else{
            //到达指定位置后，将temp字符串的该为填充'.'，然后将传入的参数回退
                    *(temp+count_t) = '.';
                    count_s--;
                }
            }
            //最后在出来时候，count_t的值增加了一个，那么就指向了'\0'后面的字符 ，所以此时要减去
            count_t--;

            list[Position] = temp;                                              //将该字符串加入list项目表中
            Position++;                                                         //list项目表中的指针下移
            dot_position++;                                                     //点的位置后移

            //如果点到了字符串的尾部，就不再产生项目
            if(*(temp+count_t - 1) == '.' && *(temp+count_t) == '\0')
                break;
        }while(1);
}

void MyWidget::Start(){
    char st[4] = {s[0],'.', s[1], s[2]};                                        //文法开始部分
        char *start[2] = {st ,NULL};
        char **result;
        int count, number, j;

        result = Closure(start);                                                //用文法的拓展项得到初始状态I0
        State_Number = 1;                                                       //生成状态由1开始
        Result(result);

        //不断地生成新状态
        while(state[Road_Position].road != '\0'){
            //通过遍历新生成的状态，再生成新的状态
            Result(state[Road_Position].destination);
            Road_Position++;
        }

        count = 0;
        while(state[count].road != '\0'){
            j = 0;
            number = 0;                                                         //初始状态为0
            while(state[j].road != '\0'){
                /*首先需要理解的是，每个结构体中的状态编号是生成状态的状态字
                所以找到当前状态的父状态的状态字,就需要找到某一个结构体的destination是当前的source
                那么找到的结构体的状态号就是父状态的状态号
                */
                if( state[count].source == state[j].destination ){
                    //这里的number表示的是该生成该状态的父状态
              //      number = state[j].state_number;
                    number++;
                    //获取父状态后，那么此时父状态中的状态字就是该节点的状态字
                    state[count].my_state_number = state[j].state_number;
                    break;
                }
                j++;
            }
            //只有可能是状态0找不到父状态，所以只有在它的时候才是number为0
            if( number == 0 ){
                state[count].my_state_number = 0;
            }
            count++;
        }
}

//找到状态可以接受的字母，为每一个字母生成下一个状态，放入状态转换数组
void MyWidget::Result(char **I){
    int count, position,temp,place,p;
    char **result;							//保存文法的结果
    char first[30] = {'\0'};					//存储点后的字符，即状态的输入字符

    //如果需要产生项目的状态，在结构体数组的source出现则代表以前与该状态相同的状态已经完成了该工作
    if(Check(I))
        return ;

    count = 0;							//I0的项目集指针
    position = 0;
    place = 0;
    //获取点后的输入字符，存放在first数组中
    while(I[count] != NULL){
        place = FindDot(I[count]);				//找到该项目集中的点
        place++;						//找到点后的字母，这个字母就是输入
        //如果点到结尾了，则直接判断下一个,否则程序会用'\0'替代集合
        if(*(I[count]+place) == '\0'){
            count++;					//如果点在字符串尾部，则直接去查询下一个字符串
            continue;
        }
        temp = 0;
        while(first[temp] != '\0'){				//遍历输入字符集
            if(first[temp] != *(I[count]+place))
                temp++;
            else
                break;					//若此字符在first数组中，则直接跳出
        }
        if(first[temp] != '\0'){				//如果没有遍历到输入字符表尾，证明输入字符表中存在该字符，则直接进行下一次判断
            count++;
            continue;
        }
        first[position++] = *(I[count]+place);			//否则将该字符保存到输入字符表中，后位置'\0'
        first[position] = '\0';
        count++;

    }

    //当first数组不为空就会产生新的结构体。
    for(count = 0; first[count] != '\0'; count++){
        result = Goto(I, first[count]);
        position = FindDot(result[0]);
        position++;
        //如果点后是终结符，则规约，若是拓展式，则符号为a代表acc
        if(*(result[0]+position) == '\0'){
            if(*(result[0]+0) == '#')
                state[Road_Number].symbol = 'a';
            else
                state[Road_Number].symbol = 'r';
        }else//如果点后不是结束符号，就是转移到下一个状态，s表示switch
                state[Road_Number].symbol = 's';
        //目前的想法是牺牲一点速度完成
        //将产生的状态和原来的所有destination状态去比较，相同则证明，原来存在已经生成了该状态，那么直接将原来的状态指针加过来就行了
        if( Check_2(result, &p) ){
            free(result);
            state[Road_Number].destination  = state[p].destination;
            state[Road_Number].state_number = state[p].state_number;
        }else{
            state[Road_Number].destination  = result;
            state[Road_Number].state_number = State_Number;
            State_Number++;
        }
        state[Road_Number].source = I;				//保存源状态
        state[Road_Number].road = first[count];			//保存路径
        Road_Number++;
    }
}


//构造一个项目集规范族的扩展
char **MyWidget::Closure(char **I){
    int count,n;
    int position = 0;
    char **I_New;
    char ch = ' ';							//记录上次所找到的点后的非终结符，若两个终结符一样则跳过

    I_New = (char **)malloc(sizeof(char *)*L_LENGTH);
    for(count = 0 ; count < L_LENGTH ; count++)
        *(I_New+count) = NULL;
    //获取状态集中项目的个数记为n,并将其保存在一个新建的指针数组中
    for(n = 0 ; *(I+n) != NULL ; n++){
        count = 0;
        //获取字符串长度
        while( *(*(I+n)+count) != '\0' ){
            count++;
        }
        //申请相同大小的空间
        I_New[n] = (char *)malloc(sizeof(char)*count);
        //将该字符串复制到指针中
        for(count = 0 ; *(*(I+n)+count) != '\0' ; count++)
            *(*(I_New+n)+count) = *(*(I+n)+count);
        *(*(I_New+n)+count) = '\0';
    }
    for(count = 0 ; I_New[count] != NULL ; count++){
        position = FindDot(*(I_New+count));			//找到点在项目中的位置，记为position
        //判断点后的字符是否为非终结符，若为非终结符，则将形如的项目加入状态集合中
        if(*(*(I_New+count)+position+1) >= 'A' && *(*(I_New+count)+position+1) <= 'Z'){
            if(*(*(I_New+count)+position+1) !=  ch)		//保证在点后的字母相同时不会重复判断
                I_New = AddItem_First(I_New, &n, *(*(I_New+count)+position+1));	//将状态集合中的最后一个空指针传入函数以便添加新的项目
        }
        ch = *(*(I_New+count)+position+1);			//保存上次查到的点后的字符，避免产生相同非终结符产生添加多次项目的情况
    }
    return I_New;							//返回新建好的状态
}

//构造一个原始的项目集规范族，之后进行扩展操作
//通过传送来的项目和点后的字母，建立一个状态
char **MyWidget::Goto(char *I[], char ch){
    int count ,position = 0,n = 0, Null = 0;			//position点的位置，Null新建的表的指针值
    char str[100];							//保存点前的字符串，用于查找
    char **I_New = (char **)malloc(sizeof(char *)*L_LENGTH);

    count = 0;
    for(count = 0 ; count < L_LENGTH ; count++)
        *(I_New+count) = NULL;					//将表清空
    Null = 0;
    for(count = 0 ; I[count] != NULL ; count++){			//判断状态中的所有项目，如果有项目中点后的字符为ch的则将ch移进
        position = FindDot(I[count]);				//找出点的位置
        position++;
        if(*(*(I+count)+position) == ch){			//判断点后的字母是否为ch，如果是，则将ch移进，将该项目放入新的状态
            n = 0;
            while(*(*(I+count)+n) != '.'){			//先将点前的串复制，添加完点后将其做为参考串，再向状态中加入集合
                str[n] = *(*(I+count)+n);
                n++;
            }
            str[n] = ch;
            str[n+1] = '.';
            str[n+2] = '\0';
            I_New = AddItem_Str(I_New, &Null, str);		//将于str串前缀匹配的串加入到状态中
            break;						//找到一个相同的就退出
        }
    }
    I_New = Closure(I_New);						//查看这个状态中是否存在形如A->.C的项目，若存在则扩充该项目
    return I_New;
}

//新建一个状态
/*
    将形如A->ab.C的想项目都加入到该状态中
*/
char **MyWidget::AddItem_Str(char **I, int *Null, char *source){
    int count,n;
    for(count = 0 ; list[count] != NULL ; count++ ){
        if( Strcmp(*(list+count), source) ){			//如果点之前的部分相同，则将其加入状态中
            n = 0;										//获取字符串的长度
            while( *(*(list+count)+n) != '\0' ){
                n++;
            }
            I[*Null] = (char *)malloc(sizeof(char)*n);
            for(n = 0 ; *(*(list+count)+n) != '\0' ; n++)	//将字符串拷贝
                *(*(I+(*Null))+n) = *(*(list+count)+n);
            *(*(I+(*Null))+n) = '\0';
            (*Null)++;
        }
    }
    return I;
}

//向一个状态中添加点在字符串首部的项目
//要修改项目集中最后一项的内容就要将这个内容的指针传过来才能改变其内容
/*
    char **I为状态，
    *Null为状态中最后一个项目的下一个空指针位置，因为在调用函数中，n的值是要跟着循环而改变的，所以要传递指针
    ch为项目中，点后的非终结符
*/
char **MyWidget::AddItem_First(char **I, int *Null, char ch){
    int count = 0 ,n = 0;


    /*
        因为是非终结符，要将左端为该非终结符的项目集放入进来。
    */
    for(count = 0 ; list[count] != NULL ; count++ ){
        //如果首字母是ch，即产生式左端为ch，产生式右端的开始为点，则将该项目加入项目集
        if( *(*(list+count) + 0 ) == ch && *(*(list+count) + 1 ) == '.'){
            while( *(*(list+count)+n) != '\0' ){
                n++;
            }		//获得该项目的长度
            I[(*Null)] = (char *)malloc(sizeof(char) * n);	//为该项目集的最后一位分配大小为字符串长度的空间，装入字符串
            for(n = 0 ; *(*(list+count)+n) != '\0' ; n++)
                *(*(I+(*Null))+n) = *(*(list+count)+n);
            *(*(I+(*Null))+n) = '\0';
            (*Null)++;								//该项目的指针加1，指向项目尾，空指针处
        }
    }
    return I;
}

void MyWidget::on_pushButton_Submit_clicked()
{
        if(ui->textEdit->toPlainText() == NULL){
           return;
        }

        Init();

        int count;
        char **I = GetGrammer();

        //获取文法的开始符，并且保存到拓展项中
        s[1] = *(I[0]+0);

        //将拓展文法所产生的项目加入到总的项目集中
        Item_List(s);
        count = 0;
        //指针数组不为空时，用所指向的字符串创建项目集
        while(I[count] != NULL){
            Item_List(I[count]);
            count++;
        }
        Start();
        //显示所有状态
        Show_Struct();
        //创建表格显示状态
        Show_Table();
        ui->pushButton_Submit->setEnabled(false);
        ui->pushButton_Clear->setEnabled(true);
}

//检查，如果该域在原来的结构体数组中的某一个的source中出现过返回1，否则返回0
int MyWidget::Check(char **I){
    int count = 0, i = 0, j = 0;
    //遍历所有的结构体数组
    while(state[count].road != '\0'){
        //遍历每一个source，将I于source想比较，如果存在不相等的一个字符串，就去遍历下一个source
        j = 0;
        while(state[count].source[j] != NULL){
            //存在一个不相等的串就去遍历下一个串
            for(i = 0; *(state[count].source[j]+i) != '\0' ; i++ ){
                if( *(state[count].source[j]+i) != *(I[j]+i) )
                    break;
            }
            //如果是因为不相等退出，则可以直接遍历下一个结构体的source
            if(*(state[count].source[j]+i) != '\0')
                break;
            j++;
        }
        //因为当存在一个字符串不相同时就会退出比较下一个字符串，直接跳去比较下一个source，此时的j值就是不相等串的位置
        //那么所有的字符串都相同的话，指针数组的指针就会指向尾部，所以可以通过判断指针数组的下一个元素是否为空来看两个是否相同
        if(state[count].source[j] == NULL)
            return 1;
        count++;
    }
    //如果遍历完了还没有直接返回，则表示没有一个状态和该状态相同
    return 0;
}

//由于所有的状态都是由上一个状态产生的，所以每次都去查询destination域即可
int MyWidget::Check_2(char **I, int *position){
    int count = 0 , i = 0, j;
    while(state[count].road != '\0'){		//状态转换数组没有到达数组尾部
        //遍历每一个destination，将I于destination想比较，如果存在不相等的一个字符串，就去遍历下一个destination
        j = 0;
        while(state[count].destination[j] != NULL){
            for(i = 0; *(state[count].destination[j]+i) != '\0' ; i++ ){
                //如果两者不相同那么,就去判断下一个结构体
                if( *(state[count].destination[j]+i) != *(I[j]+i) )
                    break;
            }
            //如果是因为不相等退出，则可以直接遍历下一个结构体的destination
            if(*(state[count].destination[j]+i) != '\0')
                break;
            j++;
        }
        //因为存在不相等串退出时，j的位置肯定是指向出错字符串的位置，
        //那么如果，整个串都遍历完还没错，那么j肯定就停在了为空的字符串
        //那么就表明，存在一个destination和该destination相同
        if(state[count].destination[j] == NULL){
            *position = count;
            return 1;
        }
        count++;
    }
    //当遍历完所有的都没有返回时，证明，该状态不存在一个相同的状态
    return 0;
}


//找到字符串中找点，返回点在字符串中的位置值
int MyWidget::FindDot(char *str){
    int count = 1;
    do{
        if(*(str+count) == '.')
            break;
        count++;
    }while(1);
    return count;
}

//比较两个串
int MyWidget::Strcmp(char *source, char *destination){
    int count = 0;
    //只要在参考串结束之前出错则证明前缀不匹配，否则匹配
    while(destination[count] != '\0'){
        if(destination[count] == source[count])
            count++;
        else
            return 0;
    }

    return 1;
}

//改变输出的信息的格式
QString* MyWidget::ChangeFormat(char **result){
     QString *list = new QString();
     unsigned char count = 0, i, j;
     char buf[20] = {0};
     while( result[count] != NULL ){
        buf[0] = *(result[count] + 0);
        buf[1] = '-';
        buf[2] = '>';
        for(i = 1, j = 0; *(result[count]+i) != '\0'; i++, j++){
            buf[3+j] = *(result[count]+i);
        }
        buf[3+j+1] = '\0';
        list->append(buf);
        list->append("\n");

        //遍历下一个
        count++;
     }

     return list;
}

//创建QLabel来显示信息
void MyWidget::CreateLabels(QString string){
    QLabel *label = new QLabel;
    label->setText(string);

    layout->addWidget(label);
}

int MyWidget::On(int *array, int value){
    unsigned char count = 0;
    while(array[count] != 0){
        if(array[count] == value)
               break;
        count++;
    }

    if(array[count] == 0)
        return 0;
    else
        return 1;
}

void MyWidget::Show_Struct(){
    /*
        创建一个QLabel数组，来表示所有的状态，状态自身的状态号就是该状态在QLabel中的索引值。
    */

    unsigned char count = 0;
    QString *string, output;
    QLabel *label;
    while(state[count].road != '\0'){
        //先遍历自身的状态号，根据该状态号创建QLabel对象并放入数组中
        if( mylabel[state[count].my_state_number] == NULL ){
            string = ChangeFormat(state[count].source);
            output = QString("状态%1:\n%2").arg(state[count].my_state_number).arg(*string);
            label = new QLabel(output);
            label->setParent(ui->widget);
            mylabel[state[count].my_state_number] = label;
        }
        //遍历所有的目的状态号，根据该状态号创建QLabel对象并放入数组中
        if( mylabel[state[count].state_number] == NULL ){
            string = ChangeFormat(state[count].destination);
            output = QString("状态%1:\n%2").arg(state[count].state_number).arg(*string);
            label = new QLabel(output);
            label->setParent(ui->widget);
            mylabel[state[count].state_number] = label;
        }
        count++;
    }


    count = 0;
    while(mylabel[count] != NULL){
        count++;
    }
#if 1
    //将QLabel显示到QGridLayout中
    int r_c, c_c, number = 0;
    int column_count = count/2;
    int row_count = count/column_count;

    //判断以下是否为整数
    if( count%3 != 0 )
        row_count++;

    for(r_c = 0; r_c < row_count; r_c++){
        for(c_c = 0; c_c < column_count; c_c++){
            if(number < count){
                //设置文字居中显示
                mylabel[number]->setAlignment(Qt::AlignCenter);
                //设置Label的边框
                mylabel[number]->setStyleSheet("border:2px solid;"
                                               "border-color: rgb(193, 193, 193)");
                layout->addWidget(mylabel[number], r_c, c_c);
                number++;
            }
        }
    }
#endif

#if 0
    //可以创建成一个树状结构，横着的树。
    //根据路径将连个状态连接。
#endif

}

void MyWidget::on_pushButton_Next_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void MyWidget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

//QTabelWidget要说明行列数,否则不显示
void MyWidget::Show_Table(){
    //设置表格行标题
    QStringList headLabels,rowLabels;
    headLabels << "Action";
    rowLabels << " ";
    //获取状态最大值
    int count = 0, number = 0, column = 0;
    char buf[20];
    while(mylabel[count] != NULL){
        rowLabels << QString::number(count, 10);
        count++;
    }
    ui->tableWidget_Show->setRowCount(count + 1);
    ui->tableWidget_Show->setVerticalHeaderLabels(rowLabels);

    //获取终结符的个数
    while(Symbol_Z[number] != '\0'){
        if(Symbol_Z[number] == '#'){
            headLabels << "GOTO";
            number++;
            continue;
        }

        headLabels << " ";
        number++;
    }
    ui->tableWidget_Show->setColumnCount(number);
    ui->tableWidget_Show->setHorizontalHeaderLabels(headLabels);

    /*
        QTableWidget: cannot insert an item that is already owned by another QTableWidget
        不能一直使用一个QTableWidget
    */
    QTableWidgetItem *item[number], *result;
    number = 0;
    while(Symbol_Z[number] != '\0'){
        item[number] = new QTableWidgetItem(QString(QChar(Symbol_Z[number])));
        ui->tableWidget_Show->setItem(0,column,item[number]);
        number++;
        column++;
    }


    //遍历state数组，根据自身状态号和目的状态号来填写表格。
    count = 0;
    while(state[count].road != '\0'){
        buf[20] = {0};
        //先填写GOTO表，再填写ACTION表
        if( state[count].road >= 'A' && state[count].road <= 'Z' ){
            //填写GOTO表
            column = 0;
            while( item[column]->text() != QString(QChar(state[count].road)) )
                column++;
            result = new QTableWidgetItem(QString::number(state[count].state_number));
            result->setTextAlignment(Qt::AlignRight);
            ui->tableWidget_Show->setItem(state[count].my_state_number + 1, column, result);
        }

        //再填写ACTION
        //动作只有三种 'a' 's' 'r'.
        /*
         *  这里的为什么加小写条件，是因为GOTO表已经写了
         *
         *  对于LR（0）存在这样的现象，你在规约的同时也是属于移进同时也是属于规约的,
         * 所以此时s和r都要写
        */
        if(state[count].symbol == 'r'){
            if(state[count].road <= 'z' && state[count].road >= 'a'){
                column = 0;
                while( item[column]->text() != QString(QChar(state[count].road)) )
                    column++;
                result = new QTableWidgetItem( QString("s%1").arg(state[count].state_number) );
                result->setTextAlignment(Qt::AlignRight);
                ui->tableWidget_Show->setItem(state[count].my_state_number + 1, column, result);
            }

            column = 0;
            //获取终结符的所有列
            while( !(item[column]->text() >= QString(QChar('A')) && item[column]->text() <= QString(QChar('Z'))) ){
                column++;
            }
            //创建与列数相同的QTableWidgetItem
            QTableWidgetItem *tableitem[column];
            //去掉最后的点，得到新的串
            buf[0] = (state[count].destination)[0][0];
            buf[1] = '-';
            buf[2] = '>';
            for(number = 3; (state[count].destination)[0][number - 2] != '.'; number++){
                    buf[number] = (state[count].destination)[0][number - 2];
            }
            buf[number++] = '\0';
            //找寻符合的产生式,肯定是找的到的,然后将目的状态号的那一行填写r
            for(number = 0; number < stringlist.size(); number++){
                if(stringlist.at(number) == QString(buf)){
                    break;
                }
            }
            //根据r和产生式编号来组合成新的QString
            QString test = QString("r%1").arg(number+1);
            for(number = 0; number < column; number++){
                tableitem[number] = new QTableWidgetItem(test);
                ui->tableWidget_Show->setItem(state[count].state_number + 1, number, tableitem[number]);
                tableitem[number]->setTextAlignment(Qt::AlignRight);
            }
        }

        //因为对于是s的项目，它的后一个字符肯定是终结符
        if(state[count].symbol == 's'){
            column = 0;
            while( item[column]->text() != QString(QChar(state[count].road)) )
                column++;
            result = new QTableWidgetItem( QString("s%1").arg(state[count].state_number) );
            result->setTextAlignment(Qt::AlignRight);
            ui->tableWidget_Show->setItem(state[count].my_state_number + 1, column, result);
        }
        if(state[count].symbol == 'a'){
            //如果将要做的动作是ACC，则显示acc
            column = 0;
            while( item[column]->text() != QString(QChar('#')) )
                column++;
            result = new QTableWidgetItem(QString("acc"));
            result->setTextAlignment(Qt::AlignRight);
            ui->tableWidget_Show->setItem(state[count].state_number + 1, column, result);
        }
        count++;
    }

#if 0
        //如果是小写字母则获取路径和目的号，将两则组合
        if(state[count].road >= 'a' && state[count].road <= 'z'){
            column = 0;
            while( item[column]->text() != QString(QChar(state[count].road)) )
                column++;
            result = new QTableWidgetItem( QString("%1%2").arg(QString(QChar(state[count].symbol))).arg(state[count].state_number) );
            result->setTextAlignment(Qt::AlignRight);
            ui->tableWidget_Show->setItem(state[count].my_state_number + 1, column, result);
        }

        if(state[count].symbol == 'a'){
            column = 0;
            while( item[column]->text() != QString(QChar('#')) )
                column++;
            result = new QTableWidgetItem(QString("acc"));
            result->setTextAlignment(Qt::AlignRight);
            ui->tableWidget_Show->setItem(state[count].my_state_number + 1, column, result);
        }
#endif

}

void MyWidget::on_pushButton_Clear_clicked()
{
    unsigned char i = 0;
    ui->textEdit->clear();
    ui->tableWidget_Show->clear();
    ui->pushButton_Submit->setEnabled(true);

    ui->tableWidget_Show->setColumnCount(10);
    ui->tableWidget_Show->setRowCount(10);

    //将数据都初始化
    stringlist.clear();
    //该Position是list中的索引，每次从新开始就要从0开始添加
    Position = 0;
    //全局的都要初始化
    Road_Number = 0;
    Road_Position = 0;
    QList<QLabel *> la = ui->widget->findChildren<QLabel *>();
    foreach(QLabel *test , la){
        delete test;
    }
    //将mylabel清空，因为判断条件就是空
    for(i = 0; i < 20; i++){
        mylabel[i] = NULL;
    }


}
