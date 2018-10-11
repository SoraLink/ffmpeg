#include "xencodethread.h"
#include "xffmpeg.h"
XEncodeThread::XEncodeThread()
{

}

void XEncodeThread::run(){
    FILE*fphWAV = fopen("test.mp3","wb+");
    while(1)
    {
        AVPacket pkt = XFFmpeg::Get()->Read();
        if(pkt.size<=0)
        {
            msleep(10);
            continue;
        }
        if(pkt.stream_index == XFFmpeg::Get()->audioStream){
            fwrite(pkt.data,1,pkt.size,fphWAV);
            printf("600");

        }
        av_free_packet(&pkt);
    }
    fclose(fphWAV);
}

XEncodeThread :: ~XEncodeThread()
{
    exec();
}
