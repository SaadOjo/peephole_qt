#include "videopane.h"
#include <QApplication>

videopane::videopane(QWidget *parent) :
    QWidget(parent)
{
    connect(&thread, SIGNAL(renderedImage(image_with_mutex *)),
                   this, SLOT(setPicture(image_with_mutex *)));

    setAutoFillBackground(true);
}


void videopane::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
    painter.drawPixmap(this->rect(),pixmap);
    //painter.drawPixmap(((QWidget*)parent())->rect(),pixmap);

}



void videopane::setPicture(image_with_mutex *i){

    i->mutex.lock();
    pixmap=QPixmap::fromImage(*i->image);
    update();
    qApp->processEvents();
    delete i->image;
    i->mutex.unlock();

}

videopane::~videopane(){

}


void videopane::setFileName(QString f){
 //   thread.setFileName(f);
}

void videopane::setDeviceName(QString f){
 //   thread.setDeviceName(f);
}

