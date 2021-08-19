#include "Label.h"

void timeLabel::setupUI() {
  /*
      布局摘要：整个label由两个嵌套的布局构成，小的layout中包含了四个按钮，也就是buttonLayout
      然后大的layout中包含了显示时间的label和小layout，也就是labelLayout
  */
  QHBoxLayout *labelLayout = new QHBoxLayout(this);
  this->LabelTime = new QLabel(this);

  QVBoxLayout *buttonLayout = new QVBoxLayout(this);
  this->ButtonStart = new QPushButton(this);
  this->ButtonPause = new QPushButton(this);
  this->ButtonReset = new QPushButton(this);
  this->ButtonRecord = new QPushButton(this);

  labelLayout->addWidget(LabelTime, 3);
  labelLayout->addLayout(buttonLayout, 1);
  buttonLayout->addWidget(ButtonStart);
  buttonLayout->addWidget(ButtonPause);
  buttonLayout->addWidget(ButtonReset);
  buttonLayout->addWidget(ButtonRecord);

  this->ButtonStart->setText(tr("Start"));
  this->ButtonPause->setText(tr("Pause"));
  this->ButtonReset->setText(tr("Reset"));
  this->ButtonRecord->setText(tr("Record"));


  this->LabelTime->setAlignment(Qt::AlignCenter);
}

timeLabel::timeLabel(QWidget* parent):QLabel(parent){
    this->parent = parent;
    this->Timer = new QTimer(this);
    this->Timer->setTimerType(Qt::CoarseTimer);
    this->Time = new QTime(0,0,0,0);
    this->IsRun = false;
    this->setupUI();

    QFont font ( "Microsoft YaHei", 40, 75);
    this->LabelTime->setFont(font);
    this->LabelTime->setText(Time->toString("hh:mm:ss"));

    this->ButtonStart->setShortcut(Qt::CTRL | Qt::Key_R);
    this->ButtonPause->setShortcut(Qt::CTRL | Qt::Key_S);
    this->ButtonReset->setShortcut(Qt::CTRL | Qt::Key_Q);
    this->ButtonRecord->setShortcut(Qt::CTRL| Qt::Key_D);

    connect(this->ButtonStart,  &QPushButton::pressed, this, &timeLabel::start );
    connect(this->ButtonPause,  &QPushButton::pressed, this, &timeLabel::pause );
    connect(this->ButtonReset,  &QPushButton::pressed, this, &timeLabel::reset );
    connect(this->ButtonRecord, &QPushButton::pressed, this, &timeLabel::record);
    connect(this->Timer,&QTimer::timeout,this,&timeLabel::update);

}

void timeLabel::start(){
    if(this->IsRun == true)
        return;
    this->IsRun = true;
    this->Timer->start(1000);
}

void timeLabel::pause(){
    if(this->IsRun == false)
        return;
    this->IsRun = false;
    *(this->Time) = this->Time->addMSecs(1000 - this->Timer->remainingTime());
    this->Timer->stop();
    this->LabelTime->setText(Time->toString("hh:mm:ss"));
}

void timeLabel::reset(){
    this->IsRun = false;
    this->Timer->stop();
    this->Time->setHMS(0, 0, 0);
    this->LabelTime->setText(Time->toString("hh:mm:ss"));
    emit this->doRecord(this->LabelTime->text());
}

void timeLabel::update(){
    *(this->Time) =this->Time->addSecs(1);
    this->LabelTime->setText(Time->toString("hh:mm:ss"));
}

void timeLabel::record(){
    emit this->doRecord(this->LabelTime->text());
}

void timeLabel::test(QString test){
    qDebug()<<test;
}

void inputLabel::setupUI(){
    QHBoxLayout* labelLayout = new QHBoxLayout(this);
    this->LabelTime = new QLabel(this);
    this->LineInput = new QLineEdit(this);
    this->ButtonCommit = new QPushButton(this);

    labelLayout->addWidget(LabelTime,1);
    labelLayout->addWidget(LineInput,5);
    labelLayout->addWidget(ButtonCommit,1);

    this->LabelTime->setText("00:00:00");
    this->LineInput->setPlaceholderText(tr("please input content here"));
    this->ButtonCommit->setText(tr("commit"));

    this->LineInput->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    this->ButtonCommit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);

    //this->setStyleSheet("border:2px solid green;");
}

