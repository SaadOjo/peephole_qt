/****************************************************************************
** Meta object code from reading C++ file 'player_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../video_stream/player_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_player_dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   14,   14,   14, 0x08,
      67,   14,   14,   14, 0x08,
      90,   14,   14,   14, 0x08,
     123,  117,   14,   14, 0x08,
     156,  117,   14,   14, 0x08,
     199,  191,   14,   14, 0x08,
     225,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_player_dialog[] = {
    "player_dialog\0\0i\0setImage(image_with_mutex*)\0"
    "on_back_btn_clicked()\0on_pause_btn_clicked()\0"
    "on_play_stop_btn_clicked()\0value\0"
    "on_seek_slider_valueChanged(int)\0"
    "on_volume_slider_valueChanged(int)\0"
    "checked\0on_mute_chk_toggled(bool)\0"
    "videoStoppedSlot()\0"
};

void player_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        player_dialog *_t = static_cast<player_dialog *>(_o);
        switch (_id) {
        case 0: _t->setImage((*reinterpret_cast< image_with_mutex*(*)>(_a[1]))); break;
        case 1: _t->on_back_btn_clicked(); break;
        case 2: _t->on_pause_btn_clicked(); break;
        case 3: _t->on_play_stop_btn_clicked(); break;
        case 4: _t->on_seek_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_volume_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_mute_chk_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->videoStoppedSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData player_dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject player_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_player_dialog,
      qt_meta_data_player_dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &player_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *player_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *player_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_player_dialog))
        return static_cast<void*>(const_cast< player_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int player_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void player_dialog::setImage(image_with_mutex * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
