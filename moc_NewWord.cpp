/****************************************************************************
** Meta object code from reading C++ file 'NewWord.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NewWord.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewWord.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TransToolw_t {
    QByteArrayData data[7];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TransToolw_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TransToolw_t qt_meta_stringdata_TransToolw = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 24),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 9),
QT_MOC_LITERAL(4, 47, 34),
QT_MOC_LITERAL(5, 82, 4),
QT_MOC_LITERAL(6, 87, 22)
    },
    "TransToolw\0on_action_Open_triggered\0"
    "\0initilise\0on_parselection_currentTextChanged\0"
    "arg1\0on_add_to_dict_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransToolw[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08,
       3,    0,   35,    2, 0x08,
       4,    1,   36,    2, 0x08,
       6,    0,   39,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void TransToolw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransToolw *_t = static_cast<TransToolw *>(_o);
        switch (_id) {
        case 0: _t->on_action_Open_triggered(); break;
        case 1: _t->initilise(); break;
        case 2: _t->on_parselection_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_add_to_dict_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject TransToolw::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TransToolw.data,
      qt_meta_data_TransToolw,  qt_static_metacall, 0, 0}
};


const QMetaObject *TransToolw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransToolw::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransToolw.stringdata))
        return static_cast<void*>(const_cast< TransToolw*>(this));
    return QDialog::qt_metacast(_clname);
}

int TransToolw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
