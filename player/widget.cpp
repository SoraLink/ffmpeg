#include "widget.h"
#include <QPainter>
#include <qmessagebox.h>
#include <QTextCodec>
#include <xffmpeg.h>
#include <windows.h>
#define MIN(x,y) (x)<(y)?(x):(y)
#define MAX(x,y) (x)>(y)?(x):(y)
Widget::Widget(QWidget *parent) : QWidget(parent)
{
    startTimer(2);
    m_Filename = "";
    if(m_Filename == "")
        return;
    m_Wavefile.WavRead(m_Filename.toStdString());
    m_SamplePerPixel = 0.0;
    m_OffsetInSamples = 0;
    m_Filename = "";
    total_Sample = m_Wavefile.totalsample;
    bitpersample = m_Wavefile.bitpersample;
    end = total_Sample;
    start = 0;

}

void Widget::open(QString filename){
    m_Filename = filename;
    if(m_Filename == "")
        return;
    m_Wavefile.WavRead(m_Filename.toStdString());
    m_SamplePerPixel = 0.0;
    m_OffsetInSamples = 0;
    m_Filename = "";
    total_Sample = m_Wavefile.totalsample;
    bitpersample = m_Wavefile.bitpersample;
    end = total_Sample;
    start = 0;
}

Widget::~Widget(){
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    flag = true;
    int W = this->width();
    int H = this->height();

    QPixmap pix(W,H);
    pix.fill(Qt::black);
    QPainter p(&pix);
    QPen pen;
    pen.setColor(QColor(00,35,00));
    p.setPen(pen);

    int i;
    double x,y;
    int col_num = 30;
    int row_num = 13;

    for(i = 0; i<=col_num;i++){
        x = i*W / col_num;
        p.drawLine((int)x,0,(int)x,H);
    }
    for(i = 0; i<=row_num;i++){
        y = i*H / row_num;
        p.drawLine(0,(int)y,W,(int)y);
    }
    pen.setColor(QColor(0x4B,0xF3,0xA7));

    p.setPen(pen);
    

    m_DrawWave = true;
    QString temptime = QString::number(V_hour,10)+":"+QString::number(V_min,10)+":"+QString::number(V_sec,10)+":"+QString::number(V_msec,10);
    p.drawText(0,20,temptime);
    pen.setColor(QColor(0x4B,0xF3,0xA7));
    p.setPen(pen);
    if(m_DrawWave)
    {
        m_SamplePerPixel = (float(total_Sample) / float(W));
        p.drawLine(0,H/2,W,H/2);
        
        if(bitpersample == 16)
            Draw16Bit(p,W,H);
        else if(bitpersample==8)
            Draw8Bit(p,W,H);
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

void Widget::Draw16Bit(QPainter &p, int W, int H)
{
    p.drawRect(0,0,W-1,H-1);
    int prevX = 0;
    int prevY = 0;
    int i = 0;
    int index = m_OffsetInSamples;
    int maxSampleToShow = (int) ((m_SamplePerPixel * W) + m_OffsetInSamples);
    maxSampleToShow = MIN(maxSampleToShow,m_Wavefile.datanum);
    bool start_flag = true;
    bool end_flag = true;
    while(index<maxSampleToShow)
    {
        short maxVal = -32767;
        short minVal = 32767;
        
        for(int x=0; x < m_SamplePerPixel&&x+index+start_offset<m_Wavefile.datanum-end_offset ; x++)
        {
            maxVal = MAX(maxVal,m_Wavefile.Data[x+index+start_offset]);
            minVal = MIN(minVal,m_Wavefile.Data[x+index+start_offset]);
        }
        if(index+start_offset>=start_sample&&start_flag){
            Drawstart(p,i);
            start_flag = false;
        }
        if(index+start_offset>=end_sample&&end_flag){
            Drawend(p,i);
            startfrom_end = i;
            end_flag  = false;
        }
        int secs = (index+start_offset)/m_Wavefile.head.samplerate;
        int hour = secs/3600;
        int min = secs%3600/60;
        int sec = secs%60;
        int msecs = ((index+start_offset)%m_Wavefile.head.samplerate)/16;
        QString time = QString::number(hour,10)+":"+QString::number(min,10)+":"+QString::number(sec,10)+":"+QString::number(msecs,10);
        if(msecs+sec*1000+min*60000+hour*3600000>V_msec+V_sec*1000+V_min*60000+V_hour*3600000&&flag){
            p.drawLine(i,0,i,160);
            flag = false;
        }
        if(i%10 == 0){
            p.drawLine(i,158,i,160);
        }
        if(i%50 == 0){
            p.drawLine(i,156,i,160);
        }
        if(i%100 == 0){
            p.drawLine(i,154,i,160);
            p.drawText(i,152,time);
        }
        
        int scaledMinVal = (int)(((minVal + 32768)*H)/65536);
        int scaledMaxVal = (int)(((maxVal + 32768)*H)/65536);
        
        scaledMinVal = H - scaledMinVal;
        scaledMaxVal = H - scaledMaxVal;
        
        if(m_SamplePerPixel > 0.0000000001)
        {
            if(scaledMinVal == scaledMaxVal)
            {
                if(prevY != 0)
                    p.drawLine(prevX,prevY,i,scaledMaxVal);
            }
            else
            {
                p.drawLine(i,scaledMinVal,i,scaledMaxVal);
            }
        }
        else
            return;
        prevX = i;
        prevY = scaledMaxVal;
        
        i++;
        index = (int)(i*m_SamplePerPixel) + m_OffsetInSamples;
    }

}
void Widget::Drawstart(QPainter &p, int i){
    QPen pen;
    pen.setColor(QColor(255,0,0));
    p.setPen(pen);
    p.drawLine(i,0,i,this->height());
    pen.setColor(QColor(0x4B,0xF3,0xA7));
    p.setPen(pen);
}

void Widget::Drawend(QPainter &p, int i){
    QPen pen;
    pen.setColor(QColor(255,255,0));
    p.setPen(pen);
    p.drawLine(i,0,i,this->height());
    pen.setColor(QColor(0x4B,0xF3,0xA7));
    p.setPen(pen);
}

void Widget::Draw8Bit(QPainter &p, int W, int H){
    int prevX = 0;
    int prevY = 0;
    
    int i = 0;
    
    int index = m_OffsetInSamples;
    int maxSampleToShow = (int)((m_SamplePerPixel * W)+m_OffsetInSamples);
    
    maxSampleToShow = MIN(maxSampleToShow,m_Wavefile.datanum);
    while(index<maxSampleToShow){
        short maxVal = 0;
        short minVal = 255;
        
        for(int x = 0; x < m_SamplePerPixel; x++){
            short low, high;
            low = (short)(m_Wavefile.Data[x+index]&0x00ff);
            high = (short)(m_Wavefile.Data[x+index] >> 8 & 0x00ff);
            maxVal = MAX(maxVal,low);
            minVal = MIN(minVal,low);
            maxVal = MAX(maxVal,high);
            minVal = MIN(minVal,high);
        }
        int scaledMinVal = (int)(((minVal)*H)/256);
        int scaledMaxVal = (int)(((maxVal)*H)/256);

        scaledMinVal = H - scaledMinVal;
        scaledMaxVal = H - scaledMaxVal;

        if(m_SamplePerPixel > 0.0000000001)
        {

            if(scaledMinVal == scaledMaxVal){
                if(prevY != 0)
                    p.drawLine(i,scaledMinVal,i,scaledMaxVal);
            }
            else
            {
                p.drawLine(i,scaledMinVal,i,scaledMaxVal);
            }

        }
        else return;

        prevX = i;
        prevY = scaledMaxVal;

        i++;
        index = (int)(i*m_SamplePerPixel)+m_OffsetInSamples;
        
    }
}

void Widget::timerEvent(QTimerEvent *event){
    V_hour=XFFmpeg::Get()->pts/1000/60/60;
    V_min = XFFmpeg::Get()->pts/1000/60%60;
    V_sec = XFFmpeg::Get()->pts/1000%60;
    V_msec = XFFmpeg::Get()->pts%1000;
    int middle = (V_hour*60*60+V_min*60+V_sec)*m_Wavefile.head.samplerate+V_msec*(m_Wavefile.head.samplerate/1000);
    bool flag_follow = XFFmpeg::Get()->isPlay;
    if(flag_follow&&start_offset!=0&&end_offset!=0&&middle - (total_Sample/2)>0&&middle + (total_Sample/2)<m_Wavefile.totalsample){
        start_offset = middle - (total_Sample/2);
        start = start_offset;
        end =  middle + (total_Sample/2);
        end_offset = m_Wavefile.totalsample - end;
        total_Sample = end - start;
    }
    if(middle>=end_sample&&startfrom_flag){
        XFFmpeg::Get()->isPlay = false;
    }
    this->update();
}

QString Widget::get_startTime(){
    int secs = start_sample/m_Wavefile.head.samplerate;
    int hour = secs/3600;
    int min = secs%3600/60;
    int sec = secs%60;
    int msecs = ((start_sample)%m_Wavefile.head.samplerate)/16;
    QString start_time = QString::number(hour,10)+":"+QString::number(min,10)+":"+QString::number(sec,10)+":"+QString::number(msecs,10);
    return start_time;
}

QString Widget::get_endTime(){
    int secs = end_sample/m_Wavefile.head.samplerate;
    int hour = secs/3600;
    int min = secs%3600/60;
    int sec = secs%60;
    int msecs = ((end_sample)%m_Wavefile.head.samplerate)/16;
    QString end_time = QString::number(hour,10)+":"+QString::number(min,10)+":"+QString::number(sec,10)+":"+QString::number(msecs,10);
    return end_time;
}

void Widget::wheelEvent(QWheelEvent *event){
    mutex.lock();
    if(event->pos().x()>0&&event->pos().x()<this->width()&&event->pos().y()>0&&event->pos().y()<160){
        if(event->delta()>0&&total_Sample*0.8>this->width()){
            float rate = float(event->pos().x())/float(this->width());
            int tempsample = total_Sample*rate+start;
            start_offset = (tempsample-start)*0.2+start_offset;
            end = end - (end - tempsample)*0.2;
            start = start_offset;
            end_offset = m_Wavefile.totalsample - end;
            total_Sample = end - start;
            this->update();
        }
        else if(event->delta()<0 ){
            if(total_Sample/0.8<m_Wavefile.totalsample){
                 float rate = float(event->pos().x()/float(this->width()));
                 int tempsample = total_Sample*rate+start;
                 if(start_offset - (tempsample-start)*0.2>0&&end+(end-tempsample)*0.2<m_Wavefile.totalsample){
                    start_offset =start_offset - (tempsample-start)*0.2;
                    start = start_offset;
                    end = end+(end-tempsample)*0.2;
                    end_offset = m_Wavefile.totalsample - end;
                    total_Sample = end - start;
                    this->update();
                 }
                 else{
                     start = 0;
                     start_offset = 0;
                     end_offset = 0;
                     end = m_Wavefile.totalsample;
                     total_Sample = m_Wavefile.totalsample;
                     this->update();
                 }
            }
            else{
                start = 0;
                start_offset = 0;
                end_offset = 0;
                end = m_Wavefile.totalsample;
                total_Sample = m_Wavefile.totalsample;
                this->update();
            }

        }
    }
    mutex.unlock();
    return;
}
void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        start_pos = event->pos().x();
        int x = start_pos;
        int m = this->width();
        int mm = start_offset;
        int sm = total_Sample;
        float chu = float(start_pos)/float(this->width());
        float chen = (float(start_pos)/float(this->width()))*total_Sample;
        start_sample = (float(start_pos)/float(this->width()))*total_Sample+start_offset;
        int mmm = start_sample;
        int hahaha = mmm;
    }
    else if(event->button() == Qt::RightButton){
        end_pos = event->pos().x();
        end_sample = (float(end_pos)/float(this->width()))*total_Sample+start_offset;
    }
}



