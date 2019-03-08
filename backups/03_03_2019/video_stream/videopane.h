#ifndef VIDEOPANE_H
#define VIDEOPANE_H


#include <QWidget>
#include <QPainter>
#include <QQueue>
#include <QMutex>
#include <QPixmap>

#include "capturethread.h"
#include "structures.h"

class videopane : public QWidget
{
Q_OBJECT
public:
    videopane(QWidget *parent = 0);
    ~videopane();

    QPixmap pixmap;
    CaptureThread thread;
    void setFileName(QString);
    void setDeviceName(QString);


protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    //void setPicture(QImage*);
    void setPicture(image_with_mutex *);

private:


};



#endif // VIDEOPANE_H
