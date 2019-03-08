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

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
  FILE *pFile;
  char szFilename[32];
  int  y;

  // Open file
  sprintf(szFilename, "frame%d.ppm", iFrame);
  pFile=fopen(szFilename, "wb");
  if(pFile==NULL)
    return;

  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
  for(y=0; y<height; y++)
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

  // Close file
  fclose(pFile);
}

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
    continue_loop = false;

    //myIWM = (image_with_mutex*) malloc(sizeof(image_with_mutex));
    myIWM = new (image_with_mutex);

}

void video_decoder_thread::run(){

    const char* filename = "/forlinx/media/test.mp4"; //this info will come from another file
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
    for(i=0; i<pFormatCtx->nb_streams; i++)
      if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
        videoStream=i;
        break;
      }
    if(videoStream==-1)
        exit(-1); // Couldn't open file

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
    while(av_read_frame(pFormatCtx, &packet)>=0 && continue_loop) {
      // Is this a packet from the video stream?
      if(packet.stream_index==videoStream) {
        // Decode video frame
        avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

        // Did we get a video frame?
        if(frameFinished) {
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
      qDebug("%d",i++);

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

      }

      // Free the packet that was allocated by av_read_frame
      av_free_packet(&packet);
    }



    // Free the RGB image
    av_free(buffer);
    av_frame_free(&pFrameRGB);

    // Free the YUV frame
    av_frame_free(&pFrame);

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




