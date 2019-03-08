#include "audio_playback_thread.h"

audio_playback_thread::audio_playback_thread(QObject *parent) : QThread(parent)
{

    continue_loop = false;

}
void audio_playback_thread::act_on_audio_thread_start(start_context* context)
{
    context->mutex.lock();
    //myQueue =  context->queue;
    //myCodecCtx = context->CodecCtx;
    context->mutex.unlock();
    //set stuff here using codexctx;
    //qDebug("frequency from ctx: %d", (int)myCodecCtx->sample_rate);
/*
    periods = 2;
    buffer_frames = (8192*periods)>>2;
    frequency = 44100;
    //start thread;
*/
    //stuff moved to start thread for now.
    //startThread();
}
void audio_playback_thread::audio_playback_thread::act_on_audio_thread_stop()
{

    stopThread();
}


void audio_playback_thread::init()
{

    fprintf(stderr, "Initialising audio playback thread! \n");


    unsigned int frequency_exact;
    snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
    snd_pcm_hw_params_t *hwparams;
    char *pcm_name;
    pcm_name = strdup("plughw:0,0");
    snd_pcm_hw_params_alloca(&hwparams);

    if (snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
      fprintf(stderr, "Error opening Playback PCM device %s\n", pcm_name);
      exit(-1);
    }
   /* Init hwparams with full configuration space */
    if (snd_pcm_hw_params_any(pcm_handle, hwparams) < 0) {
      fprintf(stderr, "Can not configure this PCM device.\n");
      exit(-1);
    }


    if (snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
      fprintf(stderr, "Error setting access.\n");
      exit(-1);
    }

    /* Set sample format */
    if (snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0) {
      fprintf(stderr, "Error setting format.\n");
      exit(-1);
    }

    frequency_exact = frequency;
    if (snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &frequency_exact, 0) < 0) {
      fprintf(stderr, "Error setting rate.\n");
      exit(-1);
    }
    //Handle message in case frequency is not same

    /* Set number of channels */
    if (snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2) < 0) {
      fprintf(stderr, "Error setting channels.\n");
      exit(-1);
    }
    /* Set number of periods. Periods used to be called fragments. */
    if (snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0) < 0) {
      fprintf(stderr, "Error setting periods.\n");
      exit(-1);
    }

    /* Set buffer size (in frames). The resulting latency is given by */
    /* latency = periodsize * periods / (rate * bytes_per_frame)     */
    snd_pcm_uframes_t buffer_frames_exact = buffer_frames;
    if (snd_pcm_hw_params_set_buffer_size_near(pcm_handle, hwparams, &buffer_frames_exact) < 0) {
      fprintf(stderr, "Error setting buffersize.\n");
      exit(-1);
    }
    if(buffer_frames!=buffer_frames_exact)
    {
        printf("The desired buffer size of %d could not be set, \n going with nearest size of  %d \n",buffer_frames,buffer_frames_exact);
    }
    buffer_frames = buffer_frames_exact; //Make class property.
    periodsize = (buffer_frames << 2)/periods; // Might give errors for some
    frames = periodsize >> 2;

      /* Apply HW parameter settings to */
    /* PCM device and prepare device  */
    if (snd_pcm_hw_params(pcm_handle, hwparams) < 0) {
      fprintf(stderr, "Error setting HW params.\n");
      exit(-1);
    }

    //Free memory here
    //free(hwparams);
    //free(pcm_name);



}

int audio_playback_thread::open_codec_context(int *stream_idx,
                              AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, enum AVMediaType type)
{
    int ret, stream_index;
    AVStream *st;
    AVCodec *dec = NULL;
    AVDictionary *opts = NULL;
    ret = av_find_best_stream(fmt_ctx, type, -1, -1, NULL, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not find %s stream in input file '%s'\n",
                av_get_media_type_string(type), src_filename);
        return ret;
    } else {
        stream_index = ret;
        st = fmt_ctx->streams[stream_index];
        /* find decoder for the stream */
        dec = avcodec_find_decoder(st->codecpar->codec_id);
        if (!dec) {
            fprintf(stderr, "Failed to find %s codec\n",
                    av_get_media_type_string(type));
            return AVERROR(EINVAL);
        }
        /* Allocate a codec context for the decoder */
        *dec_ctx = avcodec_alloc_context3(dec);
        if (!*dec_ctx) {
            fprintf(stderr, "Failed to allocate the %s codec context\n",
                    av_get_media_type_string(type));
            return AVERROR(ENOMEM);
        }
        /* Copy codec parameters from input stream to output codec context */
        if ((ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar)) < 0) {
            fprintf(stderr, "Failed to copy %s codec parameters to decoder context\n",
                    av_get_media_type_string(type));
            return ret;
        }
        /* Init the decoders, with or without reference counting */
        av_dict_set(&opts, "refcounted_frames", refcount ? "1" : "0", 0);
        if ((ret = avcodec_open2(*dec_ctx, dec, &opts)) < 0) {
            fprintf(stderr, "Failed to open %s codec\n",
                    av_get_media_type_string(type));
            return ret;
        }
        *stream_idx = stream_index;
    }
    return 0;
}

