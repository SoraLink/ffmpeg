#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include<QMouseEvent>
#include<QMutex>
#include "wavefile.h"
#include<QTimer>
namespace UI {
class Wigdet;
}

class Widget : public QWidget
{
public:
    static Widget *Get()
    {
        static Widget wave;
        return &wave;
    }
    Widget(QWidget *p = NULL);
    ~Widget();
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void open(QString filename);
    int startfrom_end;
    QString get_startTime();
    QString get_endTime();
    int start_sample;
    int end_sample;
    WaveFile m_Wavefile;
    bool startfrom_flag = false;
private:
    UI::Wigdet *ui;
    void Draw16Bit(QPainter &p,int W,int H);
    void Draw8Bit(QPainter &p,int W,int H);
    void Drawstart(QPainter &p,int i);
    void Drawend(QPainter &p,int i);
    bool m_DrawWave;
    QString m_Filename;
    double m_SamplePerPixel;
    double m_ZoomFactor;
    int m_OffsetInSamples;
    int total_Sample;
    int bitpersample;
    int start_offset = 0;
    int end_offset = 0;
    int start;
    int end;
    int V_hour=0;
    int V_min=0;
    int V_sec=0;
    int V_msec=0;
    bool flag = true;
    int start_pos=0;
    int end_pos=0;
    int store=0;
    QMutex mutex;
};

#endif // WIDGET_H
