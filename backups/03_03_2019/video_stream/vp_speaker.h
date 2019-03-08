#ifndef VP_SPEAKER_H
#define VP_SPEAKER_H

#include <QObject>
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

class vp_speaker : public QObject
{
    Q_OBJECT
public:
    explicit vp_speaker(QObject *parent = 0);
    ~vp_speaker();
    void start();
    void stop();
    bool isStarted();

signals:

private:

    int periods;
    int pcmreturn;
    int frames;
    unsigned int frequency;
    signed int left, right;
    snd_pcm_uframes_t buffer_frames;
    snd_pcm_uframes_t periodsize;
    snd_pcm_t *pcm_handle;
    void init();
    bool started;

public slots:
    void playSound(safe_sound * sound);

};
#endif // VP_SPEAKER_H
