#ifndef VIDEO_DECODER_THREAD_H
#define VIDEO_DECODER_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include <QFileDialog> //temp
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

extern "C"
{
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>
}



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
    void setFilename(QString filename);
    image_with_mutex *myIWM;
    safe_queue *myQueue;
    start_context audio_start_context;


protected:
    void run();
signals:
    //void frameDecoded(QImage *image);
    void frameDecoded(image_with_mutex *imageMutex);
    void audio_capture_started(start_context*);
    void videoStopped();

private:

    char* filename;

    bool continue_loop;

    AVFormatContext   *pFormatCtx;
    int               i, videoStream,audioStream;
    AVCodecContext    *pCodecCtxOrig;
    AVCodecContext    *pCodecCtx;
    AVCodec           *pCodec;
    AVFrame           *pFrame,*frame;
    AVFrame           *pFrameRGB;
    AVPacket          packet;
    int               frameFinished;
    int               numBytes;
    uint8_t           *buffer;
    AVCodecContext    *aCodecCtxOrig;
    AVCodecContext    *aCodecCtx;
    AVCodec           *aCodec;
    struct SwsContext *sws_ctx;

    //resampler stuff
    struct SwrContext *swr_ctx;
    int dst_nb_samples;
    int max_dst_nb_samples;
    int dst_nb_channels;
    int dst_linesize;
    uint8_t **dst_data;


    int64_t src_ch_layout; //get from stream
    int64_t dst_ch_layout;

    enum AVSampleFormat src_sample_fmt; //get from data.
    enum AVSampleFormat dst_sample_fmt;

    int ret;
    int src_rate; //get from stream.
    int dst_rate;
    int src_nb_samples; //get from stream

    void init_audio_swr();

    int decode_audio_packet(int *got_frame, int cached);
    void put_in_queue(safe_queue *queue, unsigned char *frame);
    int init_queue(safe_queue *queue);
};

#endif // VIDEO_DECODER_THREAD_H
