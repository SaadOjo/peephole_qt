#ifndef VIDEO_DECODER_THREAD_H
#define VIDEO_DECODER_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include "structures.h"

extern "C"
{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}




class video_decoder_thread : public QThread
{
    Q_OBJECT

public:
    video_decoder_thread(QObject *parent = 0);
    ~video_decoder_thread();

    void stopThread();
    void startThread();
    image_with_mutex *myIWM;


protected:
    void run();
signals:
    //void frameDecoded(QImage *image);
    void frameDecoded(image_with_mutex *imageMutex);
    void videoStopped();

private:

    bool continue_loop;

    AVFormatContext   *pFormatCtx;
    int               i, videoStream;
    AVCodecContext    *pCodecCtxOrig;
    AVCodecContext    *pCodecCtx;
    AVCodec           *pCodec;
    AVFrame           *pFrame;
    AVFrame           *pFrameRGB;
    AVPacket          packet;
    int               frameFinished;
    int               numBytes;
    uint8_t           *buffer;
    struct SwsContext *sws_ctx;

};

#endif // VIDEO_DECODER_THREAD_H
