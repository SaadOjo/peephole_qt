#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<QMutex>
#include<QImage>
#include<QWaitCondition>


#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

struct image_with_mutex
{
    QMutex mutex;
    QImage *image;
};

struct safe_sound
{
    QMutex mutex;
    QWaitCondition cond;
    unsigned char *sound;
};

struct safe_sound_queue
{
    AVPacketList *first_pkt, *last_pkt;
    QMutex mutex;
    QWaitCondition cond;
    int nb_packets, size;
};
struct start_context
{
    QMutex              mutex;
    safe_sound_queue    *queue;
    AVCodecContext      *CodecCtx; //some info in here already
};

    //sound info
    /*
    wanted_spec.freq = aCodecCtx->sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = aCodecCtx->channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = aCodecCtx;
    */



#endif // STRUCTURES_H
