#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <libv4l2.h>

#include "structures.h"

#define FRAME_WIDTH  320
#define FRAME_HEIGHT 240
#define FPS_AVG_OVER 20



#define CLEAR(x) memset(&(x), 0, sizeof(x))


class CaptureThread : public QThread
{
    Q_OBJECT

public:
    CaptureThread(QObject *parent = 0);
    ~CaptureThread();

    void stopThread();
    void startThread();    
    void setFileName(QString);
    void setDeviceName(QString);
    image_with_mutex *myIWM;

protected:
    void run();
signals:
    void renderedImage(image_with_mutex *image);

private:

    struct buffer
    {
            void   *start;
            size_t length;
    };

    struct v4l2_format              fmt;
    struct v4l2_buffer              buf;
    struct v4l2_requestbuffers      req;
    enum v4l2_buf_type              type;
    fd_set                          fds;
    struct timeval                  tv;
    int                             r, fd;
    unsigned int                    i, n_buffers;
    char* dev_name;
    char                            out_name[256];
    FILE                            *fout;
    struct buffer                   *buffers;
    bool                            continue_loop;
    QTime                           *time;
    unsigned long int               frame_counter;


    QMutex mutex;
    QWaitCondition condition;
    void closeVideoOut();
    QString fileName;
    QString deviceName;
};

static void xioctl(int fh, int request, void *arg)
{
        int r;

        do {
                r = v4l2_ioctl(fh, request, arg);
        } while (r == -1 && ((errno == EINTR) || (errno == EAGAIN)));

        if (r == -1) {
                fprintf(stderr, "error %d, %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
        }
}



#endif // CAPTURETHREAD_H
