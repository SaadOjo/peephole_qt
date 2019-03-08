/****************************************************************************
** Meta object code from reading C++ file 'audio_playback_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../video_stream/audio_playback_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audio_playback_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_audio_playback_thread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      65,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_audio_playback_thread[] = {
    "audio_playback_thread\0\0"
    "act_on_audio_thread_start(start_context*)\0"
    "act_on_audio_thread_stop()\0"
};

void audio_playback_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        audio_playback_thread *_t = static_cast<audio_playback_thread *>(_o);
        switch (_id) {
        case 0: _t->act_on_audio_thread_start((*reinterpret_cast< start_context*(*)>(_a[1]))); break;
        case 1: _t->act_on_audio_thread_stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData audio_playback_thread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject audio_playback_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_audio_playback_thread,
      qt_meta_data_audio_playback_thread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &audio_playback_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *audio_playback_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *audio_playback_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_audio_playback_thread))
        return static_cast<void*>(const_cast< audio_playback_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int audio_playback_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
