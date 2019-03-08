#ifndef AUDIO_PLAYBACK_THREAD_H
#define AUDIO_PLAYBACK_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include <QDebug>
#include <assert.h>

#include <alsa/asoundlib.h>



#define __STDC_FORMAT_MACROS
#define __STDC_CONSTANT_MACROS // for UINT64_C

#include "structures.h"


extern "C"
{
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
//#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
}




class audio_playback_thread : public QThread
{
    Q_OBJECT

public:
    audio_playback_thread(QObject *parent = 0);
    ~audio_playback_thread();

    void stopThread();
    void startThread();

protected:
    void run();
signals:

private slots:
    void act_on_audio_thread_start(start_context*); //take the queue pointer
    void act_on_audio_thread_stop();

private:

    int open_codec_context(int *stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, enum AVMediaType type);
    int decode_packet(int *got_frame, int cached);
    int get_format_from_sample_fmt(const char **fmt,enum AVSampleFormat sample_fmt);

    bool continue_loop;

    //Decoder stuff
    AVFormatContext *fmt_ctx;
    AVCodecContext *audio_dec_ctx;
    AVStream *audio_stream;
    const char *src_filename;
    int audio_stream_idx;
    AVFrame *frame;
    AVPacket pkt;
    int video_frame_count;
    int audio_frame_count;

    int refcount; //DO NOT need this


    //Alsa related stuff
    int periods;
    int pcmreturn;
    int frames;

    unsigned int frequency;
    signed int left, right;
    snd_pcm_uframes_t buffer_frames;
    snd_pcm_uframes_t periodsize;
    snd_pcm_t *pcm_handle;

    void init();

};

#endif // AUDIO_PLAYBACK_THREAD_H
