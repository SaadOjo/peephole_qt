#ifndef VIDEOPLAYER_PANE_H
#define VIDEOPLAYER_PANE_H

#include <QWidget>
#include <QPainter>
#include <QQueue>
#include <QPixmap>

#include "video_decoder_thread.h"



class videoplayer_pane : public QWidget
{
Q_OBJECT
public:
    videoplayer_pane(QWidget *parent = 0);
    ~videoplayer_pane();

    QPixmap pixmap;
    video_decoder_thread thread;


protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
   // void setPicture(QImage*);
    void setPicture(image_with_mutex*);

private:


};


#endif // VIDEOPLAYER_PANE_H
