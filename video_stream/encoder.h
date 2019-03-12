#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <stdio.h>
#include <QDebug>

#include "structures.h"

//change this for sure.
#define STREAM_FRAME_RATE 9 /* 9 images/s */
#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */

#define STREAM_DURATION   2.0
#define SCALE_FLAGS SWS_BICUBIC


extern "C"
{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/timestamp.h>
#include <libswresample/swresample.h>
}

typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc;
    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;
    AVFrame *frame;
    AVFrame *tmp_frame;
    float t, tincr, tincr2;
    struct SwsContext *sws_ctx;
    struct SwrContext *swr_ctx;
} OutputStream;


class encoder : public QObject
{
    Q_OBJECT
public:
    explicit encoder(QObject *parent = 0);
    //where is the deconstructor?

    void init_format(char * fname);
    void put_data(); //testing function. it will be replaced by slots.
    void close();
    int is_initialized(); //are we using it?
    bool encode_video_frame(safe_encode_video_context*);
    bool encode_audio_frame(safe_encode_audio_context*);


    //can personally set up the output formats.
signals:
    
public slots:
    //void encode_video_slot(safe_encode_video_data*);
    //void encode_video_slot();

private:
    int initialized;
    const char *filename;
    OutputStream video_st, audio_st;
    AVOutputFormat *fmt;
    AVFormatContext *oc;
    AVCodec *audio_codec, *video_codec;
    int ret;
    int have_video, have_audio;
    int encode_video, encode_audio;
    AVDictionary *opt;
    int i;

    void add_stream(OutputStream *ost, AVFormatContext *oc,
                           AVCodec **codec,
                           enum AVCodecID codec_id); //contains parameters about audio and video streams

    void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt);
    int write_frame(AVFormatContext *fmt_ctx, const AVRational *time_base, AVStream *st, AVPacket *pkt);

    AVFrame *get_audio_frame(OutputStream *ost, unsigned char* data);
    int write_audio_frame(AVFormatContext *oc, OutputStream *ost, unsigned char* data);
    void open_audio(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg);
    AVFrame *alloc_audio_frame(enum AVSampleFormat sample_fmt,
                                      uint64_t channel_layout,
                                      int sample_rate, int nb_samples);


    void open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg);
    AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height);

    void fill_yuv_image(AVFrame *pict, int frame_index, int width, int height);
    void fill_rgb_image(AVFrame *pict, int frame_index, int width, int height);

    AVFrame *get_video_frame(OutputStream *ost, unsigned char* data);

    void close_stream(AVFormatContext *oc, OutputStream *ost);
    int write_video_frame(AVFormatContext *oc, OutputStream *ost, unsigned char* data);


    
};

#endif // ENCODER_H
