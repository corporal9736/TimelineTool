#include "mainWindow.h"


mainWindow::mainWindow():QWidget(){
    this->setWindowTitle(tr("timeline tool"));
    this->resize(400,600);
    //this->setStyleSheet("border:2px solid red;");

    this->MainLayout = new QVBoxLayout(this);
    this->setupMenuBar();
    //this->MenuBar->setStyleSheet("border:2px solid blue;");
    MainLayout->setMenuBar(this->MenuBar);

    this->LabelTime  = new timeLabel(this);
    this->LabelInput = new inputLabel(this);
    this->LabelForm  = new formLabel(this);
    MainLayout->addWidget(LabelTime,2);
    MainLayout->addWidget(LabelInput,1);
    MainLayout->addWidget(LabelForm,5);

    connect(this->LabelTime,  &timeLabel::doRecord,       this->LabelInput, &inputLabel::getTime  );
    connect(this->LabelInput, &inputLabel::doSendContent, this->LabelForm,  &formLabel::getContent);

}

mainWindow::~mainWindow(){

}

void mainWindow::setupMenuBar(){
    this->MenuBar = new QMenuBar(this);
    QAction* actionKeymap = new QAction(tr("Keymap"),MenuBar);
    QAction* actionAbout = new QAction(tr("About"),MenuBar);
    this->MenuBar->addAction(actionKeymap);
    this->MenuBar->addAction(actionAbout);

    connect(actionKeymap, &QAction::triggered, this, mainWindow::showKeymap);
    connect(actionAbout,  &QAction::triggered, this, mainWindow::showAbout );
}

void mainWindow::showKeymap(){
    QLabel* labelKeymap = new QLabel(nullptr);
    labelKeymap->resize(300,400);
    labelKeymap->setFont(QFont("Microsoft YaHei",15));
    labelKeymap->setText(
                "Keymap\n\n"
                "Ctrl+r:  Start\n"
                "Ctrl+s:   Stop\n"
                "Ctrl+q:  Reset\n"
                "Ctrl+d: Record\n"
                "Enter:  commit");
    labelKeymap->setAlignment(Qt::AlignCenter);
    labelKeymap->show();
}

void mainWindow::showAbout(){
    QLabel* labelAbout = new QLabel(nullptr);
    labelAbout->resize(600,450);
    labelAbout->setFont(QFont("Microsoft YaHei",15));
    labelAbout->setText("About\n"
                        "This is a software designed for recording\n"
                        "the timeline of a video.\n"
                        "You press the button \"Start\" at the same\n"
                        "time when the video start.\n"
                        "And button \"Record\" to record current time.\n"
                        "Then you type something about\n"
                        "that point and then press \"commit\"\n"
                        "to push the content into the form below.\n"
                        "Finally you can press the button \"save\"\n"
                        "to save the contentinto a txt file\n"
                        "at the same dir of this software\n\n"
                        "By Corporal9736\n"
                        "LuLu Record Group");
    labelAbout->setAlignment(Qt::AlignCenter);
    labelAbout->show();
}
