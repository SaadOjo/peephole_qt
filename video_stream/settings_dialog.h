#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui {
class settings_dialog;
}

class settings_dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit settings_dialog(QWidget *parent = 0);
    ~settings_dialog();
    
private slots:
    void on_back_btn_clicked();

private:
    Ui::settings_dialog *ui;
};

#endif // SETTINGS_DIALOG_H
