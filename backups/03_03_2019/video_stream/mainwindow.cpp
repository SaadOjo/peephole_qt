#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(this,SIGNAL(setImage(image_with_mutex*)),ui->videoPane,SLOT(setPicture(image_with_mutex*)));
    //connect(mic.audiodeviceIO,SIGNAL(update()),this,SLOT(handleSound()));
    connect(&mic, SIGNAL(soundAvailable(safe_sound*)),&spkr, SLOT(playSound(safe_sound*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_btn_clicked()
{

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





    if(!ui->videoPane->thread.isRunning()){
        //ui->btnStartStopCapture->setText(tr("Stop"));
        //if(!ui->txtFileOut->text().isEmpty())
            //ui->videoViever->setFileName(ui->txtFileOut->text());
            //ui->videoViever->setDeviceName(ui->txtDevice->text());
           ui->videoPane->thread.startThread();
    }


    if(!spkr.isStarted())
    {
        spkr.start();

    }


    if(!mic.isRunning())
    {
        mic.startThread();
    }


    /*
    else {
        //ui->btnStartStopCapture->setText(tr("Start Capture"));
        ui->videoPane->thread.stopThread();
    }
    */
    //connect(&mic, SIGNAL(soundAvailable(unsigned char*)),&spkr, SLOT(playSound(unsigned char*)));

}

void MainWindow::on_stop_btn_clicked()
{
    ui->videoPane->thread.stopThread();
    //disconnect(&mic, SIGNAL(soundAvailable(unsigned char*)),&spkr, SLOT(playSound(unsigned char*)));

    mic.stopThread();
    if(spkr.isStarted())
    {
        spkr.stop(); //order changed to stop the buffer underrun thing

    }





}

void MainWindow::handleSound()
{
    qDebug() << "Handle Sound!";
}


void MainWindow::on_menu_btn_clicked()
{

    plr_diag = new player_dialog(this);
    plr_diag->showFullScreen();




}
