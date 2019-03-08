#include "player_dialog.h"
#include "ui_player_dialog.h"
#include <QDebug>

player_dialog::player_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::player_dialog)
{
    ui->setupUi(this);

    //connect(this,SIGNAL(setImage(QImage*)),ui->videoplyr_pane ,SLOT(setPicture(QImage*)));
    connect(this,SIGNAL(setImage(image_with_mutex*)),ui->videoplyr_pane ,SLOT(setPicture(image_with_mutex*)));

    connect(&ui->videoplyr_pane->thread,SIGNAL(videoStopped()),this ,SLOT(videoStoppedSlot())); //perhaps better to name it playback stopped
    connect(&ui->videoplyr_pane->thread,SIGNAL(audio_capture_started(start_context*)),&athread,SLOT(act_on_audio_thread_start(start_context*)));

    connect(&ui->videoplyr_pane->thread,SIGNAL(videoStopped()),&athread,SLOT(act_on_audio_thread_stop()));


    QString fileName = "/nfs/index.png";
    //QString fileName = QFileDialog::getOpenFileName(this,
    //tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    image_with_mutex first_image;
    first_image.mutex.lock();
    qDebug() << fileName;
    first_image.image = new QImage(fileName);
    first_image.mutex.unlock();
    //QImage image(fileName);
    emit setImage(&first_image);
    video_playing = false;
}

player_dialog::~player_dialog()
{
    delete ui;
}


void player_dialog::on_back_btn_clicked()
{
//go to video select menu
    //need to stop all threads before we go back
    close();
}

void player_dialog::on_pause_btn_clicked()
{
//pause the video
}

void player_dialog::on_play_stop_btn_clicked()
{
//toggle text
//stop start video playback

    if(!video_playing)
    {
        ui->play_stop_btn->setText("stop");
        video_playing = true;

        if(!ui->videoplyr_pane->thread.isRunning())  //Play Video
        {
            //ui->videoplyr_pane->thread.setFilename( QFileDialog::getOpenFileName(this,tr("Open Video"), "/", tr("Video Files (*.mp4)")));
            ui->videoplyr_pane->thread.startThread();
        }

        /*
        if(!athread.isRunning())  //Play Video
        {
            athread.startThread();
        }
        */


    }
    else
    {
        ui->play_stop_btn->setText("play");
        //athread.stopThread();
        ui->videoplyr_pane->thread.stopThread();

    }


}

void player_dialog::videoStoppedSlot()
{
    qDebug() << "Stopped button pressed.";
    ui->play_stop_btn->setText("play");
    video_playing = false;

}

void player_dialog::on_seek_slider_valueChanged(int value)
{
    // can use same speaker class but maybe a new object
}

void player_dialog::on_volume_slider_valueChanged(int value)
{
    // use the slider value to change the audio level
}

void player_dialog::on_mute_chk_toggled(bool checked)
{
    //turn audio on or off using checked bool
}
