#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <iostream>
#include <stdio.h>
#include "video_decoder_thread.h"

//#include <unistd.h>

// compatibility with newer API

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif


video_decoder_thread::video_decoder_thread(QObject *parent) : QThread(parent)
{


    pFormatCtx = NULL; //Set to NULL to prevent segmentation faults
    pCodecCtxOrig = NULL;
    pCodecCtx = NULL;
    pCodec = NULL;
    pFrame = NULL;
    pFrameRGB = NULL;
    buffer = NULL;
    sws_ctx = NULL;

    aCodecCtxOrig = NULL;
    aCodecCtx = NULL;
    aCodec = NULL;

    //audio swr
    //src_ch_layout = AV_CH_LAYOUT_STEREO; //get from stream
    dst_ch_layout = AV_CH_LAYOUT_STEREO;

    //src_sample_fmt = AV_SAMPLE_FMT_S32P; //get from data.
    dst_sample_fmt = AV_SAMPLE_FMT_S16;


    //src_rate = 44100; //get from stream.
    dst_rate = 44100;
    //src_nb_samples = 1024; //get from stream

    dst_data = NULL;


    continue_loop = false;

    //myIWM = (image_with_mutex*) malloc(sizeof(image_with_mutex));
    myIWM = new (image_with_mutex);
    myQueue = new (safe_queue);

}

void video_decoder_thread::put_in_queue(safe_queue *queue, unsigned char *frame)
{

    queue->lock.lock();
    if(queue->queue_size >= QUEUE_SIZE)
    {
        printf("Waiting for data to be emptied...\n");
        queue->emptied_cond.wait(&queue->lock);
    }
    queue->data[queue->head] = frame;
    //printf("head is %d.\n",queue->head);
    queue->head++;
    queue->head = queue->head%QUEUE_SIZE;
    queue->queue_size++;
    //printf("%d size of the queue is.\n",queue->queue_size);
    queue->filled_cond.wakeOne();
    queue->lock.unlock();

}
int video_decoder_thread::init_queue(safe_queue *queue)
{
    queue->data = (unsigned char**)malloc(sizeof(unsigned char*)*QUEUE_SIZE);
    queue->head = 0;
    queue->tail = 0;
    queue->queue_size = 0;
}

void video_decoder_thread::init_audio_swr()
{
    swr_ctx = swr_alloc();
    if (!swr_ctx)
    {
        fprintf(stderr, "Could not allocate resampler context\n");
        ret = AVERROR(ENOMEM);
        //free swctx.
    }
    /* set options */
    av_opt_set_int(swr_ctx, "in_channel_layout",    src_ch_layout, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate",       src_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", src_sample_fmt, 0);
    av_opt_set_int(swr_ctx, "out_channel_layout",    dst_ch_layout, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate",       dst_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", dst_sample_fmt, 0);
    /* initialize the resampling context */
    if ((ret = swr_init(swr_ctx)) < 0) {
        fprintf(stderr, "Failed to initialize the resampling context\n");
        //free swctx.
    }

    /* compute the number of converted samples: buffering is avoided
     * ensuring that the output buffer will contain at least all the
     * converted input samples */
    max_dst_nb_samples = dst_nb_samples =
        av_rescale_rnd(src_nb_samples, dst_rate, src_rate, AV_ROUND_UP);
    /* buffer is going to be directly written to a rawaudio file, no alignment */
    dst_nb_channels = av_get_channel_layout_nb_channels(dst_ch_layout);
    ret = av_samples_alloc_array_and_samples(&dst_data, &dst_linesize, dst_nb_channels,
                                             dst_nb_samples, dst_sample_fmt, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate destination samples\n");
        //free data and swrctx
    }
}

