#ifndef AUDIO_DECODER_THREAD_H
#define AUDIO_DECODER_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include "structures.h"
/*
extern "C"
{
#define __STDC_CONSTANT_MACROS
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
*/

/*
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

#define AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000


class audio_decoder_thread : public QThread
{
    Q_OBJECT

public:
    audio_decoder_thread(QObject *parent = 0);
    ~audio_decoder_thread();


    void stopThread();
    void startThread();
    safe_sound_queue myQueue;


protected:
    void run();
signals:
    void audio_decoder_thread_started(); //sends signal to tell the audio playback thread to start
    void audio_decoder_thread_stopped(); //sends signal to tell audio playback thread to stop
    //can also have signal for pause and stuff;
private:
    int packet_queue_put(safe_sound_queue *, AVPacket *);
    bool continue_loop;
    AVCodecContext  *aCodecCtxOrig;
    AVCodecContext  *aCodecCtx;
    AVCodec         *aCodec;
    AVPacket        avpacket;
    AVFormatContext *pFormatCtx;
    int             i, audioStream;




};
*/
#endif // AUDIO_DECODER_THREAD_H
