/****************************************************************************
** Meta object code from reading C++ file 'SGOOnMapTM.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SGOOnMapTM.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SGOOnMapTM.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGOOnMapTM_t {
    QByteArrayData data[9];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SGOOnMapTM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SGOOnMapTM_t qt_meta_stringdata_SGOOnMapTM = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SGOOnMapTM"
QT_MOC_LITERAL(1, 11, 15), // "SGOCountChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "id"
QT_MOC_LITERAL(4, 31, 12), // "EditPosition"
QT_MOC_LITERAL(5, 44, 1), // "x"
QT_MOC_LITERAL(6, 46, 1), // "y"
QT_MOC_LITERAL(7, 48, 1), // "z"
QT_MOC_LITERAL(8, 50, 12) // "EditRotation"

    },
    "SGOOnMapTM\0SGOCountChanged\0\0id\0"
    "EditPosition\0x\0y\0z\0EditRotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGOOnMapTM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    4,   32,    2, 0x0a /* Public */,
       8,    4,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    5,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    5,    6,    7,

       0        // eod
};

void SGOOnMapTM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SGOOnMapTM *_t = static_cast<SGOOnMapTM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SGOCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->EditPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: _t->EditRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SGOOnMapTM::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SGOOnMapTM::SGOCountChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SGOOnMapTM::staticMetaObject = {
    { &GETable<SGOOnMapDbInfo>::staticMetaObject, qt_meta_stringdata_SGOOnMapTM.data,
      qt_meta_data_SGOOnMapTM,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SGOOnMapTM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGOOnMapTM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGOOnMapTM.stringdata0))
        return static_cast<void*>(const_cast< SGOOnMapTM*>(this));
    return GETable<SGOOnMapDbInfo>::qt_metacast(_clname);
}

int SGOOnMapTM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GETable<SGOOnMapDbInfo>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SGOOnMapTM::SGOCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
