/****************************************************************************
** Meta object code from reading C++ file 'videoplayer_pane.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../video_stream/videoplayer_pane.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplayer_pane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_videoplayer_pane[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_videoplayer_pane[] = {
    "videoplayer_pane\0\0setPicture(image_with_mutex*)\0"
};

void videoplayer_pane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        videoplayer_pane *_t = static_cast<videoplayer_pane *>(_o);
        switch (_id) {
        case 0: _t->setPicture((*reinterpret_cast< image_with_mutex*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData videoplayer_pane::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject videoplayer_pane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_videoplayer_pane,
      qt_meta_data_videoplayer_pane, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &videoplayer_pane::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *videoplayer_pane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *videoplayer_pane::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_videoplayer_pane))
        return static_cast<void*>(const_cast< videoplayer_pane*>(this));
    return QWidget::qt_metacast(_clname);
}

int videoplayer_pane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
