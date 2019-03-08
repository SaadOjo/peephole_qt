/****************************************************************************
** Meta object code from reading C++ file 'speaker.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../video_stream/speaker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'speaker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Speaker[] = {

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
      15,    9,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Speaker[] = {
    "Speaker\0\0sound\0playSound(safe_sound*)\0"
};

void Speaker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Speaker *_t = static_cast<Speaker *>(_o);
        switch (_id) {
        case 0: _t->playSound((*reinterpret_cast< safe_sound*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Speaker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Speaker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Speaker,
      qt_meta_data_Speaker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Speaker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Speaker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Speaker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Speaker))
        return static_cast<void*>(const_cast< Speaker*>(this));
    return QObject::qt_metacast(_clname);
}

int Speaker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