int audio_playback_thread::decode_packet(int *got_frame, int cached)
{
    int ret = 0;
    int decoded = pkt.size;
    *got_frame = 0;
    if (pkt.stream_index == audio_stream_idx)
    {
        /* decode audio frame */
        ret = avcodec_decode_audio4(audio_dec_ctx, frame, got_frame, &pkt);
        if (ret < 0) {
            fprintf(stderr, "Error decoding audio frame (%s)\n", av_err2str(ret));
            return ret;
        }
        /* Some audio decoders decode only part of the packet, and have to be
         * called again with the remainder of the packet data.
         * Sample: fate-suite/lossless-audio/luckynight-partial.shn
         * Also, some decoders might over-read the packet. */
        decoded = FFMIN(ret, pkt.size);
        if (*got_frame) {
            size_t unpadded_linesize = frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)frame->format);
            //printf("audio_frame size %d\n",unpadded_linesize);

                     /*
            printf("audio_frame%s n:%d nb_samples:%d pts:%s\n",
                   cached ? "(cached)" : "",
                   audio_frame_count++, frame->nb_samples,
                   av_ts2timestr(frame->pts, &audio_dec_ctx->time_base));
                   */
            /* Write the raw audio data samples of the first plane. This works
             * fine for packed formats (e.g. AV_SAMPLE_FMT_S16). However,
             * most audio decoders output planar audio, which uses a separate
             * plane of audio samples for each channel (e.g. AV_SAMPLE_FMT_S16P).
             * In other words, this code will write only the first audio channel
             * in these cases.
             * You should use libswresample or libavfilter to convert the frame
             * to packed data. */

            //frame->extended_data[0], 1, unpadded_linesize;
            //second channel indata2

            unsigned char sound[1024*2*2];
            int i;
            short left_s,right_s;
            float left, right;
            //short left, right;

            for(i = 0; i<1024;i++)
            {
                left_s = (short)32000*sin((220*2*3.14*i)/44100);
                //right =  0;//(short)65000*sin((double)220*2*3.14*i/44100);
/*
                sound[4*i]     =    (unsigned char)left;
                sound[4*i + 1] =    (unsigned char)left>>8;
                sound[4*i + 2] =    (unsigned char)right;
                sound[4*i + 3] =    (unsigned char)right>>8;
                */
                memcpy(&left,frame->extended_data[0] + 4*i,4);
                memcpy(&right,frame->extended_data[1] + 4*i,4);

                left_s = left*32000;
                right_s = left*32000;

                //printf("float val %d\n",left_s);
                sound[4*i]     =    left_s;  //casting to unsigned char before assignment makes things bad. no sound
                sound[4*i + 1] =    left_s>>8;
                sound[4*i + 2] =    right_s;
                sound[4*i + 3] =    right_s>>8;
            }

            while ((pcmreturn = snd_pcm_writei(pcm_handle, sound , 1024)) < 0)
            {
             snd_pcm_prepare(pcm_handle);
             //add wait condition here
            fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
            }



        }
    }

    if (*got_frame && refcount)
        av_frame_unref(frame);
    return decoded;
}

int audio_playback_thread:: get_format_from_sample_fmt(const char **fmt,
                                      enum AVSampleFormat sample_fmt)
{
    int i;
    struct sample_fmt_entry {
        enum AVSampleFormat sample_fmt; const char *fmt_be, *fmt_le;
    } sample_fmt_entries[] = {
        { AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
        { AV_SAMPLE_FMT_S16, "s16be", "s16le" },
        { AV_SAMPLE_FMT_S32, "s32be", "s32le" },
        { AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
        { AV_SAMPLE_FMT_DBL, "f64be", "f64le" },
    };
    *fmt = NULL;
    for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++) {
        struct sample_fmt_entry *entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt) {
            *fmt = AV_NE(entry->fmt_be, entry->fmt_le);
            return 0;
        }
    }
    fprintf(stderr,
            "sample format %s is not supported as output format\n",
            av_get_sample_fmt_name(sample_fmt));
    return -1;
}


