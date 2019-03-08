/****************************************************************************
** Meta object code from reading C++ file 'video_decoder_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../video_stream/video_decoder_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'video_decoder_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_video_decoder_thread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   22,   21,   21, 0x05,
      65,   21,   21,   21, 0x05,
     103,   21,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_video_decoder_thread[] = {
    "video_decoder_thread\0\0imageMutex\0"
    "frameDecoded(image_with_mutex*)\0"
    "audio_capture_started(start_context*)\0"
    "videoStopped()\0"
};

void video_decoder_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        video_decoder_thread *_t = static_cast<video_decoder_thread *>(_o);
        switch (_id) {
        case 0: _t->frameDecoded((*reinterpret_cast< image_with_mutex*(*)>(_a[1]))); break;
        case 1: _t->audio_capture_started((*reinterpret_cast< start_context*(*)>(_a[1]))); break;
        case 2: _t->videoStopped(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData video_decoder_thread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject video_decoder_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_video_decoder_thread,
      qt_meta_data_video_decoder_thread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &video_decoder_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *video_decoder_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *video_decoder_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_video_decoder_thread))
        return static_cast<void*>(const_cast< video_decoder_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int video_decoder_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void video_decoder_thread::frameDecoded(image_with_mutex * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void video_decoder_thread::audio_capture_started(start_context * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void video_decoder_thread::videoStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
