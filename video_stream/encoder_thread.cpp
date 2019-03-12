#include "encoder_thread.h"

encoder_thread::encoder_thread(QObject *parent) : QThread(parent)
{

    continue_loop = false;
    got_video_ctx = false;
    got_audio_ctx = false;
    filenumber = 0;


}
void encoder_thread::act_on_encoder_video_set_context(safe_encode_video_context* context)
{
    qDebug()<<"The entering video context save.!";
    context->mutex.lock();
    video_ctx = context; //dunno if it will work. (apparently works)
    //can use the same lock to protect the data as well.
    context->mutex.unlock();
    got_video_ctx = true;
}

void encoder_thread::act_on_encoder_audio_set_context(safe_encode_audio_context* context)
{
    qDebug()<<"The entering audio context save.!";
    context->mutex.lock();
    audio_ctx = context; //dunno if it will work. (apparently works)
    //can use the same lock to protect the data as well.
    context->mutex.unlock();
    got_audio_ctx = true;
}

void encoder_thread::run(){

    int j = 0;
    sprintf(filename,"video_%d.mp4",filenumber++);
    enc.init_format(filename);
//add video and audio ctx get

    while(!got_video_ctx||!got_audio_ctx) //can change with wait condition
    {
      //  qDebug()<<"Waiting for context!";
    }

    while(continue_loop)
    {
       enc.encode_video_frame(video_ctx);
       enc.encode_audio_frame(audio_ctx);
    }
    /*
    while( j<100)
    {

        if(j<10)
        {
            if(enc.encode_video_frame(video_ctx)) //maybe this should return if it is slower
            {
                j++;
            }
            //so this works
            //even though we first store audio and then video both start playing at the correct time
            //yes it works
        }
        else
        {
            if(enc.encode_audio_frame(audio_ctx))
            {
                j++;
            }

        }


       //enc.encode_video_frame(video_ctx);  //maybe this should return if it is slower
       //if no data just move on do not wait. //whatever is slower should return
       //what happens if there are two audio frames one after another??
       //enc.encode_audio_frame(audio_ctx);
    }
    */
    enc.close();

}


encoder_thread::~encoder_thread()
{

}

void encoder_thread::stopThread()
{

//got_ctx = false; //just to see

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

