#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H

#include <QDialog>
#include <QDebug>

#include <gallery_dialog.h>
#include <settings_dialog.h>

namespace Ui {
class menu_dialog;
}

class menu_dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit menu_dialog(QWidget *parent = 0);
    ~menu_dialog();
    
private slots:
    void on_back_btn_clicked();

    void on_setting_btn_clicked();

    void on_gallery_btn_clicked();

private:
    Ui::menu_dialog *ui;
    gallery_dialog *glry_dlg;
    //settings_dialog *x;
    //settings_dialog *stng_dlg;
};

#endif // MENU_DIALOG_H
