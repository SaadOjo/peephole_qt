#ifndef VIDEO_DECODER_THREAD_H
#define VIDEO_DECODER_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include "structures.h"

/*
extern "C"
{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
*/

#define AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000


class video_decoder_thread : public QThread
{
    Q_OBJECT

public:
    video_decoder_thread(QObject *parent = 0);
    ~video_decoder_thread();

    void stopThread();
    void startThread();
    image_with_mutex *myIWM;
    safe_sound_queue myQueue;
    start_context audio_start_context;


protected:
    void run();
signals:
    //void frameDecoded(QImage *image);
    void frameDecoded(image_with_mutex *imageMutex);
    void audio_capture_started(start_context*);
    void videoStopped();

private:

    bool continue_loop;

    AVFormatContext   *pFormatCtx;
    int               i, videoStream,audioStream;
    AVCodecContext    *pCodecCtxOrig;
    AVCodecContext    *pCodecCtx;
    AVCodec           *pCodec;
    AVFrame           *pFrame;
    AVFrame           *pFrameRGB;
    AVPacket          packet;
    int               frameFinished;
    int               numBytes;
    uint8_t           *buffer;
    AVCodecContext    *aCodecCtxOrig;
    AVCodecContext    *aCodecCtx;
    AVCodec           *aCodec;
    struct SwsContext *sws_ctx;

    int packet_queue_put(safe_sound_queue *, AVPacket *);

};

#endif // VIDEO_DECODER_THREAD_H
