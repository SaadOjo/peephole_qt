#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<QMutex>
#include<QImage>
#include<QWaitCondition>

struct image_with_mutex
{
    QMutex mutex;
    QImage *image;
};

struct safe_sound
{
    QMutex mutex;
    QWaitCondition cond;
    unsigned char *sound;
};

#endif // STRUCTURES_H
