#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtDebug>
#include<QFile>
#include<QTextStream>
#include<QStringList>
#include<Qthread>
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<string.h>
#include<QDir>
#include<QFileInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    mediaDir= new QDir("C:/Users");
    scene= new QGraphicsScene();
    view= new QGraphicsView(scene);
    item= new QGraphicsPixmapItem();
    ui->quesLabel->setText("No question provided");
    connect(ui->keyButton,SIGNAL(clicked()),this,SLOT(onKeyClicked()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(onNextClicked()));
    this->ui->keyButton->setEnabled(false);
    this->ui->nextButton->setEnabled(false);
    this->ui->startButton->setEnabled(false);
    this->ui->skipButton->setEnabled(false);

    ui->groupTable->setColumnCount(2);
    ui->groupTable->setRowCount(1);
    ui->groupTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->groupTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(){

    QString line=this->in->readLine();
    QStringList quesans=line.split(',');
    this->question= quesans[0];
    this->answer=quesans[1];
    if(quesans.length()==3){

        for (const QFileInfo &file : this->mediaDir->entryInfoList(QDir::Files))
        {

            if(quesans[2] == file.fileName().split(".")[0]){
                this->view->show();
                QString fileName= file.absoluteFilePath();
                this->item->setPixmap(QPixmap(fileName));
                this->scene->addItem(this->item);
                this->ui->verticalLayout_3->insertWidget(0,this->view);
            }
        }



//        qDebug() << fileName;
//

    }

    this->ui->quesLabel->setText(this->question);
    this->ui->keyButton->setText("key");


}
void MainWindow::onKeyClicked(){
    this->running_row+=1;
    this->isKeyShown=true;
    this->loopCounter=this->progressLoop;

    this->ui->progressBar->setValue(this->loopCounter);
    this->ui->keyButton->setText(this->answer);
    if(isSelected){
        QTableWidgetItem *item=this->ui->groupTable->item(this->running_row-1,1);
        int updated_count= item->text().toInt() + 10;
        this->ui->groupTable->item(this->running_row-1,1)->setText(QString::number(updated_count));


    }

}

void MainWindow::onNextClicked(){
    if(this->isKeyShown){
        if(this->scene->items().length() >0){
            this->view->hide();
            this->scene->removeItem(this->item);
            this->ui->verticalLayout_3->removeWidget(this->view);

        }

    if(!this->in->atEnd()){
        this->row+=1;
        if(this->row >= this->groupList.length()){
            this->row=this->row-this->groupList.length();

        }
        this->isKeyShown=false;
        this->skipCount=0;
        this->setText();
        this->on_skipButton_clicked();

    }
    else{
    this->loopCounter=this->progressLoop;
    this->ui->progressBar->setValue(this->loopCounter);
    this->ui->quesLabel->setText("Quiz Finished");
    this->ui->keyButton->setText("END");
    if(this->file->isOpen()){
        this->file->close();
    }
    }
    }
}

void MainWindow::on_skipButton_clicked()
{
    if(!this->isKeyShown){
    if(this->skipCount < this->groupList.length()){
    this->running_row=this->row+this->skipCount;
    if(this->running_row >= this->groupList.length()){
        this->running_row=this->running_row-this->groupList.length();
    }
    this->ui->groupTable->selectRow(this->running_row);
    qDebug() << "current row: " << this->row;
    qDebug() << "running_row: " << this->running_row;
    this->isSelected=true;
    this->skipCount+=1;
    this->loopCounter=0;
    while(this->loopCounter<=this->progressLoop){
        QThread::msleep(40);
        this->loopCounter+=1;
        this->ui->progressBar->setValue(this->loopCounter);
        qApp->processEvents(QEventLoop::AllEvents);
    }

   }
    else{
//    this->skipCount=-1;
    this->ui->groupTable->clearSelection();
    this->isSelected=false;
    this->loopCounter=this->progressLoop;
    this->ui->progressBar->setValue(this->loopCounter);
    }
    }
}


void MainWindow::on_initButton_clicked()
{
    int rowCount;
    QStringList groupNamesList=this->groupList;
    for(int i=0;i<groupNamesList.length();i++){
    if(this->ui->groupTable->item(0,0) == nullptr) {
        qDebug() << "Inside inital loop";
        ui->groupTable->setItem(0,0,new QTableWidgetItem(groupNamesList[i]));
        ui->groupTable->setItem(0,1,new QTableWidgetItem("0"));
    }
    else{
        rowCount=this->ui->groupTable->rowCount();
        qDebug() << "Inside major loop";
        ui->groupTable->insertRow(rowCount);
        ui->groupTable->setItem(rowCount,0,new QTableWidgetItem(groupNamesList[i]));
        ui->groupTable->setItem(rowCount,1,new QTableWidgetItem("0"));
    }
    }

    this->file=new QFile(this->fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug()<< "no file";
    }
    this->in = new QTextStream(file);
    this->ui->startButton->setEnabled(true);

    this->progressLoop=this->timePerQuestion*25;
    this->ui->progressBar->setMaximum(this->progressLoop);
    this->skipCount=0;
    this->isKeyShown=false;

    this->ui->initButton->close();




}


void MainWindow::on_startButton_clicked()
{
    this->row=0;
    this->setText();
    this->ui->skipButton->setEnabled(true);
    this->ui->nextButton->setEnabled(true);
    this->ui->keyButton->setEnabled(true);
    this->ui->startButton->close();
    this->on_skipButton_clicked();

}

