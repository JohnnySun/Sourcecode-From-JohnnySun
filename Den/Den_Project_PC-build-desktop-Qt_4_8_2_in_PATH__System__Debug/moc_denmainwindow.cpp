/****************************************************************************
** Meta object code from reading C++ file 'denmainwindow.h'
**
** Created: Sun Aug 3 00:42:27 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Den_Project/Den_Project_PC/denmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'denmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DenMainWindow[] = {

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
      23,   15,   14,   14, 0x08,
      52,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DenMainWindow[] = {
    "DenMainWindow\0\0checked\0"
    "on_conn_button_clicked(bool)\0"
    "on_pushButton_clicked()\0"
};

void DenMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DenMainWindow *_t = static_cast<DenMainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_conn_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DenMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DenMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DenMainWindow,
      qt_meta_data_DenMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DenMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DenMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DenMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DenMainWindow))
        return static_cast<void*>(const_cast< DenMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DenMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
