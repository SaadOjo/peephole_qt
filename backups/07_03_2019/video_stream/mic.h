#ifndef MIC_H
#define MIC_H

#include <QDebug>

#include <QWidget>
#include <QObject>
#include <QAudioInput>
#include <QVBoxLayout>
#include <QAudioDeviceInfo>
#include <QAudioInput>

#include <stdlib.h>
#include <math.h>

class AudioDeviceIO : public QIODevice
{
    Q_OBJECT
public:
    AudioDeviceIO(QObject *parent, QAudioInput *device);
    ~AudioDeviceIO();

    void start();
    void stop();

    int LinearMax();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

    const char *soundData;

private:
    int m_maxValue;

signals:
    void update();
};


class Microphone : public QWidget
{
    Q_OBJECT
public:
    Microphone(QWidget *parent = 0);
    ~Microphone();
    AudioDeviceIO *audiodeviceIO;

private slots:
    void status();
    void toggleSuspend();
    void state(QAudio::State s);
    void handleSound();
private:

    QAudioDeviceInfo device;
    QAudioFormat format;
    QAudioInput *audioInput;


    char *buffer;
};


#endif // MIC_H
