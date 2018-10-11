#ifndef XENCODETHREAD_H
#define XENCODETHREAD_H

#include<QThread>
class XEncodeThread:public QThread
{
public:
    static XEncodeThread *Get(){
        static XEncodeThread et;
        return  &et;
    }

    void run();
    XEncodeThread();
    ~XEncodeThread();
};

#endif // XENCODETHREAD_H
