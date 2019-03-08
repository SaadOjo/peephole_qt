#ifndef GALLERY_DIALOG_H
#define GALLERY_DIALOG_H

#include <QDialog>

namespace Ui {
class gallery_dialog;
}

class gallery_dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit gallery_dialog(QWidget *parent = 0);
    ~gallery_dialog();
    
private:
    Ui::gallery_dialog *ui;
};

#endif // GALLERY_DIALOG_H
