#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <iostream>
#include <stdio.h>

#include "audio_decoder_thread.h"

//#include <unistd.h>

/*
// compatibility with newer API

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif


audio_decoder_thread::audio_decoder_thread(QObject *parent) : QThread(parent)
{
    aCodecCtxOrig = NULL;
    aCodecCtx = NULL;
    aCodec = NULL;
    pFormatCtx = NULL;
    continue_loop = false;

}

int audio_decoder_thread::packet_queue_put(safe_sound_queue *q, AVPacket *pkt)
{
    AVPacketList *pkt1;

    if(pkt==NULL)
    {
       //Do some error handling here
       // return -1;
    }
    pkt1 = new (AVPacketList);
    if(pkt1 == NULL)
    {
        //do error handling here
    }
    q->mutex.lock();

    if (!q->last_pkt)
    {
        q->first_pkt = pkt1;
    }
    else
    {
        q->last_pkt->next = pkt1;
    }
    q->last_pkt = pkt1;
    q->nb_packets++;
    //q->size += pkt1->pkt.size; //cant determine size
    q->cond.wakeAll();
    q->mutex.unlock();


}

void audio_decoder_thread::run(){

    const char* filename = "/forlinx/media/test.mp4"; //this info will come from another file
    // Open video file
    if(avformat_open_input(&pFormatCtx, filename, NULL, NULL)!=0) //gives error 11 when does not find file
      exit(-1); // Couldn't open file

    // Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        exit(-1); // Couldn't open file

    // Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, filename, 0);

    // Find the first video stream
    audioStream=-1;

    for(i=0; i<pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO &&
           audioStream < 0)
        {
            audioStream=i;
            break;
        }
    }

    if(audioStream==-1)
    {
        exit(-1); // Couldn't find audio stream
    }


    aCodecCtxOrig=pFormatCtx->streams[audioStream]->codec;
    aCodec = avcodec_find_decoder(aCodecCtxOrig->codec_id);
    if(!aCodec)
    {
        fprintf(stderr, "Unsupported codec!\n");
        exit(-1);
    }

    // Copy context
    aCodecCtx = avcodec_alloc_context3(aCodec);
    if(avcodec_copy_context(aCodecCtx, aCodecCtxOrig) != 0) {
      fprintf(stderr, "Couldn't copy codec context");
      exit(-1); // Error copying codec context
    }

    //sets audio playback settings
    //set alsa here but the playback thread should do that.

    // Open codec
    if(avcodec_open2(aCodecCtx, aCodec, NULL)<0)
        exit(-1); // Couldn't open codec


    i=0;
    continue_loop = true;
    while(av_read_frame(pFormatCtx, &avpacket)>=0 && continue_loop)
    {

        if(avpacket.stream_index==audioStream)
        {

            packet_queue_put(&myQueue, &avpacket); //can instead put decoded packets
            qDebug("put packet in queue.");

        }
        else  //don't free packet if it is an audio packet. free when we decode
        {
            av_free_packet(&avpacket);
        }

    }

    // Close the video file
    avformat_close_input(&pFormatCtx);

    qDebug("audio capture stopped.");


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

*/
