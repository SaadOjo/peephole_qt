#ifndef AUDIO_DECODER_THREAD_H
#define AUDIO_DECODER_THREAD_H

#include <QThread>
#include <QImage>
#include <QTime>
#include <QMutex>
#include "structures.h"

extern "C"
{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}




class audio_decoder_thread : public QThread
{
    Q_OBJECT

public:
    audio_decoder_thread(QObject *parent = 0);
    ~audio_decoder_thread();

    void stopThread();
    void startThread();


protected:
    void run();
signals:

private:

    bool continue_loop;



};
#endif // AUDIO_DECODER_THREAD_H