void audio_playback_thread::run(){

    printf("testing conversion from floating point to int and then to  array of unsigned char");


    init();
    int ret = 0, got_frame;
    src_filename = "/forlinx/media/test.mp4"; //this info will come from another file

    //goto end;

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }
    /* retrieve stream information */
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

    if (open_codec_context(&audio_stream_idx, &audio_dec_ctx, fmt_ctx, AVMEDIA_TYPE_AUDIO) >= 0)
    {
        audio_stream = fmt_ctx->streams[audio_stream_idx];
    }
    /* dump input information to stderr */
    av_dump_format(fmt_ctx, 0, src_filename, 0);

    if (!audio_stream) {
        fprintf(stderr, "Could not find audio or video stream in the input, aborting\n");
        ret = 1;
        goto end;
    }
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate frame\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /* initialize packet, set data to NULL, let the demuxer fill it */
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    /* read frames from the file */
    while (av_read_frame(fmt_ctx, &pkt) >= 0) {
        AVPacket orig_pkt = pkt;
        do {
            ret = decode_packet(&got_frame, 0);
            if (ret < 0)
                break;
            pkt.data += ret;
            pkt.size -= ret;
        } while (pkt.size > 0);
        av_packet_unref(&orig_pkt);
    }
    /* flush cached frames */
    pkt.data = NULL;
    pkt.size = 0;
    do {
        decode_packet(&got_frame, 1);
    } while (got_frame);


    if (audio_stream) {
        enum AVSampleFormat sfmt = audio_dec_ctx->sample_fmt;
        int n_channels = audio_dec_ctx->channels;
        const char *fmt;
        if (av_sample_fmt_is_planar(sfmt)) {
            const char *packed = av_get_sample_fmt_name(sfmt);
            printf("Warning: the sample format the decoder produced is planar "
                   "(%s). This example will output the first channel only.\n",
                   packed ? packed : "?");
            sfmt = av_get_packed_sample_fmt(sfmt);
            n_channels = 1;
        }
        if ((ret = get_format_from_sample_fmt(&fmt, sfmt)) < 0)
            goto end;
        printf("Play the output audio file with the command:\n"
               "ffplay -f %s -ac %d -ar %d \n",
               fmt, n_channels, audio_dec_ctx->sample_rate
                );
    }

/*
    while(continue_loop)
    {




                while ((pcmreturn = snd_pcm_writei(pcm_handle, (frame->data[0] + data_size*i), data_size)) < 0)
                {
                 snd_pcm_prepare(pcm_handle);
                 //add wait condition here
                fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
                }


        }
*/

end:

    avcodec_free_context(&audio_dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_frame_free(&frame);


    //free stuff before ending
    snd_pcm_drain(pcm_handle);
    if(snd_pcm_close(pcm_handle))
    {
        free(pcm_handle);

    }


}


audio_playback_thread::~audio_playback_thread()
{

}

void audio_playback_thread::stopThread()
{


continue_loop = false; // allow the run command finish by ending while //may need mutex
this->wait();          //wait for the thread to finish
qDebug("The audio playback thread has successfully finished");

}

void audio_playback_thread::startThread()
{       periods = 2; //overrides stuff set in on_start_
        buffer_frames = 1024*periods*2*2; //devide by //(bytespersample*channels)
        frequency = 44100;
        qDebug()<<"The audio playback thread is starting!";
        continue_loop = true;

        fmt_ctx = NULL;
        audio_dec_ctx = NULL;
        audio_stream = NULL;
        src_filename = NULL;

        frame = NULL;

        audio_stream_idx = -1;
        video_frame_count = 0;
        audio_frame_count = 0;
        refcount = 0;

        this->start();
}
/*
    while(continue_loop)
    {


        //wanted_spec.freq = aCodecCtx->sample_rate;
        //wanted_spec.format = AUDIO_S16SYS;
        //wanted_spec.channels = aCodecCtx->channels;

        qDebug("marker 1 ");


        if( !packet_queue_get(myQueue, pkt, 1) )
        {
            qDebug("marker 2 ");

            break;
        }
        qDebug("marker 3 ");


        // send the packet with the compressed data to the decoder
        ret = avcodec_send_packet(myCodecCtx, pkt);
        if (ret < 0) {
            fprintf(stderr, "Error submitting the packet to the decoder\n");
            exit(1);
        }

        // read all the output frames (in general there may be any number of them
        while (ret >= 0) {
            ret = avcodec_receive_frame(myCodecCtx, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                return;
            else if (ret < 0) {
                fprintf(stderr, "Error during decoding\n");
                exit(1);
            }
            data_size = av_get_bytes_per_sample(myCodecCtx->sample_fmt);
            if (data_size < 0)
            {
                // This should not occur, checking just for paranoia
                fprintf(stderr, "Failed to calculate data size\n");
                exit(1);
            }
            for (i = 0; i < frame->nb_samples; i++)
            {

                while ((pcmreturn = snd_pcm_writei(pcm_handle, (frame->data[0] + data_size*i), data_size)))
                {
                 snd_pcm_prepare(pcm_handle);
                 //add wait condition here
                fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
                }

            }

        }


    }
*/

