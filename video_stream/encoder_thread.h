#ifndef ENCODER_THREAD_H
#define ENCODER_THREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QApplication> //to try and update stuff (app is getting stuck)


#include "structures.h"
#include "encoder.h"

class encoder_thread : public QThread
{
    Q_OBJECT

public:
    encoder_thread(QObject *parent = 0);
    ~encoder_thread();

    void stopThread(); //check if initialized
    void startThread();

protected:
    void run();
signals:

private slots:
    void act_on_encoder_video_set_context(safe_encode_video_context* context); //take the queue pointer
    void act_on_encoder_audio_set_context(safe_encode_audio_context* context);

    //void act_on_encoder_thread_start(safe_encode_video_context*); //take the queue pointer
    //dont immedietly start recording
    //wait for command
    //check if encoder has been initialised before starting thread
    //void act_on_encoder_thread_stop();

private:
    bool continue_loop;
    bool got_video_ctx, got_audio_ctx;
    encoder enc;
    safe_encode_video_context* video_ctx;
    safe_encode_audio_context* audio_ctx;
    int filenumber;
    char filename[50];



};


#endif // ENCODER_THREAD_H