int video_decoder_thread::decode_audio_packet(int *got_frame, int cached)
{
    int ret = 0;
    int decoded = packet.size;
    *got_frame = 0;
    int dst_bufsize;

        /* decode audio frame */
        ret = avcodec_decode_audio4(aCodecCtx, frame, got_frame, &packet);
        if (ret < 0) {
            fprintf(stderr, "Error decoding audio frame (%s)\n", av_err2str(ret));
            return ret;
        }
        /* Some audio decoders decode only part of the packet, and have to be
         * called again with the remainder of the packet data.
         * Sample: fate-suite/lossless-audio/luckynight-partial.shn
         * Also, some decoders might over-read the packet. */
        decoded = FFMIN(ret, packet.size);
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

            //unsigned char sound[1024*2*2];
            /* compute destination number of samples */

            dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, src_rate) +
                                            src_nb_samples, dst_rate, src_rate, AV_ROUND_UP);
            if (dst_nb_samples > max_dst_nb_samples) {
                av_freep(&dst_data[0]);
                ret = av_samples_alloc(dst_data, &dst_linesize, dst_nb_channels,
                                       dst_nb_samples, dst_sample_fmt, 1);
                if (ret < 0)
                    exit(-1);//break;
                max_dst_nb_samples = dst_nb_samples;
            }

            // convert to destination format
            ret = swr_convert(swr_ctx, dst_data, dst_nb_samples, (const uint8_t **)frame->extended_data, src_nb_samples);
            if (ret < 0) {
                fprintf(stderr, "Error while converting\n");

                //free stuff
            }
            dst_bufsize = av_samples_get_buffer_size(&dst_linesize, dst_nb_channels,
                                                     ret, dst_sample_fmt, 1);
            if (dst_bufsize < 0) {
                fprintf(stderr, "Could not get sample buffer size\n");
                //free stuff
            }
            //printf("t:%f in:%d out:%d\n", t, src_nb_samples, ret);
            //fwrite(dst_data[0], 1, dst_bufsize, dst_file);

            qDebug()<< "Size of dst_buff" << dst_bufsize;
            unsigned char *sound = (unsigned char*)malloc(dst_bufsize);
            //memcpy(sound,dst_data[0],dst_bufsize);
            memcpy(sound,dst_data[0],dst_bufsize);
            put_in_queue(myQueue,sound);


            /*
            unsigned char *sound = (unsigned char*)malloc(BUFFER_SIZE);

            int i;
            short left_s,right_s;
            float left, right;
            //short left, right;

            for(i = 0; i<1024;i++)
            {
                left_s = (short)32000*sin((220*2*3.14*i)/44100);
                //right =  0;//(short)65000*sin((double)220*2*3.14*i/44100);

                //sound[4*i]     =    (unsigned char)left;
                //sound[4*i + 1] =    (unsigned char)left>>8;
                //sound[4*i + 2] =    (unsigned char)right;
                //sound[4*i + 3] =    (unsigned char)right>>8;

                memcpy(&left,frame->extended_data[0] + 4*i,4);
                memcpy(&right,frame->extended_data[1] + 4*i,4);

                left_s = left*32000;
                right_s = left*32000;

                //printf("float val %d\n",left_s);
                *(sound + 4*i)     =    left_s;  //casting to unsigned char before assignment makes things bad. no sound
                *(sound + 4*i + 1) =    left_s>>8;
                *(sound + 4*i + 2) =    right_s;
                *(sound + 4*i + 3) =    right_s>>8;
            }

            //unsigned char *sound = (unsigned char*)malloc(sizeof(unsigned char)*1024*2*2);
            put_in_queue(myQueue,sound);
            */

        }

        printf("successfully decoded stuff..\n");

    return decoded;
}

void video_decoder_thread::setFilename(QString filename_string)
{

    //QByteArray ba = filename_string.toLocal8Bit();
    //filename = (char*)ba.data();
}


