#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include<QFileDialog>
#include<QDir>
#include<QTableWidgetItem>
#include<QDir>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_done_button_clicked()
{
    this->main_screen= new MainWindow();
    this->main_screen->timePerQuestion=this->ui->timeEdit->text().toInt();
    this->main_screen->groupList=this->ui->groupEdit->toPlainText().split(',');
    this->main_screen->fileName=this->fileName;
    this->main_screen->mediaDir->setPath(this->folderName);

    this->main_screen->show();

    this->close();
}


void Dialog::on_fileButton_clicked()
{
    this->fileName = QFileDialog::getOpenFileName(this,"Open question file",QDir::homePath());
    this->ui->fileButton->setText(this->fileName.mid(this->fileName.lastIndexOf("/")+1));
}


void Dialog::on_folderButton_clicked()
{
    this->folderName=QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                             | QFileDialog::DontResolveSymlinks);
    this->ui->folderButton->setText(this->folderName.mid(this->folderName.lastIndexOf("/")+1));
}

