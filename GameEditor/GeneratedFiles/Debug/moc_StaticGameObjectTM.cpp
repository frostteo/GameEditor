/****************************************************************************
** Meta object code from reading C++ file 'StaticGameObjectTM.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../StaticGameObjectTM.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StaticGameObjectTM.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StaticGameObjectTM_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StaticGameObjectTM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StaticGameObjectTM_t qt_meta_stringdata_StaticGameObjectTM = {
    {
QT_MOC_LITERAL(0, 0, 18), // "StaticGameObjectTM"
QT_MOC_LITERAL(1, 19, 16), // "TableDataChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "PagingInfoChanged"
QT_MOC_LITERAL(4, 55, 10), // "PagingInfo"
QT_MOC_LITERAL(5, 66, 10) // "pagingInfo"

    },
    "StaticGameObjectTM\0TableDataChanged\0"
    "\0PagingInfoChanged\0PagingInfo\0pagingInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StaticGameObjectTM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    1,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void StaticGameObjectTM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StaticGameObjectTM *_t = static_cast<StaticGameObjectTM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->TableDataChanged(); break;
        case 1: _t->PagingInfoChanged((*reinterpret_cast< PagingInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StaticGameObjectTM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StaticGameObjectTM::TableDataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StaticGameObjectTM::*_t)(PagingInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StaticGameObjectTM::PagingInfoChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject StaticGameObjectTM::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_StaticGameObjectTM.data,
      qt_meta_data_StaticGameObjectTM,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StaticGameObjectTM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StaticGameObjectTM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StaticGameObjectTM.stringdata0))
        return static_cast<void*>(const_cast< StaticGameObjectTM*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int StaticGameObjectTM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void StaticGameObjectTM::TableDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StaticGameObjectTM::PagingInfoChanged(PagingInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
