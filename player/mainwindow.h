#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringList video_list;
    QStringList audio_list;
    QStringList text_list;
    QString videoname = "";
    QString textname="";
    int tempplay = 0;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void timerEvent(QTimerEvent *event);
    void openFile(QString name);
    void addText(QFile myfile);
    void openText(QString name);
    void add_playlist();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void settime();
    void confirm();
    void open();
    void play();
    void sliderPress();
    void sliderRelease();
    void addrow();
    void delrow();
    void save();
    void start_from();
    void open_video();
    void output();
private:
    QStandardItemModel *model = new QStandardItemModel();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
