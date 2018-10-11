/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "videowidget.h"
#include "widget.h"
#include "xslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    VideoWidget *openGLWidget;
    QPushButton *OpenButton;
    QPushButton *PlayButton;
    QLabel *totaltime;
    QLabel *playtime;
    QLabel *label;
    XSlider *playslider;
    QTableView *showText;
    QPushButton *add_row;
    QPushButton *del_row;
    QPushButton *save;
    QPushButton *confirm;
    QComboBox *speedbox;
    Widget *wave;
    QPushButton *changetime;
    QPushButton *pushButton;
    QListWidget *playlist;
    QPushButton *output;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1363, 849);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new VideoWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 591, 411));
        OpenButton = new QPushButton(centralWidget);
        OpenButton->setObjectName(QStringLiteral("OpenButton"));
        OpenButton->setGeometry(QRect(0, 410, 41, 31));
        OpenButton->setAutoFillBackground(true);
        OpenButton->setStyleSheet(QStringLiteral(""));
        OpenButton->setIconSize(QSize(35, 35));
        PlayButton = new QPushButton(centralWidget);
        PlayButton->setObjectName(QStringLiteral("PlayButton"));
        PlayButton->setGeometry(QRect(40, 410, 41, 31));
        PlayButton->setAutoFillBackground(true);
        PlayButton->setStyleSheet(QStringLiteral(""));
        PlayButton->setIconSize(QSize(35, 35));
        PlayButton->setAutoRepeat(false);
        PlayButton->setAutoExclusive(false);
        totaltime = new QLabel(centralWidget);
        totaltime->setObjectName(QStringLiteral("totaltime"));
        totaltime->setGeometry(QRect(170, 420, 61, 21));
        totaltime->setStyleSheet(QLatin1String("color:rgb(0, 0, 0);\n"
"font: 14pt \"Constantia\";"));
        playtime = new QLabel(centralWidget);
        playtime->setObjectName(QStringLiteral("playtime"));
        playtime->setGeometry(QRect(90, 420, 81, 21));
        playtime->setStyleSheet(QLatin1String("color:rgb(85, 170, 127);\n"
"font: 14pt \"Constantia\";"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 420, 41, 21));
        playslider = new XSlider(centralWidget);
        playslider->setObjectName(QStringLiteral("playslider"));
        playslider->setGeometry(QRect(0, 460, 741, 22));
        playslider->setMaximum(999);
        playslider->setPageStep(100);
        playslider->setOrientation(Qt::Horizontal);
        showText = new QTableView(centralWidget);
        showText->setObjectName(QStringLiteral("showText"));
        showText->setGeometry(QRect(590, 0, 491, 411));
        add_row = new QPushButton(centralWidget);
        add_row->setObjectName(QStringLiteral("add_row"));
        add_row->setGeometry(QRect(590, 410, 151, 23));
        del_row = new QPushButton(centralWidget);
        del_row->setObjectName(QStringLiteral("del_row"));
        del_row->setGeometry(QRect(730, 410, 181, 23));
        save = new QPushButton(centralWidget);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(910, 410, 171, 23));
        confirm = new QPushButton(centralWidget);
        confirm->setObjectName(QStringLiteral("confirm"));
        confirm->setGeometry(QRect(380, 420, 75, 23));
        speedbox = new QComboBox(centralWidget);
        speedbox->setObjectName(QStringLiteral("speedbox"));
        speedbox->setGeometry(QRect(280, 420, 69, 22));
        wave = new Widget(centralWidget);
        wave->setObjectName(QStringLiteral("wave"));
        wave->setGeometry(QRect(0, 510, 1350, 160));
        changetime = new QPushButton(centralWidget);
        changetime->setObjectName(QStringLiteral("changetime"));
        changetime->setGeometry(QRect(10, 690, 341, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 690, 311, 23));
        playlist = new QListWidget(centralWidget);
        playlist->setObjectName(QStringLiteral("playlist"));
        playlist->setGeometry(QRect(1090, 0, 261, 431));
        output = new QPushButton(centralWidget);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(1090, 430, 261, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1363, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(OpenButton, SIGNAL(clicked()), MainWindow, SLOT(open()));
        QObject::connect(playslider, SIGNAL(sliderPressed()), MainWindow, SLOT(sliderPress()));
        QObject::connect(playslider, SIGNAL(sliderReleased()), MainWindow, SLOT(sliderRelease()));
        QObject::connect(PlayButton, SIGNAL(clicked()), MainWindow, SLOT(play()));
        QObject::connect(add_row, SIGNAL(clicked()), MainWindow, SLOT(addrow()));
        QObject::connect(del_row, SIGNAL(clicked()), MainWindow, SLOT(delrow()));
        QObject::connect(save, SIGNAL(clicked()), MainWindow, SLOT(save()));
        QObject::connect(confirm, SIGNAL(clicked()), MainWindow, SLOT(confirm()));
        QObject::connect(changetime, SIGNAL(clicked()), MainWindow, SLOT(settime()));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(start_from()));
        QObject::connect(playlist, SIGNAL(doubleClicked(QModelIndex)), MainWindow, SLOT(open_video()));
        QObject::connect(output, SIGNAL(clicked()), MainWindow, SLOT(output()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        OpenButton->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        PlayButton->setText(QApplication::translate("MainWindow", "Play", Q_NULLPTR));
        totaltime->setText(QApplication::translate("MainWindow", "000:00", Q_NULLPTR));
        playtime->setText(QApplication::translate("MainWindow", "000:00", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "/", Q_NULLPTR));
        add_row->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", Q_NULLPTR));
        del_row->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\241\214", Q_NULLPTR));
        save->setText(QApplication::translate("MainWindow", "\345\202\250\345\255\230", Q_NULLPTR));
        confirm->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244", Q_NULLPTR));
        changetime->setText(QApplication::translate("MainWindow", "\350\260\203\346\225\264\346\227\266\351\227\264", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start From", Q_NULLPTR));
        output->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
