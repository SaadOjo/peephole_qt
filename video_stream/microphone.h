#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>
#include <QString>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "structures.h"


//Check buffer sizes

class Microphone : public QThread
{
    Q_OBJECT

public:
    Microphone(QObject *parent = 0);
    ~Microphone();
    //unsigned char * sound;
    void stopThread();
    void startThread();
    safe_sound *mySS;
    safe_encode_audio_context my_safe_encode_audio_context;
    unsigned char *encoder_audio_buffer;

protected:
    void run();
signals:
    void soundAvailable(safe_sound * sound);
    void give_encode_audio_context(safe_encode_audio_context*);

private:
    int context_data_filled_atleast_once;

    bool continue_loop;
    int periods;
    int pcmreturn;
    unsigned int frequency;
    signed int left, right;
    snd_pcm_uframes_t buffer_frames;
    snd_pcm_uframes_t periodsize;
    snd_pcm_t *pcm_handle;
    void init();


    //QMutex mutex;
    //QWaitCondition condition;
};


#endif // MICROPHONE_H
