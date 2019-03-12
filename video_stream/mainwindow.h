#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QDebug>
#include "microphone.h"
#include "speaker.h"
//#include "player_dialog.h"
#include "menu_dialog.h"
#include "encoder_thread.h"
#include "structures.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_start_btn_clicked();
    void on_stop_btn_clicked();
    void handleSound();

    void on_menu_btn_clicked();

signals:
    void setImage(image_with_mutex *i);

private:
    Ui::MainWindow *ui;

    Microphone mic;
    encoder_thread enc_thr;
    //encoder thread will come here

    Speaker spkr;
    //player_dialog *plr_diag;
    menu_dialog *mnu_dlg;

};

#endif // MAINWINDOW_H
