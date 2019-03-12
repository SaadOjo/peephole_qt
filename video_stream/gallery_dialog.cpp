#include "gallery_dialog.h"
#include "ui_gallery_dialog.h"
#include <iostream>
#include <QDebug>


gallery_dialog::gallery_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gallery_dialog)
{
    ui->setupUi(this);

    //QDir dir("/forlinx/media");
    QDir dir("./");

    if(dir.exists())
    {
        printf("The directory exists.");
    }
    else
    {
        printf("The directory does not exists.");
    }

    QStringList filters;
    filters << "*.txt" << "*.mp4";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();

        for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        ui->listWidget->addItem(fileInfo.fileName());
        //std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                //.arg(fileInfo.fileName()));
        //std::cout << std::endl;

        }
}

gallery_dialog::~gallery_dialog()
{
    delete ui;
}

void gallery_dialog::on_back_btn_clicked()
{
    close();
}

void gallery_dialog::on_play_btn_clicked()
{

    QListWidgetItem *videoItem = ui->listWidget->currentItem();
        QString fn =   videoItem->text();
        player_dialog * plr_diag = new player_dialog(this);
        qDebug() << fn << "\n";
        //plr_diag->setFilename("./live_out.mp4");
        plr_diag->setFilename(fn);
        plr_diag->setWindowState(Qt::WindowFullScreen);
        plr_diag->exec();
        qDebug() << "Returning from player!";
        delete(videoItem);
        delete(plr_diag);



}
