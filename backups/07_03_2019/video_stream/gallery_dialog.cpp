#include "gallery_dialog.h"
#include "ui_gallery_dialog.h"

gallery_dialog::gallery_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gallery_dialog)
{
    ui->setupUi(this);
}

gallery_dialog::~gallery_dialog()
{
    delete ui;
}
