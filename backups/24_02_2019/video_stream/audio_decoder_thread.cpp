#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <iostream>
#include <stdio.h>

#include "audio_decoder_thread.h"

//#include <unistd.h>


// compatibility with newer API

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif


audio_decoder_thread::audio_decoder_thread(QObject *parent) : QThread(parent)
{

    continue_loop = false;

}

void audio_decoder_thread::run(){





}
audio_decoder_thread::~audio_decoder_thread()
{

}

void audio_decoder_thread::stopThread()
{


continue_loop = false; // allow the run command finish by ending while //may need mutex
this->wait();          //wait for the thread to finish
qDebug("The audio decoder thread has successfully finished");

}

void audio_decoder_thread::startThread()
{
        qDebug()<<"The audio decoder thread is starting!";
        continue_loop = true;
        this->start();
}