inputLabel::inputLabel(QWidget* parent):QLabel(parent){
    this->parent = parent;
    this->setupUI();
    this->ButtonCommit->setShortcut(Qt::Key_Enter);
    this->ButtonCommit->setShortcut(Qt::Key_Return);
    connect(this->ButtonCommit, &QPushButton::clicked,
            this, [this](){emit this->doSendContent(this->wrapContent());});
    //connect(this,&inputLabel::doSendContent,this,&inputLabel::test);
}

void inputLabel::getTime(QString time){
    this->LabelTime->setText(time);
}

void inputLabel::test(QPair<QString, QString> content){
    qDebug()<<content.first;
    qDebug()<<content.second;
}

QPair<QString,QString> inputLabel::wrapContent(){
    // get the time and text in LineInput and then clear it
    QString time = this->LabelTime->text();
    QString content = this->LineInput->text();
    this->LineInput->clear();
    return QPair<QString,QString>(time,content);
}


void formLabel::setupUI(){
    QVBoxLayout* labelLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    this->TableContent = new QTableWidget(this);
    this->ButtonDelete = new QPushButton(this);
    this->ButtonClear = new QPushButton(this);
    this->ButtonSave = new QPushButton(this);

    labelLayout->addWidget(TableContent);
    labelLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(ButtonDelete);
    buttonLayout->addWidget(ButtonClear);
    buttonLayout->addWidget(ButtonSave);

    this->ButtonSave->setText(tr("save"));
    this->ButtonClear->setText(tr("clear"));
    this->ButtonDelete->setText(tr("delete"));


    this->TableContent->setColumnCount(2);
    this->TableContent->setShowGrid(true);
    this->TableContent->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    this->TableContent->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    this->TableContent->setHorizontalHeaderLabels({tr("time"),tr("content")});
}

formLabel::formLabel(QWidget* parent):QLabel(parent){
    this->parent = parent;
    this->setupUI();
    this->TableContent->setSelectionBehavior(QAbstractItemView::SelectRows);
    //据说可以自动换行，但是似乎并没有成功
    connect(TableContent,&QTableWidget::itemChanged,
            TableContent,&QTableWidget::resizeRowsToContents);
    connect(ButtonDelete,&QPushButton::clicked,
            this,&formLabel::deleteLine);
    connect(ButtonClear,&QPushButton::clicked,
            this,&formLabel::clear);
    connect(ButtonSave,&QPushButton::clicked,
            this,&formLabel::generateTXT);

}

void formLabel::deleteLine(){
    int RowIndex = this->TableContent->currentRow();
    this->TableContent->removeRow(RowIndex);
}

void formLabel::clear(){
    this->TableContent->setRowCount(0);
}

void formLabel::generateTXT(){
    int RowCount = this->TableContent->rowCount();
    QString fileName = QString("%1_record.txt").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd..hh_mm_ss"));
    QFile file(fileName);
    if (!file.open(QIODevice::Append)) {
        QMessageBox::critical(nullptr, tr("tips"), tr("unable to create new file"));
        return;
    }
    QTextStream text(&file);
    for(int i=0;i<RowCount;i++){
        text<<this->TableContent->item(i,0)->text()<<" "<<this->TableContent->item(i,1)->text()<<"\n";
        text.flush();
    }
    file.close();
    QMessageBox::information(nullptr, tr("tips"), tr("successfully saved"));
}

void formLabel::getContent(QPair<QString, QString> content){
    int RowIndex = TableContent->rowCount();
    TableContent->insertRow(RowIndex);
    TableContent->setItem(RowIndex,0,new QTableWidgetItem(content.first));
    TableContent->setItem(RowIndex,1,new QTableWidgetItem(content.second));

    TableContent->scrollToBottom();
}
