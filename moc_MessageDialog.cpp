/****************************************************************************
** Meta object code from reading C++ file 'MessageDialog.h'
**
** Created: Wed Feb 8 10:10:46 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MessageDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessageDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MessageDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      20,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MessageDialog[] = {
    "MessageDialog\0\0ok()\0exit()\0"
};

const QMetaObject MessageDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MessageDialog,
      qt_meta_data_MessageDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MessageDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MessageDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MessageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MessageDialog))
        return static_cast<void*>(const_cast< MessageDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MessageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ok(); break;
        case 1: exit(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE