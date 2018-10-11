#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "xffmpeg.h"
#include <QMessageBox>
#include <xaudioplay.h>
#include <QToolBar>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QList>
#include "xencodethread.h"
#include "widget.h"
#include <QCheckBox>

static bool ispressSlider = false;
static bool isPlay = true;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startTimer(40);
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,"开始时间");
    model->setHeaderData(1,Qt::Horizontal,"结束时间");
    model->setHeaderData(2,Qt::Horizontal,"字幕");
    ui->showText->setModel(model);
    ui->showText->setColumnWidth(0,150);
    ui->showText->setColumnWidth(1,150);
    ui->showText->setColumnWidth(2,150);
    ui->speedbox->insertItem(0,tr("1"));
    ui->speedbox->insertItem(1,tr("0.5"));
    ui->speedbox->insertItem(2,tr("0.25"));
    ui->speedbox->insertItem(3,tr("0"));

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    int min = XFFmpeg::Get()->pts/1000/60;
    int sec = XFFmpeg::Get()->pts/1000%60;
    char buf[1024] = {0};
    sprintf(buf,"%03d:%02d",min,sec);
    ui->playtime->setText(buf);

    if(XFFmpeg::Get()->totalMs>0)
    {
        float rate = (float)XFFmpeg::Get()->pts/(float)XFFmpeg::Get()->totalMs;
        if(!ispressSlider){
            ui->playslider->setValue(rate*1000);
        }
    }
}

void MainWindow::addText(QFile myfile){ //添加文字
    int count = -1;
    while(!myfile.atEnd()){
        count++;
        QByteArray line = myfile.readLine();
        QString str(line);
        str.replace(QString("\n"),QString(""));
        QStringList strs = str.split(" ");
        model->setItem(count,0,new QStandardItem(strs[0]));
        model->setItem(count,1,new QStandardItem(strs[1]));
        model->setItem(count,2,new QStandardItem(strs[2]));
    }

}

void MainWindow::start_from(){
    ui->wave->startfrom_flag = true;
    XFFmpeg::Get()->isPlay = true;
    float pos = float(ui->wave->start_sample)/float(ui->wave->m_Wavefile.totalsample);
    XFFmpeg::Get()->Seek(pos);
}

void MainWindow::settime(){
    QString start_time = ui->wave->get_startTime();
    QString end_time = ui->wave->get_endTime();
    QItemSelectionModel *selections = ui->showText->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap<int,int> rows;
    foreach(QModelIndex index,selected)
    {
        rows.insert(index.row(),0);
    }
    QMapIterator<int,int> r(rows);
    r.toBack();
    while(r.hasPrevious())
    {
        r.previous();
        model->setItem(r.key(),0,new QStandardItem(start_time));
        model->setItem(r.key(),1,new QStandardItem(end_time));

    }
}

void MainWindow::sliderPress()
{
    ispressSlider=true;
}
void MainWindow::sliderRelease()
{
    ispressSlider=false;
    float pos = 0;
    pos = (float)ui->playslider->value() / (float)(ui->playslider->maximum()+1);
    XFFmpeg::Get()->Seek(pos);
}

void MainWindow::play(){
    ui->wave->startfrom_flag = false;
    XFFmpeg::Get()->isPlay = !XFFmpeg::Get()->isPlay;
    if(isPlay){
        //Pause
        ui->PlayButton->setText("Puase");
    }
    else{
        ui->PlayButton->setText("Play");
    }
}

void MainWindow::openFile(QString name){
    if(name.isEmpty()){
        return;
    }
    this->setWindowTitle(name);
    int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
    if(totalMs<=0)
    {
        QMessageBox::information(this,"err","file open failed!");
        return;
    }
    XAudioPlay::Get()->samplleRate = XFFmpeg::Get()->samplleRate;
    XAudioPlay::Get()->channel = XFFmpeg::Get()->channel;
    XAudioPlay::Get()->sampleSize = 16;
    XAudioPlay::Get()->Start();
    int min =(totalMs/1000)/60;
    int sec =(totalMs/1000)%60;
    char buf[1024]={0};
    sprintf(buf,"%03d:%02d",min,sec);
    ui->totaltime->setText(buf);
    XFFmpeg::Get()->isPlay = false;
    play();
}

void MainWindow::open(){
    bool flag = true;
    QStringList templist = QFileDialog::getOpenFileNames(this,QString("选择视频文件"));
    foreach (QString videoname, templist) {
        video_list.push_back(videoname);
        QString audioname = videoname.replace(QString("/video"),QString("/audio"));
        audioname = audioname.replace(QString(".flv"),QString(".wav"));
        audioname = audioname.replace(QString("/"),QString("\\"));
        audio_list.push_back(audioname);
        QString textname = videoname.replace(QString("/audio"),QString("/text"));
        textname = textname.replace(QString(".flv"),QString(".txt"));
        text_list.push_back(textname);
    }
    add_playlist();
}

void MainWindow::add_playlist(){
    ui->playlist->clear();
    foreach (QString name, video_list) {
        QString res = "";
        for(int i = 0;i<name.size();i++){
            if(name[i]=='/'){
                res = "";
                continue;
            }
            res += name[i];
        }
        QListWidgetItem *temp_item = new QListWidgetItem(res,ui->playlist);
        temp_item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        temp_item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::delrow(){
    QItemSelectionModel *selections = ui->showText->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap<int,int> rows;
    foreach(QModelIndex index,selected)
    {
        rows.insert(index.row(),0);
    }
    QMapIterator<int,int> r(rows);
    r.toBack();
    while(r.hasPrevious())
    {
        r.previous();
        model->removeRow(r.key());
    }
}


void MainWindow::save(){
    QString textname = this->textname;
    QFile file(textname);
    if(!file.open(QIODevice::Text|QIODevice::WriteOnly)){
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    for(int i=0;i<model->rowCount(QModelIndex());i++){
        QString str1 = model->data(model->index(i,0)).toString();
        QString str2 = model->data(model->index(i,1)).toString();
        QString str3 = model->data(model->index(i,2)).toString();
        if(i<model->rowCount(QModelIndex()))
        in<<str1+" "+str2+" "+str3<<endl;
        else in<<str1+" "+str2+" "+str3;
    }
    file.close();
}

void MainWindow::addrow(){
    QItemSelectionModel *selections = ui->showText->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.count()==0){
         QMessageBox::information(this,"err","Please select a item");
         return;
    }
    QMap<int,int> rows;
    foreach(QModelIndex index,selected)
    {
        rows.insert(index.row(),0);
        break;
    }
    QMapIterator<int,int> r(rows);
    r.toBack();
    r.previous();
    int count = r.key();
    for(int i= model->rowCount(QModelIndex());i>count;i--){
        QString str1 = model->data(model->index(i-1,0)).toString();
        QString str2 = model->data(model->index(i-1,1)).toString();
        QString str3 = model->data(model->index(i-1,2)).toString();
        model->setItem(i,0,new QStandardItem(str1));
        model->setItem(i,1,new QStandardItem(str2));
        model->setItem(i,2,new QStandardItem(str3));
    }
    model->setItem(count+1,0,new QStandardItem(""));
    model->setItem(count+1,1,new QStandardItem(""));
    model->setItem(count+1,2,new QStandardItem(""));
}

void MainWindow::confirm(){
    QString str = ui->speedbox->currentText();
    float muti = str.toFloat();
    XAudioPlay::Get()->samplleRate = float(44100)*0.6+float(44100)*0.4*muti;
    XFFmpeg::Get()->samplleRate =float(44100)*0.6+float(44100)*0.4*muti;
    float pos = 0;
    pos = (float)ui->playslider->value() / (float)(ui->playslider->maximum()+1);
    openFile(videoname);
    XFFmpeg::Get()->Seek(pos);
}

void MainWindow::open_video(){
    ui->playlist->item(tempplay)->setBackgroundColor(QColor(Qt::white));
    save();
    tempplay = ui->playlist->currentRow();
    int pos = tempplay;
    openFile(video_list[pos]);
    openText(text_list[pos]);
    ui->wave->open(audio_list[pos]);
    this->textname = text_list[pos];
    this->videoname = video_list[pos];
    ui->playlist->currentItem()->setBackgroundColor(QColor(Qt::red));
}

void MainWindow::output(){
    for(int i = 0;i<ui->playlist->count();i++){
        if(ui->playlist->item(i)->checkState()){
            QString output_url = text_list[i];
            output_url.replace(QString("text"),QString("output"));
            QString temptextname = textname;
            openText(text_list[i]);
            textname = output_url;
            save();
            textname = temptextname;
        }
    }
    openText(textname);
}

void MainWindow::openText(QString name){
    QFile myfile(name);
    int count = -1;
    if(!myfile.open(QIODevice::ReadWrite|QIODevice::Text)){
        return;
    }
    model->clear();
    while(!myfile.atEnd()){
        count++;
        QByteArray line = myfile.readLine();
        QString str(line);
        str.replace(QString("\n"),QString(""));
        QStringList strs = str.split(" ");
        if(strs.count()<3) {
            count--;
            continue;
        }
        model->setItem(count,0,new QStandardItem(strs[0]));
        model->setItem(count,1,new QStandardItem(strs[1]));
        model->setItem(count,2,new QStandardItem(strs[2]));
    }
    myfile.close();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return||event->key()==Qt::Key_Space){

        XFFmpeg::Get()->isPlay=!XFFmpeg::Get()->isPlay;
    }
}

