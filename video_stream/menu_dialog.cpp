#include "menu_dialog.h"
#include "ui_menu_dialog.h"

menu_dialog::menu_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu_dialog)
{
    ui->setupUi(this);


}

menu_dialog::~menu_dialog()
{
    delete ui;
}

void menu_dialog::on_back_btn_clicked()
{
    close();
}

void menu_dialog::on_setting_btn_clicked()
{
/*
    stng_dlg  = new settings_dialog(this);
    stng_dlg->setWindowState(Qt::WindowFullScreen);
    stng_dlg->exec();
    qDebug() << "Returning from settings dialog!";
    delete(stng_dlg);
    */
    //little bit of a problem but hey it works.
    settings_dialog *x  = new settings_dialog(this);
    x->setWindowState(Qt::WindowFullScreen);
    x->exec();
    qDebug() << "Returning from settings dialog!";
    delete(x);

}

void menu_dialog::on_gallery_btn_clicked()
{
    glry_dlg = new gallery_dialog(this);
    //send structure where settings are held
    glry_dlg->setWindowState(Qt::WindowFullScreen);
    glry_dlg->exec();
    qDebug() << "Returning from gallery dialog!";
    delete(glry_dlg);

}
