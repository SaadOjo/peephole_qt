#ifndef STRUCTURES_H
#define STRUCTURES_H


#define __STDC_FORMAT_MACROS
#if !defined __cplusplus || defined __STDC_FORMAT_MACROS

# if __WORDSIZE == 64
#  define __PRI64_PREFIX	"l"
#  define __PRIPTR_PREFIX	"l"
# else
#  define __PRI64_PREFIX	"ll"
#  define __PRIPTR_PREFIX
# endif

/* Macros for printing format specifiers.  */

/* Decimal notation.  */
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
# define PRId64		__PRI64_PREFIX "d"
#endif

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif


#include<QMutex>
#include<QImage>
#include<QWaitCondition>

//#include <inttypes.h>

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


struct safe_queue
{
unsigned char **data;
unsigned int head;
unsigned int tail;
unsigned int  queue_size;

QMutex lock;
QWaitCondition filled_cond, emptied_cond; //according to signal
};

struct start_context
{
    QMutex        mutex;
    safe_queue    *queue;
    int           buffer_size;
};

#define QUEUE_SIZE 300
//#define BUFFER_SIZE 1024*2*2

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
