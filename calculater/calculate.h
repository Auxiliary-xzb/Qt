#ifndef CALCULATE_H
#define CALCULATE_H


class calculate : public QWidget
{
    Q_OBJECT
public:
    explicit calculate(QWidget *parent = 0);

public slots:
    void deal_dengyu(QString);
};

#endif // CALCULATE_H
