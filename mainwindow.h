#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Label.h"
#include <QVBoxLayout>
#include <QMenuBar>
class mainWindow:public QWidget{
    Q_OBJECT
    public:
        mainWindow();
        ~mainWindow();
        void setupMenuBar();
        void showKeymap();
        void showAbout();

    private:
        QVBoxLayout* MainLayout;
        QMenuBar* MenuBar;
        timeLabel* LabelTime;
        inputLabel* LabelInput;
        formLabel* LabelForm;


};

#endif // MAINWINDOW_H
