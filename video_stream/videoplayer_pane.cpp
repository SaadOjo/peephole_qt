#include <QApplication>
#include "videoplayer_pane.h"

videoplayer_pane::videoplayer_pane(QWidget *parent) :
    QWidget(parent)
{
    //connect(&thread, SIGNAL(frameDecoded(QImage *)),
    //               this, SLOT(setPicture(QImage *)));

    connect(&thread, SIGNAL(frameDecoded(image_with_mutex *)),
                   this, SLOT(setPicture(image_with_mutex *)));

    setAutoFillBackground(true);
}


void videoplayer_pane::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
    painter.drawPixmap(this->rect(),pixmap);
    //painter.drawPixmap(((QWidget*)parent())->rect(),pixmap);

}



void videoplayer_pane::setPicture(image_with_mutex *i){

    i->mutex.lock();
    pixmap=QPixmap::fromImage(*i->image);
    update();
    qApp->processEvents();
    //delete i;
    delete i->image;
    i->mutex.unlock();

}

videoplayer_pane::~videoplayer_pane(){

}



