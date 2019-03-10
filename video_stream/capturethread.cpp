#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <QFile>
#include <typeinfo>
#include <iostream>

#include "capturethread.h"


CaptureThread::CaptureThread(QObject *parent) : QThread(parent)
{
    fd = -1;
    dev_name = (char*) "/dev/video1";
    continue_loop = true;
    time = new QTime;
    frame_counter = 0;
    myIWM = new(image_with_mutex);
    my_safe_encode_video_context.mutex.lock();
    my_safe_encode_video_context.put_data = false;
    my_safe_encode_video_context.mutex.unlock();

    context_data_filled_atleast_once = 0;
}

void CaptureThread::run(){
// Do main stuff here.

    time->start();


    fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
    if (fd < 0) {
            perror("Cannot open device");
            exit(EXIT_FAILURE);
    }

    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = FRAME_WIDTH;
    fmt.fmt.pix.height      = FRAME_HEIGHT;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
//        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
    xioctl(fd, VIDIOC_S_FMT, &fmt);
//        if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV) {
    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24) {
//                printf("Libv4l didn't accept YUYV format. Can't proceed.\\n");
            printf("Libv4l didn't accept RGB24 format. Can't proceed.\\n");
            exit(EXIT_FAILURE);
    }
    if ((fmt.fmt.pix.width != FRAME_WIDTH) || (fmt.fmt.pix.height != FRAME_HEIGHT))
            printf("Warning: driver is sending image at %dx%d\\n",
                    fmt.fmt.pix.width, fmt.fmt.pix.height);

    CLEAR(req);
    req.count = 2;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    xioctl(fd, VIDIOC_REQBUFS, &req);

    buffers = (buffer*) calloc(req.count, sizeof(*buffers));
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
            CLEAR(buf);

            buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory      = V4L2_MEMORY_MMAP;
            buf.index       = n_buffers;

            xioctl(fd, VIDIOC_QUERYBUF, &buf);

            buffers[n_buffers].length = buf.length;
            buffers[n_buffers].start = v4l2_mmap(NULL, buf.length,
                          PROT_READ | PROT_WRITE, MAP_SHARED,
                          fd, buf.m.offset);

            if (MAP_FAILED == buffers[n_buffers].start) {
                    perror("mmap");
                    exit(EXIT_FAILURE);
            }
    }

    for (i = 0; i < n_buffers; ++i)
    {
            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            xioctl(fd, VIDIOC_QBUF, &buf);
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    xioctl(fd, VIDIOC_STREAMON, &type);


    //loop

    char header [50];
    sprintf(header,"P6\n%d %d 255\n",fmt.fmt.pix.width,fmt.fmt.pix.height);

    //for (i = 0; i < 100; i++)
    while(continue_loop)
    {
        frame_counter++;
/*
        qDebug("frame: %d \n",frame_counter);
        qDebug("frame%10: %d \n",frame_counter%10);
        qDebug("frame%1: %d \n",frame_counter%1);

*/

        if(frame_counter%FPS_AVG_OVER == 0)
        {
           //qDebug("Frame Rate: %0.1f\n",FPS_AVG_OVER*1000.0/time->elapsed());
            time->start();

        }

            do {
                    FD_ZERO(&fds);
                    FD_SET(fd, &fds);

                    /* Timeout. */
                    tv.tv_sec = 2;
                    tv.tv_usec = 0;

                    r = select(fd + 1, &fds, NULL, NULL, &tv);
            } while ((r == -1 && (errno = EINTR)));
            if (r == -1) {
                    perror("select");
                    return;
            }

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            xioctl(fd, VIDIOC_DQBUF, &buf); //uncommented (this might have been the issue)

           /*
            sprintf(out_name, "out%03d.ppm", i);
            fout = fopen(out_name, "w");
            if (!fout) {
                    perror("Cannot open image");
                    exit(EXIT_FAILURE);
            }
            fprintf(fout, "P6\\n%d %d 255\\n",
                    fmt.fmt.pix.width, fmt.fmt.pix.height);
            printf("Size of buffer = %d \n",buf.bytesused);
            fwrite(buffers[buf.index].start, buf.bytesused, 1, fout);
            fclose(fout);
            */


            unsigned char* image_buffer =(unsigned char*)malloc(fmt.fmt.pix.sizeimage+qstrlen(header));

            qDebug("capture thread running.");


            //if more data send than encoded (slow encoder)



         //free(encoder_image_buffer);
         if(context_data_filled_atleast_once == 0)
         {
             encoder_image_buffer =(unsigned char*)malloc(fmt.fmt.pix.sizeimage); //memory leak possible as all the data might not be freed by the encoder
             memcpy(encoder_image_buffer, buffers[buf.index].start, fmt.fmt.pix.sizeimage); //use wait condition

             my_safe_encode_video_context.mutex.lock();
             my_safe_encode_video_context.data = encoder_image_buffer;
             my_safe_encode_video_context.put_data = true;
             my_safe_encode_video_context.mutex.unlock(); //more like a wait condition here just to make sure all data is freed,

             emit give_encode_video_context(&my_safe_encode_video_context);
             //emit encode_video_signal();
             context_data_filled_atleast_once = 1;

         }
         else
         {
             my_safe_encode_video_context.mutex.lock();
             //my_safe_encode_video_context.data = encoder_image_buffer;
             memcpy(encoder_image_buffer, buffers[buf.index].start, fmt.fmt.pix.sizeimage); //use wait condition
             my_safe_encode_video_context.put_data = true;
             my_safe_encode_video_context.cond.wakeOne();
             my_safe_encode_video_context.mutex.unlock(); //more like a wait condition here just to make sure all data is freed,

         }


            memmove(image_buffer, buffers[buf.index].start, fmt.fmt.pix.sizeimage);
            memmove(image_buffer+qstrlen(header), image_buffer, fmt.fmt.pix.sizeimage);
            memcpy(image_buffer,header,qstrlen(header));

            //QImage *qq=new QImage(image_buffer, FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH*3, QImage::Format_RGB888);
            //QImage *qq;
            //qq = new QImage();
            myIWM->mutex.lock(); //use wait condition
            myIWM->image = new QImage();

            if(myIWM->image->loadFromData(image_buffer,fmt.fmt.pix.sizeimage+qstrlen(header),"PPM"))
            {
                emit renderedImage(myIWM);
                myIWM->mutex.unlock();
            }
            else
            {
                qDebug("Data could not be loaded on image");
            }

            //delete qq; //deleted in service function
            free(image_buffer);

            xioctl(fd, VIDIOC_QBUF, &buf);
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMOFF, &type);
    for (i = 0; i < n_buffers; ++i)
            v4l2_munmap(buffers[i].start, buffers[i].length);
    v4l2_close(fd);



}
CaptureThread::~CaptureThread()
{

}
void CaptureThread::closeVideoOut(){

}
void CaptureThread::stopThread()
{


continue_loop = false; // allow the run command finish by ending while
this->wait();          //wait for the thread to finish
qDebug("The video thread has successfully finished");


}

void CaptureThread::startThread()
{
        qDebug()<<"The video thread is starting!";
        continue_loop = true;
        this->start();
}


void CaptureThread::setFileName(QString fileN) {
    fileName=fileN;
}

void CaptureThread::setDeviceName(QString fileN) {
    deviceName=fileN;
}



