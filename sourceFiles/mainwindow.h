#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QFile;
class QTextStream;
class QGraphicsScene;
class QGraphicsView;
class QGraphicsPixmapItem;
class QDir;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setText();

private:
    Ui::MainWindow *ui;
    QString question;
    QString answer;
    QFile *file;
    QTextStream *in;
    int loopCounter;
    int progressLoop;
    int row;
    int running_row;
    int skipCount;
    bool isKeyShown;
    bool isSelected;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item;


public:

    int timePerQuestion;
    QStringList groupList;
    QString fileName;
    QString mediaFolder;
    QDir *mediaDir;

public slots:
    void onKeyClicked();
    void onNextClicked();
    void on_skipButton_clicked();
private slots:
    void on_initButton_clicked();
    void on_startButton_clicked();
};
#endif // MAINWINDOW_H
