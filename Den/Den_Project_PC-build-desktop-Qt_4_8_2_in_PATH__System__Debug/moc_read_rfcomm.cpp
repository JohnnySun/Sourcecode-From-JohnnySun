/****************************************************************************
** Meta object code from reading C++ file 'read_rfcomm.h'
**
** Created: Sun Aug 3 00:42:28 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Den_Project/Den_Project_PC/read_rfcomm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'read_rfcomm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_read_rfcomm[] = {

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
      17,   12,   13,   12, 0x0a,
      31,   12,   13,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_read_rfcomm[] = {
    "read_rfcomm\0\0int\0conn_rfcomm()\0"
    "discon_rfcomm()\0"
};

void read_rfcomm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        read_rfcomm *_t = static_cast<read_rfcomm *>(_o);
        switch (_id) {
        case 0: { int _r = _t->conn_rfcomm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->discon_rfcomm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData read_rfcomm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject read_rfcomm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_read_rfcomm,
      qt_meta_data_read_rfcomm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &read_rfcomm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *read_rfcomm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *read_rfcomm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_read_rfcomm))
        return static_cast<void*>(const_cast< read_rfcomm*>(this));
    return QObject::qt_metacast(_clname);
}

int read_rfcomm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
