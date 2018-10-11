#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <qwidget.h>
#include<QOpenGLWidget>
#include"qpainter.h"
class VideoWidget:public QOpenGLWidget
{
public:
    VideoWidget(QWidget *p = NULL);
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    ~VideoWidget(){};
};

#endif // VIDEOWIDGET_H
