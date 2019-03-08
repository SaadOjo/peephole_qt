#include "encoder_thread.h"

encoder_thread::encoder_thread(QObject *parent) : QThread(parent)
{

    continue_loop = false;
    got_ctx = false;

}
void encoder_thread::act_on_encoder_set_context(safe_encode_video_context* context)
{
    qDebug()<<"The entering context save.!";
    context->mutex.lock();
    video_ctx = context; //dunno if it will work.
    //can use the same lock to protect the data as well.
    context->mutex.unlock();
    got_ctx = true;

}



void encoder_thread::run(){

    enc.init_format();

    while(!got_ctx); //can change with wait condition

    while(continue_loop)
    {
        enc.encode_video_frame(video_ctx);
    }
    enc.close();
}


encoder_thread::~encoder_thread()
{

}

void encoder_thread::stopThread()
{


continue_loop = false; // allow the run command finish by ending while //may need mutex
this->wait();          //wait for the thread to finish
qDebug("The encoder thread has successfully finished");

}

void encoder_thread::startThread()
{
        qDebug()<<"The encoder thread is starting!";
        continue_loop = true;
        this->start();
}

