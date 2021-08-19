#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFont>
#include <QLineEdit>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtGlobal>
#include <QFile>
#include <QMessageBox>


class timeLabel:public QLabel{
    Q_OBJECT

    public:
        timeLabel(QWidget* parent = nullptr);
        ~timeLabel()=default;

        void update();
    signals:
        void doRecord(QString time);
    public slots:
        void start();
        void pause();
        void reset();
        void record();
        void test(QString test);

    private:
        void setupUI();

        bool IsRun;
        QWidget* parent;
        QTime* Time;
        QTimer* Timer;
        QLabel* LabelTime;
        QPushButton* ButtonStart;
        QPushButton* ButtonPause;
        QPushButton* ButtonReset;
        QPushButton* ButtonRecord;
};


class inputLabel:public QLabel{
    Q_OBJECT

    public:
        inputLabel(QWidget* parent);
    signals:
        void doSendContent(QPair<QString,QString> content);

    public slots:
        void getTime(QString time);
        void test(QPair<QString,QString> content);


    private:
        void setupUI();
        QPair<QString,QString> wrapContent();

        QWidget* parent;
        QLabel* LabelTime;
        QLineEdit* LineInput;
        QPushButton* ButtonCommit;


};

class formLabel:public QLabel{
    Q_OBJECT
    public:
        formLabel(QWidget* parent);
        void setupUI();
        void generateTXT();
    public slots:
        void deleteLine();
        void clear();
        void getContent(QPair<QString,QString> content);
    private:
        QWidget* parent;
        QTableWidget* TableContent;
        QPushButton* ButtonDelete;
        QPushButton* ButtonClear;
        QPushButton* ButtonSave;

};

#endif // TIMELABEL_H
