#ifndef PLAYER_DIALOG_H
#define PLAYER_DIALOG_H

#include <QDialog>
#include "audio_decoder_thread.h"
#include "audio_playback_thread.h"
#include "structures.h"

namespace Ui {
class player_dialog;
}

class player_dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit player_dialog(QWidget *parent = 0);
    ~player_dialog();

signals:
    void setImage(image_with_mutex *i);
    
private slots:

    void on_back_btn_clicked();

    void on_pause_btn_clicked();

    void on_play_stop_btn_clicked();


    void on_seek_slider_valueChanged(int value);

    void on_volume_slider_valueChanged(int value);

    void on_mute_chk_toggled(bool checked);

    void videoStoppedSlot();

private:
    Ui::player_dialog *ui;
    audio_playback_thread athread;
    bool video_playing;

};

#endif // PLAYER_DIALOG_H
