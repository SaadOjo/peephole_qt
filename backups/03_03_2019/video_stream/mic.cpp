#include "mic.h"


AudioDeviceIO::AudioDeviceIO(QObject *parent, QAudioInput *device)
    :QIODevice(parent)
{
    input = device;

    m_maxValue = 0;
}

AudioDeviceIO::~AudioDeviceIO()
{

}

void AudioDeviceIO::start()
{
    open(QIODevice::WriteOnly);
}

void AudioDeviceIO::stop()
{
    close();
}

qint64 AudioDeviceIO::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    Q_UNUSED(maxlen);

    return 0;
}

qint64 AudioDeviceIO::writeData(const char *data, qint64 len)
{
    //qDebug()<<"data:"<<data;

    int samples = len/2; // 2 bytes per sample
    int maxAmp = 32768; // max for S16 samples
    bool clipping = false;

    m_maxValue = 0;

    qint16 *s = (qint16*)data;

    // sample format is S16LE, only!

    for (int i = 0; i < samples; ++i) {
        qint16 sample = *s;
        s++;
        if (abs(sample) > m_maxValue) m_maxValue = abs(sample);
    }
    // check for clipping
    if (m_maxValue >= (maxAmp - 1))
        clipping = true;

    float value = ((float)m_maxValue/(float)maxAmp);
    if (clipping)
        m_maxValue = 100;
    else
        m_maxValue = (int)(value*100);

    ses=data;

    if(m_maxValue>0)
        emit update();

    return len;
}

int AudioDeviceIO::LinearMax()
{
    return m_maxValue;
}


Microphone::Microphone(QWidget *parent):QWidget(parent)
{

    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");


    if(format.sampleSize() != 16) {
        qWarning()<<"audio device doesn't support 16 bit samples, example cannot run";
        audioInput = 0;
        return;
    }

    audioInput = new QAudioInput(format,this); //here you can perhaps change the default device.
    connect(audioInput, SIGNAL(notify()), SLOT(status()));
    connect(audioInput, SIGNAL(stateChanged(QAudio::State)), SLOT(state(QAudio::State)));
    AudioDeviceIO  = new AudioDeviceIO(this,audioInput);
    audiodeviceIO->start();
    audioInput->start(audiodeviceIO);
}

Microphone::~Microphone() {}

void Microphone::status()
{
    //qWarning()<<"bytesReady = "<<audioInput->bytesReady()<<" bytes, elapsedUSecs = "<<audioInput->elapsedUSecs()<<", processedUSecs = "<<audioInput->processedUSecs();
}

void Microphone::toggleSuspend()
{
    // toggle suspend/resume
    if(audioInput->state() == QAudio::SuspendedState) {
        qWarning() << "status: Suspended, resume()";
        audioInput->resume();
    } else if (audioInput->state() == QAudio::ActiveState) {
        qWarning() << "status: Active, suspend()";
        audioInput->suspend();
    } else if (audioInput->state() == QAudio::StoppedState) {
        qWarning() << "status: Stopped, resume()";
        audioInput->resume();
    } else if (audioInput->state() == QAudio::IdleState) {
        qWarning() << "status: IdleState";
    }
}

void Microphone::state(QAudio::State state)
{
    qWarning() << " state=" << state;
}