void video_decoder_thread::run(){

    int got_frame,ret;

    filename = (char*)"/forlinx/media/test.mp4"; //this info will come from another file

    // Open video file
    if(avformat_open_input(&pFormatCtx, filename, NULL, NULL)!=0) //gives error 11 when does not find file
      exit(-1); // Couldn't open file

    // Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        exit(-1); // Couldn't open file

    // Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, filename, 0);

    // Find the first video stream
    videoStream=-1;
    audioStream=-1;

    for(i=0; i<pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoStream=i;
        }

        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO &&
        audioStream < 0)
        {
            audioStream=i;
            //cannot have break because of other steam
        }

    }
    if(videoStream==-1)
    {
        exit(-1); // Couldn't find video stream
    }
    if(audioStream==-1)
    {
        exit(-1); // Couldn't find audio stream
    }
    //AUDIO CODEC
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


    frame = av_frame_alloc(); //do we need to do this?
    if (!frame) {
        fprintf(stderr, "Could not allocate frame\n");
        exit(-1);
    }

    //send signal to start audio playback thread;
    //set data about stream here for the audio resamlpler

    src_ch_layout = aCodecCtx->channel_layout;
    src_rate = aCodecCtx->sample_rate;
    src_sample_fmt = aCodecCtx->sample_fmt;
    src_nb_samples = aCodecCtx->frame_size;

    init_queue(myQueue);
    init_audio_swr();
    int x_dst_bufsize = max_dst_nb_samples *4;
    qDebug("sending dest buff size to audio player %d \n",x_dst_bufsize);

    //while(1);

    audio_start_context.mutex.lock();
    audio_start_context.queue = myQueue;
    audio_start_context.buffer_size = x_dst_bufsize;
    //add buff size here
    audio_start_context.mutex.unlock();



    emit audio_capture_started(&audio_start_context); //mutex requrired??


    qDebug("video capture thread sends signal to video playback thread to start audio playback.");
    //VIDEO CODEC
    // Get a pointer to the codec context for the video stream
    pCodecCtxOrig=pFormatCtx->streams[videoStream]->codec;
    // Find the decoder for the video stream
    pCodec=avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec==NULL) {
      fprintf(stderr, "Unsupported codec!\n");
      exit(-1); // Couldn't open file
    }
    // Copy context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
      fprintf(stderr, "Couldn't copy codec context");
      exit(-1); // Couldn't open file
    }

    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
        exit(-1); // Couldn't open file

    // Allocate video frame
    pFrame=av_frame_alloc();

    // Allocate an AVFrame structure
    pFrameRGB=av_frame_alloc();
    if(pFrameRGB==NULL)
        exit(-1); // Couldn't open file

    // Determine required buffer size and allocate buffer
    numBytes=avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width,
                    pCodecCtx->height);
    buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

    char header [50];
    sprintf(header,"P6\n%d %d 255\n",pCodecCtx->width,pCodecCtx->height);

    fprintf(stderr, "numBytes %d, intosizeof %d", numBytes, numBytes*sizeof(uint8_t)); //same as expected
    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)pFrameRGB, buffer, AV_PIX_FMT_RGB24,
           pCodecCtx->width, pCodecCtx->height);

    // initialize SWS context for software scaling
    sws_ctx = sws_getContext(pCodecCtx->width,
                 pCodecCtx->height,
                 pCodecCtx->pix_fmt,
                 pCodecCtx->width,
                 pCodecCtx->height,
                 AV_PIX_FMT_RGB24,
                 SWS_BILINEAR,
                 NULL,
                 NULL,
                 NULL
                 );

    // Read frames and save first five frames to disk
    i=0;
    continue_loop = true;
    while(av_read_frame(pFormatCtx, &packet)>=0 && continue_loop)
    {
    // Is this a packet from the video stream?
    if(packet.stream_index==videoStream)
        {
        // Decode video frame
        avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

        // Did we get a video frame?
        if(frameFinished)
        {
            // Convert the image from its native format to RGB
            sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data,
            pFrame->linesize, 0, pCodecCtx->height,
            pFrameRGB->data, pFrameRGB->linesize);

            // Save the frame to disk
            /*
            if(++i<=5)
            SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height,
            i);
            }
            */
            //qDebug("%d",i++);

            unsigned char* image_buffer =(unsigned char*)malloc(numBytes+qstrlen(header));

            memmove(image_buffer, buffer, numBytes); //not sure how buffer works exactly but it contains rgb data
            memmove(image_buffer+qstrlen(header), image_buffer, numBytes);
            memcpy(image_buffer,header,qstrlen(header));

            //Critical section start.
            //QImage *qq=new QImage(image_buffer, FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH*3, QImage::Format_RGB888);
            //QImage *qq;
            myIWM->mutex.lock();
            myIWM->image = new QImage();

            if(myIWM->image->loadFromData(image_buffer,numBytes+qstrlen(header),"PPM"))
            {
            //myIWM->image = qq;
            emit frameDecoded(myIWM);
            myIWM->mutex.unlock();
            }
            else
            {
                qDebug("Data could not be loaded on image");
            }

            //delete myIWM->image; //delete qq in other method
            //end of critical section.

            free(image_buffer);

            }
            // Free the packet that was allocated by av_read_frame
            av_free_packet(&packet);
        }
        else if(packet.stream_index==audioStream)
        {

            do
            {
                ret = decode_audio_packet(&got_frame, 0);
                if (ret < 0)
                    break;
                packet.data += ret;
                packet.size -= ret;
            } while (packet.size > 0);

            // flush cached frames look at this part
            /*
            packet.data = NULL;
            packet.size = 0;
            /*
            do
            {
                decode_audio_packet(&got_frame, 1);
            } while (got_frame);
            */



        }
        else
        {
            av_free_packet(&packet);
        }

    }

    // Free the RGB image
    av_free(buffer);
    av_frame_free(&pFrameRGB);

    // Free the YUV frame
    av_frame_free(&pFrame);
    av_frame_free(&frame);


    // Close the codecs
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);

    // Close the video file
    avformat_close_input(&pFormatCtx);

    qDebug("video stopped x.");


    emit videoStopped();

}
video_decoder_thread::~video_decoder_thread()
{

}

void video_decoder_thread::stopThread()
{


continue_loop = false; // allow the run command finish by ending while //may need mutex
this->wait();          //wait for the thread to finish
qDebug("The video decoder thread has successfully finished");

}

void video_decoder_thread::startThread()
{
        qDebug()<<"The video decoder thread is starting!";
        continue_loop = true;
        this->start();
}




