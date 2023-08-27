#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
class MainWindow;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_done_button_clicked();

    void on_fileButton_clicked();

    void on_folderButton_clicked();

private:
    Ui::Dialog *ui;
    MainWindow *main_screen;
    QString fileName;
    QString folderName;
};

#endif // DIALOG_H
